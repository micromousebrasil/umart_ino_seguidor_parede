/*
 * controlador.h
 *
 *  Created on: 30/06/2015
 *      Author: Kleber Lima da Silva (micromousebrasil@gmail.com)
 */

#ifndef CONTROLADOR_H_
#define CONTROLADOR_H_


// Bibliotecas -----------------------------------------------------------------
#include <stdint.h>
#include <math.h>
#include "Encoder.h"
#include "motores.h"
#include "sensores.h"


// Definição dos Pinos ---------------------------------------------------------
#define ENCODER_A_E 4	// Encoder do motor esquerdo (sinal A)
#define ENCODER_B_E 2	// Encoder do motor esquerdo (sinal B)
#define ENCODER_A_D 3	// Encoder do motor direito (sinal A)
#define ENCODER_B_D 5	// Encoder do motor direito (sinal B)


// Constantes ------------------------------------------------------------------
// Ganho dos controladores de velocidade
#define KP	5	// Ganho Proporcional
#define KD	10	// Ganho Derivativo

// Indica o tipo de movimento
#define TRANSLACIONAL	0
#define ROTACIONAL		1

// Parâmetros do robô
#define ENCODER_PPR		360		// Resolução do Encoder pulsos por revolução [ppr]
#define	DIAMETRO_RODA	32		// Diâmetro da roda [mm]
#define RODA_RODA		84		// Distância entre as rodas [mm]
#define CNT_POR_1000MM	3581	// = (1000*ENCODER_PPR) / (DIAMETRO_RODA*PI)
#define CNT_POR_360DEG	945		// = ((PI*W_DISTANCE)*CNT_PER_1000MM)/(1000)

// Parâmetros do controlador
#define TS	10		// Período de amostragem [ms]
#define K_SENSORES	100	// Constante para ajuste do peso dos sensores no controlador
#define SPEED_RETA	300	// Velocidade nas retas [mm/s]
#define SPEED_CURVA	300	// Velocidade nas curvas [mm/s]

#define CELULA	180	// Tamanho da célula [mm]


// Macros ----------------------------------------------------------------------
#define LER_ENCODER_E	-encoder_esquerda.read()
#define LER_ENCODER_D	-encoder_direita.read()
#define RESET_ENCODER_E	encoder_esquerda.write(0)
#define RESET_ENCODER_D	encoder_direita.write(0)

#define COUNTS_TO_MM(cnt)	(((cnt) * 1000) / CNT_POR_1000MM)
#define COUNTS_TO_DEG(cnt)	(((cnt) * 360) / CNT_POR_360DEG)
#define DIST_TO_COUNTS(mm)	(((mm) * CNT_POR_1000MM) / 1000)
#define SPEED_TO_COUNTS(speed)	((CNT_POR_1000MM * (speed) * TS) / 1000000)
#define RAD_S_TO_COUNTS(rad_s)	(SPEED_TO_COUNTS(rad_s * RODA_RODA))


// Protótipo das Funções -------------------------------------------------------
void controleVelocidade(void);
void setMovimento(int32_t raio, int32_t dist_angulo, int32_t speed);
void updateEncoders(void);
void controladorPID(void);
void controleVelocidade(void);
bool isFinalMovimento(void);
void resetControlador(void);
void frente(int32_t distancia);
void curvaPivot(int16_t graus);
void curva(int16_t graus);


// Variáveis Externas ----------------------------------------------------------
extern int32_t distancia_mm;
extern int32_t distancia_deg;
extern Encoder encoder_esquerda;
extern Encoder encoder_direita;


#endif /* CONTROLADOR_H_ */
