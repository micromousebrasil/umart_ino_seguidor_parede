/*
 * umart_ino_seguidor_parede.h
 *
 *  Created on: 30/06/2015
 *      Author: Kleber Lima da Silva (micromousebrasil@gmail.com)
 */

#ifndef _umart_ino_seguidor_parede_H_
#define _umart_ino_seguidor_parede_H_


// Bibliotecas -----------------------------------------------------------------
#include "Arduino.h"
#include "TimerOne.h"
#include "motores.h"
#include "sensores.h"
#include "controlador.h"
#include <stdint.h>


// Definição dos pinos no modo MICROMOUSE --------------------------------------
#define LED1 0		// LED1
#define LED2  1		// LED2
#define B_ENC_E 2	// Encoder do motor esquerdo (sinal B)
#define A_ENC_D 3	// Encoder do motor direito (sinal A)
#define A_ENC_E 4	// Encoder do motor esquerdo (sinal A)
#define B_ENC_D 5	// Encoder do motor direito (sinal B)
#define SW1 12		// Botão SW1


// Constantes ------------------------------------------------------------------
#define ESQUERDA 1
#define DIREITA 2


// Protótipo das Funções -------------------------------------------------------
void setup(void);
void loop(void);
void callbackTimer1(void);


#endif /* _umart_ino_seguidor_parede_H_ */
