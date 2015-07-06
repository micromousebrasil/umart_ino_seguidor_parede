/**
 *******************************************************************************
 * Arquivo  umart_ino_seguidor_parede.cpp
 * Autor    Kleber Lima da Silva (micromousebrasil@gmail.com)
 * Versão   V1.0.0
 * Data     30-Junho-2015
 * Resumo   Programa de demonstração do Robô uMaRT-INO no modo
 *         micromouse (algoritmo seguidor de parede)
 *******************************************************************************
 */

// Bibliotecas -----------------------------------------------------------------
#include "umart_ino_seguidor_parede.h"


// Variáveis do Privadas -------------------------------------------------------
bool bRodarControle = false;
uint8_t seguidor = 0;
uint8_t paredes = 0;


//#define USE_UART	// Comentar esta linha para usar os LEDs
// Inicialização dos Periféricos -----------------------------------------------
void setup()
{
	pinMode(FE_RECEPTOR, INPUT);
	pinMode(LE_RECEPTOR, INPUT);
	pinMode(LD_RECEPTOR, INPUT);
	pinMode(FD_RECEPTOR, INPUT);
	pinMode(FE_EMISSOR, OUTPUT);
	pinMode(L_EMISSORES, OUTPUT);
	pinMode(FD_EMISSOR, OUTPUT);
	pinMode(PWM_E, OUTPUT);
	pinMode(IN1_E, OUTPUT);
	pinMode(IN2_E, OUTPUT);
	pinMode(PWM_D, OUTPUT);
	pinMode(IN1_D, OUTPUT);
	pinMode(IN2_D, OUTPUT);
	pinMode(SW1, INPUT);

#ifdef USE_UART	// Inicialização para usar a UART
	pinMode(0, INPUT);
	pinMode(1, OUTPUT);
	Serial.begin(115200);
#else	// Inicialização para usar os LEDs
	pinMode(LED1, OUTPUT);
	pinMode(LED2, OUTPUT);
	digitalWrite(LED1, LOW);
	digitalWrite(LED2, LOW);
#endif

	// Será habilitado seguidor de parede esquerda ou direita de acordo com o
	// respectivo sensor frontal acionado
	while ((getSensoresParede() & 0b010) == 0)
	{
		delay(100);
	}
	if (frontal_esquerdo > frontal_direito)
	{
		seguidor = ESQUERDA;
	}
	else
	{
		seguidor = DIREITA;
	}
	delay(2000);	// Aguarda um tempo para a partida do micromouse

	// Inicia o Timer do controle de velocidade
	Timer1.initialize(TS * 1000);
	Timer1.attachInterrupt(callbackTimer1);
	bRodarControle = true;

	// Ao iniciar o micromouse deve estar no centro da primeira célula...
	// Com isso, deve se deslocar meia célula até a FRONTEIRA da próxima célula
	// (local IDEAL para realizar a leitura dos sensores)
	frente(CELULA / 2);
}


// LOOP principal do programa --------------------------------------------------
void loop()
{
	// Realiza a máquina de estados de acordo com o que foi selecionado
	if (seguidor == DIREITA)
	{
		switch (paredes)	// Máquina de Estados - Seguidor de Parede DIREITA
		{
		// Sem paredes
		case 0b000:
			curva(-90);	// Vira para a direita
			break;

		// Apenas parede da direita
		case 0b001:
			frente(CELULA);	// Anda uma célula para frente
			break;

		// Apenas parede da esquerda
		case 0b100:
			curva(-90);	// Vira para a direita
			break;

		// Ambas paredes laterais
		case 0b101:
			frente(CELULA);	// Anda uma célula para frente
			break;

		// Apenas parede frontal
		case 0b010:
			curva(-90);	// Vira para a direita
			break;

		// Parede frontal e direita
		case 0b011:
			curva(90);	// Vira para a esquerda
			break;

		// Parede frontal e esquerda
		case 0b110:
			curva(-90);	// Vira para a direita
			break;

		// Todas as paredes
		case 0b111:
			curva(180);	// Meia volta
			break;
		}
	}
	else if (seguidor == ESQUERDA)
	{
		switch (paredes)	// Máquina de Estados - Seguidor de Parede ESQUERDA
		{
		// Sem paredes
		case 0b000:
			curva(90);	// Vira para esquerda
			break;

		// Apenas parede da direita
		case 0b001:
			curva(90);	// Vira para esquerda
			break;

		// Apenas parede da esquerda
		case 0b100:
			frente(CELULA);	// Anda uma célula para frente
			break;

		// Ambas paredes laterais
		case 0b101:
			frente(CELULA);	// Anda uma célula para frente
			break;

		// Apenas parede frontal
		case 0b010:
			curva(90);	// Vira para esquerda
			break;

		// Parede frontal e direita
		case 0b011:
			curva(90);	// Vira para a esquerda
			break;

		// Parede frontal e esquerda
		case 0b110:
			curva(-90);	// Vira para direita
			break;

		// Todas as paredes
		case 0b111:
			curva(-180);	// Meia volta
			break;
		}
	}
}


// Callback do Timer 1 - Controle de Velocidade --------------------------------
void callbackTimer1(void)
{
	if (bRodarControle == true)
	{
		paredes = getSensoresParede();	// Realiza a leitura dos sensores
		controleVelocidade();			// Realiza o controle de velocidade
	}
}
