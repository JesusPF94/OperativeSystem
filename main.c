/*
 * File:   OSMain.c
 * Author: David
 *
 * Created on 16 de enero de 2016, 10:40
 */


#include <xc.h>
#include <pic18f4455.h>
#include "Structure.h"
#include <stdio.h>

void low_priority interrupt Low_Priority_Interrupt(void) {
    FunctionA();
    FunctionB();
    FunctionC();
    FunctionD();
    FunctionE();
}


void high_priority interrupt High_Priority_Interrupt(void){
    INTCON &=  0xFD;
    asm("nop");
    xInterruptTaskCreate(&FunctionE,6,0);
    asm("nop");

}



void main(void) {
    asm("nop");
    asm("nop");
    OSInit();
    GIE=ON;
   //INT0IE_bit = 1;
    xTaskCreate(&FunctionA,0,10); 

    //INTCON |=  0x12;
    asm("nop");
    xTaskCreate(&FunctionA,0,10); 
        asm("nop");


    do{
        asm("nop");
    }while(1);    
    return;
}
