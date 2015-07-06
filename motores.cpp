/*
 * motores.cpp
 *
 *  Created on: 30/06/2015
 *      Author: Kleber Lima da Silva (micromousebrasil@gmail.com)
 */

#include "motores.h"


/* Função para acionamento dos motores ---------------------------
 * pwm_esquerda e pwm_direita recebem valores entre -255 e 255
 * (valores negativos giram o respectivo motor para trás)
 */
void setMotores(int16_t pwm_esquerda, int16_t pwm_direita)
{
	if(pwm_esquerda < 0)
	{
		pwm_esquerda = -pwm_esquerda;

		digitalWrite(IN1_E, LOW);
		digitalWrite(IN2_E, HIGH);
	}
	else
	{
		digitalWrite(IN1_E, HIGH);
		digitalWrite(IN2_E, LOW);
	}

	if(pwm_direita < 0)
	{
		pwm_direita = -pwm_direita;

		digitalWrite(IN1_D, LOW);
		digitalWrite(IN2_D, HIGH);
	}
	else
	{
		digitalWrite(IN1_D, HIGH);
		digitalWrite(IN2_D, LOW);
	}

	if(pwm_esquerda > 255) pwm_esquerda = 255;
	if(pwm_direita > 255) pwm_direita = 255;

	analogWrite(PWM_E, pwm_esquerda);
	analogWrite(PWM_D, pwm_direita);
}

