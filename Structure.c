#include "Structure.h"

//#define TASKPOSITION unsigned char 

static unsigned char taskPosition=0;
static unsigned char actualPosition=0;           //This is the indexOf the process executing
static unsigned char schedulerAdd1=0;
static unsigned char schedulerAdd2=0;
static unsigned char schedulerAdd3=0;
static unsigned char schedulerStatus;

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
    //HEre we save the lastest current PC
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
    if(TaskArray[actualPosition].Priority >= Prior){
        TaskArray[actualPosition].currentAdd3=TOSU;
        TaskArray[actualPosition].currentAdd2=TOSH;
        TaskArray[actualPosition].currentAdd1=TOSL;
    }
    OSRun();
}

void vTaskDelete(void){
    TaskArray[actualPosition].state=SUSPEND;
   // PCLATU = TaskArray[schedulerAdd3].currentAdd3;                  //Regresamos al Scheduler en posición más alta.
   // PCLATH = TaskArray[schedulerAdd2].currentAdd2;                 //Scheduler posición de enmedio.
    OSRun();
   // STKPTR -= 3;
   // PCL = TaskArray[schedulerAdd1].currentAdd1;
    //Here we should adjust the }

}

void OSInit(){
    unsigned char i;
    for(i=0;i<TASKNUMBER ; i++){
        TaskArray[i].Priority=255;
        TaskArray[i].Id=i;
        TaskArray[i].state=SUSPEND;
    }

}


void OSRun(void){
    if(schedulerStatus=ON){    
    unsigned char index=0,
                  i;
    unsigned char minPrior=255;
    
    for(i=0;i<TASKNUMBER ; i++){
        if(TaskArray[i].Priority < minPrior && (TaskArray[i].state==READY||TaskArray[i].state==RUNNING)){
            index=i;
            minPrior = TaskArray[index].Priority;
        } 
    }
     
       TaskArray[index].state=RUNNING; 
       STKPTR++;                                    //Each time we jump to osRun, the previous PC is saved into the stack, to prevent overflow make adjust
       actualPosition=index;
       PCLATU = TaskArray[index].currentAdd3;
       PCLATH = TaskArray[index].currentAdd2;         //Here we should jump
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
    xTaskCreate(FunctionE,0,2);
    asm("nop");
    vTaskDelete();
    
}

void FunctionC(void){
    asm("nop");
    asm("nop");
    xTaskCreate(FunctionD,2,4);
    asm("nop");
    asm("nop");
    vTaskDelete();
}

void FunctionB(void){
    asm("nop");
    asm("nop");
    xTaskCreate(FunctionC,7,10);
    vTaskDelete(); 
}

void FunctionA(void){
    asm("nop");
    asm("nop");
    asm("nop");
    xTaskCreate(FunctionB,4,12);
    asm("nop");
    asm("nop");
    vTaskDelete();
}
