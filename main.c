/**********************************************************
 * FileName:        main.c
 * Dependencies:    msp.h, stdint.h
 * Processor:       MSP432
 * Board:           MSP432P401R
 * Program version: CCS V10 TI
 * Company:         TecNM /IT Chihuahua
 * Description:     ACCESO A MEMORIA DE REGISTROS DE PERIFERICO GPIO CON "ESTRUCTURAS_V2"
 * Authors:         ALFREDO CHACON
 * Updated:         03/2021
 * Nota: no se están usando las estructuras definidas en los sorucefiles dados por el BSP de TI, Aqui se declran las estructuras
 *       los punteros declarados se incializan con las direcciones de memoria de los registros de los perifericos en cuestión
 * Created on: 6 oct. 2021
 * updated: 20/11/2021
 **************************************************/

/************************************************************************************************
 * * Copyright (C) 2021 by Alfredo Chacon - TecNM /IT Chihuahua
 *
 * Se permite la redistribución, modificación o uso de este software en formato fuente o binario
 * siempre que los archivos mantengan estos derechos de autor.
 * Los usuarios pueden modificar esto y usarlo para aprender sobre el campo de software embebido.
 * Alfredo Chacon y el TecNM /IT Chihuahua no son responsables del mal uso de este material.
 *************************************************************************************************/
/************************************************
  HEADER FILES
 ************************************************/
#include<stdint.h>
#include "msp.h"
#include "DRIVERS\BSP.h"

void main(void)
{
    /************************************************
              DECLARACION DE VARIABLES
     ************************************************/
    uint32_t i;
    uint8_t bandera = 0;

    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;           // DETIENE EL TIMER DEL WATCHDOG

    //Inicializacion de E/S
        /************************************************
                CONFIGURACION DE GPIO
            ************************************************/
            GPIO_setPinEntradaconPullUp(GPIO_PORT_P1 , 0x0002 | 0x0010);                 //PIN P1.1 y P1.4 COMO ENTRADA

            GPIO_setPinSalida(GPIO_PORT_P2, 0x0001 | 0x0002 | 0x0004);   // CONFIGURA PINES 2.0,2.1,2.2  COMO SALIDA (LEDS RGB)"
            GPIO_setPinBajo(GPIO_PORT_P2, 0x0001 | 0x0002 | 0x0004);      // APAGADOS

            GPIO_setPinSalida(GPIO_PORT_P1, GPIO_PIN0);   // CONFIGURA PINES 1.0 COMO SALIDA (LED rojo)"
            GPIO_setPinBajo(GPIO_PORT_P1, GPIO_PIN0);      // APAGADOS



    while(1)
    {

        if ( Gpio_Pin_in(0x0010) != 1)                // ENTRA AL PRESIONAR EL SWITCH DEL PUERTO P1.4 (CUANDO ESTA EN BAJO)
                {
                GPIO_setPinBajo(GPIO_PORT_P1,0x0001);
                GPIO_setPinBajo(GPIO_PORT_P2, 0x0001 | 0x0002 | 0x0004);
                    if(bandera == FALSE)
                        {
                            bandera = TRUE;                                //BANDERA EN ALTO
                            while (bandera==TRUE){
                                GPIO_setPinAlto(GPIO_PORT_P1,0x0001);    //ENCIENDE LED
                                for(i=RETARDO; i>0 ;i--);
                                GPIO_setPinBajo(GPIO_PORT_P1, 0x0001);    //APAGA LED
                                for(i=RETARDO; i>0 ;i--);
                                if ( Gpio_Pin_in(0x0010) != 1) bandera=FALSE;    // ENTRA CUANDO PRESIONAMOS BOTON DE P1.4
                             while( Gpio_Pin_in(0x0010) != 1);                //MIENTRAS ESTE PRESIONADO EL BOTON
                            }
                        }
                 GPIO_setPinBajo(GPIO_PORT_P1, GPIO_PIN0);  //APAGA TODOS
                }
        if ( Gpio_Pin_in(0x0002) != 1)                // ENTRA AL PRESIONAR EL SWITCH DEL PUERTO P1.1 (CUANDO ESTA EN BAJO)
                        {
                            GPIO_setPinBajo(GPIO_PORT_P1, 0x0001);
                            GPIO_setPinBajo(GPIO_PORT_P2,0x0001 | 0x0002 | 0x0004);
                            if(bandera == FALSE)
                                {
                                    bandera = TRUE;                                 //BANDERA EN ALTO
                                    while (bandera==TRUE){
                                        GPIO_setPinBajo(GPIO_PORT_P2 , 0x0004);    //APAGA BLUE
                                        GPIO_setPinAlto(GPIO_PORT_P2 ,0x0001);    //ENCIENDE RED
                                        for(i=RETARDO; i>0 ;i--);
                                        GPIO_setPinBajo (GPIO_PORT_P2 , 0x0001);    //APAGA RED
                                        GPIO_setPinAlto(GPIO_PORT_P2 ,0x0002);    //ENCIENDE GREEN
                                        for(i=RETARDO; i>0 ;i--);
                                        GPIO_setPinBajo(GPIO_PORT_P2 , 0x0002);    //APAGA GREEN
                                        GPIO_setPinAlto( GPIO_PORT_P2, 0x0004);    //ENCIENDE BLUE
                                        for(i=RETARDO; i>0 ;i--);
                                     if ( Gpio_Pin_in(0x0002) != 1) bandera=FALSE;    // ENTRA CUANDO PRESIONAMOS BOTON DE P1.1
                                     while( Gpio_Pin_in(0x0002) != 1);                //MIENTRAS ESTE PRESIONADO EL BOTON
                                    }
                                }
                         GPIO_setPinBajo(GPIO_PORT_P2, 0x0001 | 0x0002 | 0x0004);  //APAGA TODOS
                        }
        for(i=RETARDO; i>0 ;i--);

    }

}
