/*****************************************************
 * FileName:        gpio_config_2021.h
 * Dependencies:    msp.h
 * Processor:       MSP432
 * Board:           MSP432P401R
 * Program version: CCS V10 TI
 * Company:         TecNM /IT Chihuahua
 * Description:     DEFINICION DE ESTRUCTURAS DE CONFIGURACION DE LOS GPIO
 * Authors:         ALFREDO CHACON
 * Nota: Aqui se declran las estructuras, los punteros declarados se incializan
 * con las direcciones de memoria base de los puertos en cuestión en gpio.c
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
#include "msp.h"
#ifndef DRIVERS_GPIO_CONFIG_2021_H_
#define DRIVERS_GPIO_CONFIG_2021_H_
/************************************************
  DEFINICIONES MACROS A REGISTROS
 ************************************************/
#define PERI_BASE                   ((uint32_t) 0x40000000)
#define P1_Y_P2_BASE                (PERI_BASE + 0x0000004c00)
#define PUERTO_P1                   ((Struct_Puerto_impar *) P1_Y_P2_BASE)
#define   PUERTO_P2           ((Struct_Puerto_par *) P1_Y_P2_BASE)
/************************************************
  DEFINICIONES DE ESTRUCTURAS
 ************************************************/
typedef struct {
  __I uint8_t IN;                                                                 /*!< Port Input */
  uint8_t RESERVED0;
  __IO uint8_t OUT;                                                               /*!< Port Output */
  uint8_t RESERVED1;
  __IO uint8_t DIR;                                                               /*!< Port Direction */
  uint8_t RESERVED2;
  __IO uint8_t REN;                                                               /*!< Port Resistor Enable */
  uint8_t RESERVED3;
  __IO uint8_t DS;                                                                /*!< Port Drive Strength */
  uint8_t RESERVED4;
  __IO uint8_t SEL0;                                                              /*!< Port Select 0 */
  uint8_t RESERVED5;
  __IO uint8_t SEL1;                                                              /*!< Port Select 1 */
  uint8_t RESERVED6;
  __I  uint16_t IV;                                                               /*!< Port Interrupt Vector Value */
  uint8_t RESERVED7[6];
  __IO uint8_t SELC;                                                              /*!< Port Complement Select */
  uint8_t RESERVED8;
  __IO uint8_t IES;                                                               /*!< Port Interrupt Edge Select */
  uint8_t RESERVED9;
  __IO uint8_t IE;                                                                /*!< Port Interrupt Enable */
  uint8_t RESERVED10;
  __IO uint8_t IFG;                                                               /*!< Port Interrupt Flag */
  uint8_t RESERVED11;
} Struct_Puerto_impar;

typedef struct {
  uint8_t RESERVED0;
  __I uint8_t IN;                                                                 /*!< Port Input */
  uint8_t RESERVED1;
  __IO uint8_t OUT;                                                               /*!< Port Output */
  uint8_t RESERVED2;
  __IO uint8_t DIR;                                                               /*!< Port Direction */
  uint8_t RESERVED3;
  __IO uint8_t REN;                                                               /*!< Port Resistor Enable */
  uint8_t RESERVED4;
  __IO uint8_t DS;                                                                /*!< Port Drive Strength */
  uint8_t RESERVED5;
  __IO uint8_t SEL0;                                                              /*!< Port Select 0 */
  uint8_t RESERVED6;
  __IO uint8_t SEL1;                                                              /*!< Port Select 1 */
  uint8_t RESERVED7[9];
  __IO uint8_t SELC;                                                              /*!< Port Complement Select */
  uint8_t RESERVED8;
  __IO uint8_t IES;                                                               /*!< Port Interrupt Edge Select */
  uint8_t RESERVED9;
  __IO uint8_t IE;                                                                /*!< Port Interrupt Enable */
  uint8_t RESERVED10;
  __IO uint8_t IFG;                                                               /*!< Port Interrupt Flag */
  __I uint16_t IV;                                                                /*!< Port Interrupt Vector Value */
} Struct_Puerto_par;

//Calculos de los offsets de cada uno de los registros para puertos Pares y nones, segun las estructuras definidas en msp432p401r.h
#define OFS_LIB_PAIN    ((uint32_t)&P1->IN - (uint32_t)P1)
#define OFS_LIB_PAOUT   ((uint32_t)&P1->OUT - (uint32_t)P1)
#define OFS_LIB_PADIR   ((uint32_t)&P1->DIR - (uint32_t)P1)
#define OFS_LIB_PAREN   ((uint32_t)&P1->REN - (uint32_t)P1)
#define OFS_LIB_PADS    ((uint32_t)&P1->DS - (uint32_t)P1)
#define OFS_LIB_PASEL0  ((uint32_t)&P1->SEL0 - (uint32_t)P1)
#define OFS_LIB_PASEL1  ((uint32_t)&P1->SEL1 - (uint32_t)P1)
#define OFS_LIB_PAIE    ((uint32_t)&P1->IE - (uint32_t)P1)
#define OFS_LIB_PAIES   ((uint32_t)&P1->IES - (uint32_t)P1)
#define OFS_LIB_PAIFG   ((uint32_t)&P1->IFG - (uint32_t)P1)
#define OFS_LIB_P1IE    ((uint32_t)&P1->IE - (uint32_t)P1)
#define OFS_LIB_P2IE    OFS_LIB_P1IE

#endif      /* DRIVERS_GPIO_CONFIG_2021_H_ */
