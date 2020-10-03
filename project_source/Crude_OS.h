
#include<xc.h>

//uint8_t Tick_Sens;
//char value = 0;
#define SBIT_PS1  5
#define SBIT_PS0  4
void __interrupt() timer_isr();
void tick_init();
void periodic_task_update();
void tick_start();
void tick_stop();
