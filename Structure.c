#include "Structure.h"

//#define TASKPOSITION unsigned char 

static unsigned char taskPosition=0;
static unsigned char actualPosition=10;           //This is the indexOf the process executing
static unsigned char schedulerAdd1=0;
static unsigned char schedulerAdd2=0;
static unsigned char schedulerAdd3=0;
static unsigned char schedulerStatus;

//Global modifications
static unsigned char i;
static unsigned char index=0;
static unsigned char minPrior=255;

struct Task{
    unsigned char Add1;
    unsigned char Add2;                          //This is where it starts
    unsigned char Add3;
    unsigned char state;
    unsigned char Id;                           //THIS IS THE SAME AS THE INDEX
    unsigned char Priority;
    unsigned char currentAdd1;
    unsigned char currentAdd2;                    //donde se quedo
    unsigned char currentAdd3;  
};

struct Task TaskArray[TASKNUMBER];

void xTaskCreate(unsigned long pvTaskCode, unsigned char Id, unsigned char Prior){
    GIE = OFF;
    //HEre we save the lastest current PC
     TaskArray[actualPosition].currentAdd3=TOSU;
     TaskArray[actualPosition].currentAdd2=TOSH;
     TaskArray[actualPosition].currentAdd1=TOSL;
    
    taskPosition=Id;
    TaskArray[taskPosition].Id=Id;
    TaskArray[taskPosition].state=READY;
    TaskArray[taskPosition].Add3=(pvTaskCode & 0x00ff0000) >> 16;
    TaskArray[taskPosition].Add2=(pvTaskCode & 0x0000ff00) >> 8;
    TaskArray[taskPosition].Add1=(pvTaskCode & 0x000000ff);
    TaskArray[taskPosition].currentAdd3=(pvTaskCode & 0x00ff0000) >> 16;
    TaskArray[taskPosition].currentAdd2=(pvTaskCode & 0x0000ff00) >> 8;
    TaskArray[taskPosition].currentAdd1=(pvTaskCode & 0x000000ff);
    TaskArray[taskPosition].Priority=Prior;
   // if(TaskArray[actualPosition].Priority >= Prior){
       
   // }
    STKPTR--;
    OSRun();
}

void xInterruptTaskCreate(unsigned long pvTaskCode, unsigned char Id, unsigned char Prior){
    GIE = OFF;
    TaskArray[actualPosition].currentAdd3=TOSU;
    TaskArray[actualPosition].currentAdd2=TOSH;
    TaskArray[actualPosition].currentAdd1=TOSL;
    //HEre we save the lastest current PC
    TaskArray[Id].Id=Id;
    TaskArray[Id].state=READY;
    TaskArray[Id].Add3=(pvTaskCode & 0x00ff0000) >> 16;
    TaskArray[Id].Add2=(pvTaskCode & 0x0000ff00) >> 8;
    TaskArray[Id].Add1=(pvTaskCode & 0x000000ff);
    TaskArray[Id].currentAdd3=(pvTaskCode & 0x00ff0000) >> 16;
    TaskArray[Id].currentAdd2=(pvTaskCode & 0x0000ff00) >> 8;
    TaskArray[Id].currentAdd1=(pvTaskCode & 0x000000ff);
    TaskArray[Id].Priority=Prior;
 /*   if(TaskArray[actualPosition].Priority >= Prior    && TaskArray[actualPosition].state == RUNNING){
        TaskArray[actualPosition].currentAdd3=TOSU;
        TaskArray[actualPosition].currentAdd2=TOSH;
        TaskArray[actualPosition].currentAdd1=TOSL;
    }*/
    STKPTR--;
    OSRun();
}


void vTaskDelete(void){
    GIE = OFF;
    TaskArray[actualPosition].state=SUSPEND;
   // PCLATU = TaskArray[schedulerAdd3].currentAdd3;                  //Regresamos al Scheduler en posición más alta.
   // PCLATH = TaskArray[schedulerAdd2].currentAdd2;                 //Scheduler posición de enmedio.
   STKPTR--;
    OSRun();
   // STKPTR -= 3;
   // PCL = TaskArray[schedulerAdd1].currentAdd1;
    //Here we should adjust the }

}

void OSInit(){
    for(i=0;i<TASKNUMBER ; i++){
        TaskArray[i].Priority=255;
        TaskArray[i].Id=i;
        TaskArray[i].state=SUSPEND;
    }

}


void OSRun(void){
    index = 10;
    minPrior = 255;
    if(schedulerStatus=ON){    
    for(i=0;i<TASKNUMBER ; i++){
        if(TaskArray[i].Priority < minPrior && (TaskArray[i].state==READY||TaskArray[i].state==RUNNING)){
            index=i;
            minPrior = TaskArray[index].Priority;
        } 
    }
  //  if(index == 10){
        
   // } 
       TaskArray[index].state=RUNNING; 
       STKPTR--;                                    //Each time we jump to osRun, the previous PC is saved into the stack, to prevent overflow make adjust
       actualPosition=index;
       PCLATU = TaskArray[index].currentAdd3;
       PCLATH = TaskArray[index].currentAdd2;         //Here we should jump
       GIE = ON;
       PCL = TaskArray[index].currentAdd1;    
    //we save the pc which is pointing the following app, we increase it by two to point 
    //here we jump to the next task  

    }
}

/*void vTaskStartScheduler(void){
    
}*/

void FunctionE(void){
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    vTaskDelete();
    
}

void FunctionD(void){
    asm("nop");
    asm("nop");
    asm("nop");
  //  xTaskCreate(FunctionE,4,7);
    asm("nop");
    vTaskDelete();
    
}

void FunctionC(void){
    asm("nop");
    asm("nop");
    xTaskCreate(FunctionD,3,7);
    asm("nop");
    asm("nop");
    vTaskDelete();
}

void FunctionB(void){
    asm("nop");
    asm("nop");
    INTCON |=  0x12;
    xTaskCreate(FunctionC,2,8);
    vTaskDelete(); 
}

void FunctionA(void){
    asm("nop");
    asm("nop");
    asm("nop");
    xTaskCreate(FunctionB,1,9);
    asm("nop");
    asm("nop");
    vTaskDelete();
}
