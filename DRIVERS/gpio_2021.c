/*****************************************************
 * FileName:        gpio_2021.c
 * Dependencies:    gpio_2021.h
 * Processor:       MSP432
 * Board:           MSP432P401R
 * Program version: CCS V10 TI
 * Company:         TecNM /IT Chihuahua
 * Description:     IMPLEMENTACION DE LAS FUNCIONES DEL DRIVER
 * Authors:         ALFREDO CHACON
 * Nota:  Aqui se declaran los metodos
 *
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
#include "gpio_2021.h"

/* Declaración del arreglo GPIO_PORT_TO_BASE
 * En el cual se encuentran las direcciones en donde comienzan
 * los registros de control para cada puerto.                   */
static const uint32_t GPIO_PORT_TO_BASE[] =
{   0x00,
    0x40004C00,
    0x40004C01,
    0x40004C20,
    0x40004C21,
    0x40004C40,
    0x40004C41,
    0x40004C60,
    0x40004C61,
    0x40004C80,
    0x40004C81,
    0x40004D20
};
                                                // <-- E9
/*****************************************************************************
 * Function: GPIO_PIN_IN
 * Preconditions: PUERTO1 SELECCIONADO.
 * Overview: LEE EL PIN DESEADO
 * Input: pin_.
 * Output: 0/1
 *****************************************************************************/
void Ejercicio_9(){

    /************************************************
            CONFIGURACION DE GPIO
        ************************************************/
        GPIO_setPinEntradaconPullUp(PUERTO1, BOTON1 | BOTON4);                 //PIN P1.1 y P1.4 COMO ENTRADA

        GPIO_setPinSalida(PUERTO2, LEDROJO | LEDVERDE | LEDAZUL);   // CONFIGURA PINES 2.0,2.1,2.2  COMO SALIDA (LEDS RGB)"
        GPIO_setPinBajo(PUERTO2, LEDROJO | LEDVERDE | LEDAZUL);      // APAGADOS

        GPIO_setPinSalida(PUERTO1, LED);   // CONFIGURA PINES 1.0 COMO SALIDA (LED rojo)"
        GPIO_setPinBajo(PUERTO1, LED);      // APAGADOS
}

uint8_t Gpio_Pin_in( uint_fast16_t pin_)
{
    uint_fast16_t inputPinValue;
    inputPinValue = PUERTO_P1->IN & (pin_);         // LEE EL REGISTRO QUE INDICA EL VALOR DE ENTRADA DE UN PIN
    if (inputPinValue > 0)                          // RETORNA EL VALOR 1 o 0
        return (0x01);
    return (0x00);
}

uint8_t Gpio_Pin_in_P2( uint_fast16_t pin_)
{
    uint_fast16_t inputPinValue;
    inputPinValue = PUERTO_P2->IN & (pin_);         // LEE EL REGISTRO QUE INDICA EL VALOR DE ENTRADA DE UN PIN
    if (inputPinValue > 0)                          // RETORNA EL VALOR 1 o 0
        return (0x01);
    return (0x00);
}
                                                   // <-- E8

/******************************************************************************
 * Function: GPIO_setPinSalida
 * Preconditions: None.
 * Overview: Configura el Pin(es) del Puerto seleccionado como salida.
 * Input: Puerto (i.e 2), Pin (i.e BIT0), estado.
 * Output: None.
 *
 *****************************************************************************/
void GPIO_setPinSalida(uint_fast8_t selectedPort, uint_fast8_t selectedPins)
{

    uint32_t baseAddress = GPIO_PORT_TO_BASE[selectedPort];
    if(selectedPort % 2 == 0)                                                   // SI ES PUERTO PAR
    {
        baseAddress--;                                                          // SE LE RESTA 1 PARA QUE TENGA LA MISMA DIRECCION BASE QUE PUERTO IMPAR
        Struct_Puerto_par * const Puerto_par = (Struct_Puerto_par *) baseAddress;     // YA QUE LA ESTRUCTURA SE ENCARGA DE HACER EL OFFSET A LOS REGISTROS
        Puerto_par->SEL0 &= ~selectedPins;
        Puerto_par->SEL1 &= ~selectedPins;
        Puerto_par->DIR |= selectedPins;
    }
    else                                                                       // SI ES PUERTO IMPAR
    {
        Struct_Puerto_impar * const Puerto_impar = (Struct_Puerto_impar *) baseAddress ;
        Puerto_impar->SEL0 &= ~selectedPins;
        Puerto_impar->SEL1 &= ~selectedPins;
        Puerto_impar->DIR |= selectedPins;
    }

}
/******************************************************************************
 * Function: GPIO_setPinEntradaconPullUp
 * Preconditions: None.
 * Overview: Configura el Pin(es) del Puerto seleccionado como entrada y pone PullUp.
 * Input: Puerto (i.e 2), Pin (i.e BIT0), estado.
 * Output: None.
 *
 *****************************************************************************/
void GPIO_setPinEntradaconPullUp(uint_fast8_t selectedPort,
        uint_fast16_t selectedPins)
{

    uint32_t baseAddress = GPIO_PORT_TO_BASE[selectedPort];
    if(selectedPort % 2 == 0)                                                   // SI ES PUERTO PAR
    {
        baseAddress--;                                                          // SE LE RESTA 1 PARA QUE TENGA LA MISMA DIRECCION BASE QUE PUERTO IMPAR
        Struct_Puerto_par * const Puerto_par = (Struct_Puerto_par *) baseAddress;     // YA QUE LA ESTRUCTURA SE ENCARGA DE HACER EL OFFSET A LOS REGISTROS
        Puerto_par->SEL0 &= ~selectedPins;
        Puerto_par->SEL1 &= ~selectedPins;
        Puerto_par->DIR  &= ~selectedPins;
        Puerto_par->REN  |= selectedPins;
        Puerto_par->OUT  |= selectedPins;
    }
    else                                                                       // SI ES PUERTO IMPAR
    {
        Struct_Puerto_impar * const Puerto_impar = (Struct_Puerto_impar *) baseAddress ;
        Puerto_impar->SEL0 &= ~selectedPins;
        Puerto_impar->SEL1 &= ~selectedPins;
        Puerto_impar->DIR  &= ~selectedPins;
        Puerto_impar->REN  |= selectedPins;
        Puerto_impar->OUT  |= selectedPins;
    }
}
/******************************************************************************
 * Function: GPIO_setPinLow
 * Preconditions: GPIO_setPinSalida.
 * Overview: Establece el Pin(es) del Puerto seleccionado en bajo.
 * Input: Puerto (i.e 2), Pin (i.e BIT0), estado.
 * Output: None.
 *
 *****************************************************************************/
void GPIO_setPinBajo(uint_fast8_t selectedPort,
        uint_fast16_t selectedPins)
{
    uint32_t baseAddress = GPIO_PORT_TO_BASE[selectedPort];
    if(selectedPort % 2 == 0)                                                   // SI ES PUERTO PAR
    {
        baseAddress--;                                                          // SE LE RESTA 1 PARA QUE TENGA LA MISMA DIRECCION BASE QUE PUERTO IMPAR
        Struct_Puerto_par * const Puerto_par = (Struct_Puerto_par *) baseAddress;     // YA QUE LA ESTRUCTURA SE ENCARGA DE HACER EL OFFSET A LOS REGISTROS
        Puerto_par->OUT &= ~selectedPins;
    }
    else                                                                       // SI ES PUERTO IMPAR
    {
        Struct_Puerto_impar * const Puerto_impar = (Struct_Puerto_impar *) baseAddress ;
        Puerto_impar->OUT &= ~selectedPins;
    }
}
/******************************************************************************
 * Function: GPIO_setPinHigh
 * Preconditions: GPIO_setPinSalida.
 * Overview: Establece el Pin(es) del Puerto seleccionado en alto.
 * Input: Puerto (i.e 2), Pin (i.e BIT0), estado.
 * Output: None.
 *
 *****************************************************************************/
void GPIO_setPinAlto(uint_fast8_t selectedPort, uint_fast16_t selectedPins)
{
    uint32_t baseAddress = GPIO_PORT_TO_BASE[selectedPort];
    if(selectedPort % 2 == 0)                                                   // SI ES PUERTO PAR
    {
        baseAddress--;                                                          // SE LE RESTA 1 PARA QUE TENGA LA MISMA DIRECCION BASE QUE PUERTO IMPAR
        Struct_Puerto_par * const Puerto_par = (Struct_Puerto_par *) baseAddress;     // YA QUE LA ESTRUCTURA SE ENCARGA DE HACER EL OFFSET A LOS REGISTROS
        Puerto_par->OUT  |= selectedPins;
    }
    else                                                                       // SI ES PUERTO IMPAR
    {
        Struct_Puerto_impar * const Puerto_impar = (Struct_Puerto_impar *) baseAddress ;
        Puerto_impar->OUT  |= selectedPins;
    }
}
/******************************************************************************
 * Function: GPIO_getPinValor
 * Preconditions: GPIO_setPinEntradaconPullUp.
 * Overview: Obtiene el valor del Pin(es) del Puerto seleccionado.
 * Input: Puerto (i.e 2), Pin (i.e BIT0), estado.
 * Output: None.
 *
 *****************************************************************************/
uint8_t GPIO_getPinValor(uint_fast8_t selectedPort,  uint_fast16_t selectedPins)
{
    uint_fast16_t inputPinValue;

    uint32_t baseAddress = GPIO_PORT_TO_BASE[selectedPort];
    if(selectedPort % 2 == 0)                                                   // SI ES PUERTO PAR
    {
        baseAddress--;                                                          // SE LE RESTA 1 PARA QUE TENGA LA MISMA DIRECCION BASE QUE PUERTO IMPAR
        Struct_Puerto_par * const Puerto_par = (Struct_Puerto_par *) baseAddress;     // YA QUE LA ESTRUCTURA SE ENCARGA DE HACER EL OFFSET A LOS REGISTROS
        inputPinValue = Puerto_par->IN & (selectedPins);
    }
    else                                                                       // SI ES PUERTO IMPAR
    {
        Struct_Puerto_impar * const Puerto_impar = (Struct_Puerto_impar *) baseAddress ;
        inputPinValue = Puerto_impar->IN & (selectedPins);
    }
    if (inputPinValue > 0)
        return GPIO_INPUT_PIN_HIGH;
    return GPIO_INPUT_PIN_LOW;
}
