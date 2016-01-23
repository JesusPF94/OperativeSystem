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

void FunctionD(void){
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    vTaskDelete();
    
}

void FunctionC(void){
    asm("nop");
    asm("nop");
    xTaskCreate(&FunctionD,2,4);
    asm("nop");
    asm("nop");
    vTaskDelete();
}

void FunctionB(void){
    asm("nop");
    asm("nop");
    xTaskCreate(&FunctionC,7,10);
    asm("nop");
    asm("nop");
    vTaskDelete();    
}

void FunctionA(void){
    asm("nop");
    asm("nop");
    asm("nop");
    xTaskCreate(&FunctionB,4,12);
    asm("nop");
    asm("nop");
    vTaskDelete();
}

void main(void) {
    unsigned long a;
    a = &FunctionA;
    asm("nop");
    asm("nop");
    OSInit();
    xTaskCreate(a,1,15);    //TESTTTTTTTTTT Fakin git lo odio
    do{
        OSRun();
        asm("clrwdt");
    }while(1);
    return;
}
