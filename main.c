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
    //unsigned int* pc3=0xFF9,            pc2=0xFFA,            pc1=0xFFB;
    //funcionMLP();
   // WA_method();
    //WA++;
  //  pc1 = (&FunctionA & 0x000000ff);
  //  pc2=(&FunctionA & 0x0000ff00) >> 8;
  //  pc3=(&FunctionA & 0x00ff0000) >> 16;
//    PCLAT = &FunctionA ;       
    asm("nop");
    asm("nop");
    OSInit();
    GIE=ON;
   //INT0IE_bit = 1;
    
    INTCON |=  0x12;
    asm("nop");
    xTaskCreate(&FunctionA,0,0); 
    
   // FunctionA();
    return;
}
