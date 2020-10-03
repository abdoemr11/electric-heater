/* In this source file we all intialize various component and PORTS*/
#include "Port.h"
#include "adc.h"
#include "i2c.h"
#include "eeprom_ext.h"
#include "Crude_OS.h"
#include "global_var.h"
void init_all(void)
{ 
    TRISB = 0; 
    TRISC = 0x00;
    //PORTB = 0;
    //In_Sett_Mode = 1;
    sev_seg_on = 1;
    i2c_init();
    tick_init();
    adc_init();
    //<--------------Initializing ports ----->
    //initializing switch
    On_Off_Sw_TRIS = 1;
    Up_Temp_Sw_TRIS = 1;
    Down_Temp_Sw_TRIS = 1;
    //initializing led
    Heat_Led_Indicator_TRIS = 0;
    //initializing seven segment
    Sev_Seg_TRIS = 0x00;
    Sev_Seg_Low_TRIS = 0;
    Sev_Seg_High_TRIS = 0;
    //initializing heat element & cool 
    Heater_Elem_TRIS = 0;
    Cooler_Elem_TRIS = 0;
    //initializing sensor 
    Heat_Sensor_TRIS = 1;
    //PORTB = 0;
    
    //unsigned char del ;
    //for ( del = 0; del < 40; del++)
     //   e2pext_w(del, 0x00);
}
