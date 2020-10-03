
#include<xc.h>
#include "Crude_OS.h"
#include "Tasks.h"
#include "global_var.h"
#define SBIT_PS1  5
#define SBIT_PS0  4

void __interrupt() timer_isr()
{  
    if(TMR1IF==1)
    {
    TMR1H=0xE7;     // Load the time value(0xBDC) for 100ms delay
    TMR1L=0x96;       
    periodic_task_update();
        TMR1IF=0;       // Clear timer interrupt flag
    } 
}


void tick_init()
{    

    T1CON = (1<<SBIT_PS1) | (1<<SBIT_PS0); // Timer1 
    TMR1H=0xE7;     //  for 100ms delay
    TMR1L=0x96;       
    TMR1IE=1;       //Enable timer interrupt bit in PIE1 register
    GIE=1;          //Enable Global Interrupt
    PEIE=1;         //Enable the Peripheral Interrupt

}

void periodic_task_update()
{ 
    if(On_Stat)
    {
        temp_control(); 
        heat_element_indicator();
        sev_seg_disp();
    }
}

void tick_start()
{ 
    TMR1ON = 1;     //Start Timer1    
}
void tick_stop()
{ 
    TMR1ON = 0;     //Start Timer1    
}
