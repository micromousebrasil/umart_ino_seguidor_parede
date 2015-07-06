/*
 * motores.h
 *
 *  Created on: 30/06/2015
 *      Author: Kleber Lima da Silva (micromousebrasil@gmail.com)
 */

#ifndef MOTORES_H_
#define MOTORES_H_

// Bibliotecas -----------------------------------------------------------------
#include "Arduino.h"


// Definição dos Pinos ---------------------------------------------------------
#define PWM_E	6	// PWM do motor esquerdo
#define IN2_E	7	// IN2 da ponte H do motor esquerdo
#define IN1_E	8	// IN1 da ponte H do motor esquerdo
#define IN1_D	9	// IN1 da ponte H do motor direito
#define IN2_D	10	// IN2 da ponte H do motor direito
#define PWM_D	11	// PWM do motor direito


// Protótipo das Funções -------------------------------------------------------
void setMotores(int16_t pwm_esquerda, int16_t pwm_direita);


#endif /* MOTORES_H_ */
