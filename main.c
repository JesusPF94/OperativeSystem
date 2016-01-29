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
    xInterruptTaskCreate(&FunctionE,0,15);
    asm("nop");

}



void main(void) {
    asm("nop");
    asm("nop");
    OSInit();
    GIE=ON;
   //INT0IE_bit = 1;
    
    //INTCON |=  0x12;
    asm("nop");
    xTaskCreate(&FunctionA,9,0); 
        asm("nop");

   // FunctionA();
    return;
}
