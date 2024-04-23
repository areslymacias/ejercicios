/*****************************************************
 * FileName:        gpio_2021.h
 * Dependencies:
 * Processor:       MSP432
 * Board:           MSP432P401R
 * Program version: CCS V10 TI
 * Company:         TecNM /IT Chihuahua
 * Description:     PROTOTIPOS DE FUNCIONES DEL DRIVER
 * Authors:         ALFREDO CHACON
 * Nota: La interfaz definida de este DRIVER hace uso de las estructuras
 *       declarados en gpio_config_2021.h
 *  Created on: 6 oct. 2021
 *  updated: 20/11/2021
 **************************************************/
/************************************************************************************************
 * * Copyright (C) 2021 by Alfredo Chacon - TecNM /IT Chihuahua
 *
 * Se permite la redistribucion, modificacion o uso de este software en formato fuente o binario
 * siempre que los archivos mantengan estos derechos de autor.
 * Los usuarios pueden modificar esto y usarlo para aprender sobre el campo de software embebido.
 * Alfredo Chacon y el TecNM /IT Chihuahua no son responsables del mal uso de este material.
 *************************************************************************************************/
#ifndef GPIO_2021_H
#define GPIO_2021_H

//#include<stdint.h>
#include "DRIVERS\gpio_config_2021.h"


/************************************************
  DEFINICIONES DE CONSTANTES Y/O MASCARAS
 ************************************************/
#define RETARDO (100000)
#define RETARDO2 (10000)
#define PIN0    (0x01)      // definimos el numero Hexadecimal segun el Pin del PUERTO
#define PIN1    (0x02)
#define PIN2    (0x04)
#define PIN4    (0x10)
#define FALSE 0U
#define TRUE 1U
#define GPIO_INPUT_PIN_HIGH                                              (0x01)
#define GPIO_INPUT_PIN_LOW                                               (0x00)

//Definiciones de Puertos
#define GPIO_PORT_P1    1
#define GPIO_PORT_P2    2
#define GPIO_PORT_P3    2
#define GPIO_PORT_P4    4
#define GPIO_PORT_P5    5



//Definiciones de pines para las funciones
#define GPIO_PIN0    (0x0001)
#define GPIO_PIN1    (0x0002)
#define GPIO_PIN2    (0x0004)
#define GPIO_PIN3    (0x0008)
#define GPIO_PIN4    (0x0010)
#define GPIO_PIN5    (0x0020)
#define GPIO_PIN6    (0x0040)
#define GPIO_PIN7    (0x0080)


/************************************************
    PROTOTIPO DE FUNCIONES
************************************************/

extern void GPIO_setPinEntradaconPullUp(uint_fast8_t selectedPort,     uint_fast16_t selectedPins);
extern void GPIO_setPinSalida(uint_fast8_t selectedPort,                      uint_fast8_t selectedPins);

extern void GPIO_setPinAlto(uint_fast8_t selectedPort,                  uint_fast16_t selectedPins);
extern void GPIO_setPinBajo(uint_fast8_t selectedPort,                   uint_fast16_t selectedPins);
extern uint8_t GPIO_getPinValor(uint_fast8_t selectedPort,                 uint_fast16_t selectedPins);
extern uint8_t Gpio_Pin_in( uint_fast16_t pin_);
#endif  /* gpio_2021.h*/
