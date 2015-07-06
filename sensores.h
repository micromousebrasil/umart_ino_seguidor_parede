/*
 * sensores.h
 *
 *  Created on: 30/06/2015
 *      Author: Kleber Lima da Silva (micromousebrasil@gmail.com)
 */

#ifndef SENSORES_H_
#define SENSORES_H_

// Bibliotecas -----------------------------------------------------------------
#include "Arduino.h"


// Definição dos Pinos ---------------------------------------------------------
#define FE_RECEPTOR	A0	// Fototransistor frontal esquerdo
#define LE_RECEPTOR	A1	// Fototransistor lateral esquerdo
#define LD_RECEPTOR	A2	// Fototransistor lateral direito
#define FD_RECEPTOR	A3	// Fototransistor frontal direito
#define FE_EMISSOR	A4	// LED frontal esquerdo
#define L_EMISSORES	13	// LEDs laterais
#define FD_EMISSOR	A5	// LED frontal direito


// Constantes ------------------------------------------------------------------
const int16_t FRONTAL_TH = 80;	// Limiar para reconhecer parede frontal ou não
const int16_t LATERAL_TH = 80;	// Limiar para reconhecer parede lateral ou não
const int16_t CENTRO_LATERAL = 170;	// Leitura dos sensores laterais no centro da célula
const int16_t CENTRO_FRONTAL = 900;	// Leitura dos sensores frontais no centro da célula
const int16_t ALINHAMENTO_FRONTAL = 300;	// Valor para habilitar o alinhamento pelos sensores frontais


// Protótipo das Funções -------------------------------------------------------
uint8_t getSensoresParede(void);
int16_t getErroSensores(void);
void printSensores(void);


// Variáveis Externas ----------------------------------------------------------
extern int16_t frontal_esquerdo;
extern int16_t lateral_esquerdo;
extern int16_t lateral_direito;
extern int16_t frontal_direito;


#endif /* SENSORES_H_ */
