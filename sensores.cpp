/*
 * sensores.cpp
 *
 *  Created on: 30/06/2015
 *      Author: Kleber Lima da Silva (micromousebrasil@gmail.com)
 */

#include "sensores.h"

// Variáveis Externas ----------------------------------------------------------
int16_t frontal_esquerdo = 0;
int16_t lateral_esquerdo = 0;
int16_t lateral_direito = 0;
int16_t frontal_direito = 0;


/* Função para leitura dos sensores de parede ----------------------------------
 * Atualiza as leituras dos sensores frontais e laterais.
 * Retorna uma máscara de bits indicando presença (1) ou não (0)
 * de paredes. O bit mais significativo representa a parede da
 * esquerda. Ex.: 011 = presença de parede frontal e direita.
 */
uint8_t getSensoresParede(void)
{
	uint8_t paredes = 0;

	frontal_esquerdo = analogRead(FE_RECEPTOR);
	lateral_esquerdo = analogRead(LE_RECEPTOR);
	lateral_direito = analogRead(LD_RECEPTOR);
	frontal_direito = analogRead(FD_RECEPTOR);

	// Registra o tempo atual
	uint32_t t0 = micros();

	// Sensor frontal esquerdo
	digitalWrite(FE_EMISSOR, HIGH);
	while((micros() - t0) < 80);
	frontal_esquerdo = analogRead(FE_RECEPTOR) - frontal_esquerdo;
	digitalWrite(FE_EMISSOR, LOW);
	if(frontal_esquerdo < 0) frontal_esquerdo = 0;
	while((micros() - t0) < 160);

	// Sensor frontal direito
	digitalWrite(FD_EMISSOR, HIGH);
	while((micros() - t0) < 240);
	frontal_direito = analogRead(FD_RECEPTOR) - frontal_direito;
	digitalWrite(FD_EMISSOR, LOW);
	if(frontal_direito < 0) frontal_direito = 0;
	while((micros() - t0) < 320);

	// Sensores laterais
	digitalWrite(L_EMISSORES, HIGH);
	while((micros() - t0) < 400);
	lateral_esquerdo = analogRead(LE_RECEPTOR) - lateral_esquerdo;
	lateral_direito = analogRead(LD_RECEPTOR) - lateral_direito;
	digitalWrite(L_EMISSORES, LOW);
	if(lateral_esquerdo < 0) lateral_esquerdo = 0;
	if(lateral_direito < 0) lateral_direito = 0;

	// Realiza a máscara de bits
	if(frontal_esquerdo > FRONTAL_TH || frontal_direito > FRONTAL_TH)
	{
		paredes |= 0b010;
	}

	if(lateral_esquerdo > LATERAL_TH)
	{
		paredes |= 0b100;
	}

	if(lateral_direito > LATERAL_TH)
	{
		paredes |= 0b001;
	}

	return paredes;
}


/* Retorna o erro de alinhamento dos sensores ----------------------------------
 *
 */
int16_t getErroSensores(void)
{
	int16_t erro = 0;

	/* ------ ALINHAMENTO LATERAL ------ */
	if (frontal_esquerdo < FRONTAL_TH && frontal_direito < FRONTAL_TH)
	{
		if (lateral_esquerdo > CENTRO_LATERAL && lateral_direito < CENTRO_LATERAL)
		{
			erro = lateral_esquerdo - CENTRO_LATERAL;
		}
		else if (lateral_direito > CENTRO_LATERAL && lateral_esquerdo < CENTRO_LATERAL)
		{
			erro = CENTRO_LATERAL - lateral_direito;
		}
	}
	/* ------ ALINHAMENTO FRONTAL ------ */
	else if (frontal_esquerdo > ALINHAMENTO_FRONTAL && frontal_direito > ALINHAMENTO_FRONTAL)
	{
		erro = (frontal_direito - frontal_esquerdo);
	}

	return erro;
}
