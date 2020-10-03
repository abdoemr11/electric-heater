#include "Tasks.h"
#include "adc.h"
#include "global_var.h"
#include "Port.h"
#include "xc.h"
#include "eeprom_ext.h"
#include "display7s.h"
#include "Crude_OS.h"
unsigned char Tick_Sens;

unsigned int Cur_Tmp; 
unsigned char Wanted_Tmp ; 
unsigned char temps[10];
unsigned char tmpL, tmpH;
    unsigned char dull;
//***************************************
unsigned char Tick_Sens = 0;
unsigned char Tick_Sens_Read = 0;
unsigned char Tick_Heat_Element = 0;
unsigned char Tick_Sev_Seg = 0;
unsigned int Tick_Sett_mode_Time = 0;
unsigned char Tick_On_Off;
unsigned char  Delay_On_Off_Tick;
/****************************************/
__bit In_Sett_Mode = 0;
__bit On_Stat = 0;
__bit Heat_Element_On = 0;
__bit Cool_Element_On = 0;
__bit sev_seg_on = 0;
__bit is_low_seg = 0;

/****************************************/
unsigned char get_temp_from_sensor()
{ 
    //get this value from LM35 data sheet
  return adc_amostra(2) * .489;
}
void temp_control()
{ 
    //get the temperature every 100ms (10 * 10ms)
    if (Tick_Sens>= Max_Sensor_Tick)     
    { 
        temps[Tick_Sens_Read++] = get_temp_from_sensor();
        Tick_Sens = 0;
    }
    else 
    { 
        Tick_Sens++;
    }
    if (Tick_Sens_Read >= Max_Sensor_Tick_Read)
    { 
          
        //calculate the average temperature then 
        // enable or disable the heating element or cooling element 
        Tick_Sens = 0;
        Tick_Sens_Read = 0;
        Cur_Tmp = 0; 
        unsigned char i = 0;
        for (;i <10; i++)
        { 
            Cur_Tmp += temps[i];  
        }
        Cur_Tmp = Cur_Tmp /10;
        //call temperature checker and act based on the value of the current temperature
        temp_checker();
    }


}
void my_delay()
{ 
    unsigned char i;  
    unsigned char j; 
    for(i = 0; i <250; i++)
    { 
        for(j = 0; j <250; j++)
        { 
            asm("NOP");
        }

    }
}
void temp_setting()
{ 
    if(In_Sett_Mode)
    { 
        if(!Up_Temp_Sw&& Wanted_Tmp<MaxTmp) 
        { 
            my_delay();
            //increase the wanted temperature   
            Wanted_Tmp += 5;
            Tick_Sett_mode_Time = 0;
        }
        else if(!Down_Temp_Sw&& Wanted_Tmp > MinTmp) 
        { 
            my_delay();
            //decrease the wanted temperature   
            Wanted_Tmp -= 5;
            Tick_Sett_mode_Time = 0;
        }
        else 
        { 
            //  
        }
    }
    else if(!Up_Temp_Sw || !Down_Temp_Sw) 
    { 
        my_delay();
        In_Sett_Mode = 1;  //we will exit temperature setting mode in seven seg
        Tick_Sett_mode_Time = 0;
        Wanted_Tmp = 60; // the intial setting temperature is 60
    }
}
__bit delay_on_off_toggle()
{ 
    if(Delay_On_Off_Tick++ >50) 
    {
        Delay_On_Off_Tick = 0;
        return 1;
        
    }
    else 
        return 0;
}
__bit Can_Press;
void on_off_toggle()
{ 
    
    if(!On_Off_Sw && !Can_Press)  

    {
        Can_Press = 1;
            //unsigned char dul2;
      //for(dull = 0; dull< 250; dull++)
      //{ 
      //    for(dul2 = 0; dul2 < 250; dul2++)
      //    { 
      //         asm("NOP");
      //    }
      //}
       // tick_stop();
        //if(delay_on_off_toggle())
            //tick_stop();
    }
    if(Can_Press)
    { 
          
        my_delay();
        On_Stat = !On_Stat;
        Tick_On_Off = 0;
        Can_Press = 0;
    }
}
void temp_checker()
{ 
    if (Cur_Tmp < (Wanted_Tmp - 5))
    { 
          
        Heater_Elem_Pin = 1;
        Heat_Element_On = 1;
        //Cool_Element_On = 1;
        //Cooler_Elem_Pin = 1;
    }
    else if (Cur_Tmp > (Wanted_Tmp + 5))
    { 
        Heater_Elem_Pin = 0;
        Heat_Element_On = 0;
    }
    if (Cur_Tmp > (Wanted_Tmp + 5))
    { 
        Cool_Element_On = 1;
        Cooler_Elem_Pin = 1;
    }
    else if (Cur_Tmp < (Wanted_Tmp - 5))
    { 
        Cool_Element_On = 0;
        Cooler_Elem_Pin = 0;
    }
}
void heat_element_indicator()
{ 
    if(Heat_Element_On)  
    { 
        //blink Heat element led every 1 sec
        if(Tick_Heat_Element++ >= Max_Heat_Tick )
        { 
            //make the  LED toggle action 
            Tick_Heat_Element = 0;
            Heat_Led_Indicator = !Heat_Led_Indicator;
        }
    }
    else if (Cool_Element_On)
    { 
        //make the heat element  LED on   
        Tick_Heat_Element = 0;
        Heat_Led_Indicator = 1;
    }
    else 
    { 
        //turn off the heat indicator led   
        Tick_Heat_Element = 0;
        Heat_Led_Indicator = 0;
    }
}
void sev_seg_disp()
{
    if(In_Sett_Mode)  
    { 
        //display the Wanted temperature
        //make the seven segment display blink
        Tick_Sev_Seg++;  
        sev_seg_action(Wanted_Tmp);
        if(Tick_Sev_Seg >= Max_Sev_Seg_Tick)
        { 
            Tick_Sett_mode_Time++;
            Tick_Sev_Seg = 0;
            sev_seg_on = !sev_seg_on;
        }
        if(Tick_Sett_mode_Time >= Max_Tmp_Stt_Time)
        { 
            //exit the temperature setting mode   
            //Save the Wanting temperature in the eprom 
            In_Sett_Mode = 0;
            Tick_Sev_Seg = 0;
            //set_data_to_eprom(); // this function that cause the problem
            sev_seg_on = 1; 
            //On_Stat = 1;
            e2pext_w(E2PROM_ADDR, Wanted_Tmp);
        }
    }
    else 
    { 
        //make the seven segment display the current temperature  
        sev_seg_on = 1; 
        sev_seg_action(Cur_Tmp);
        On_Stat = 1;
    }
        //sev_seg_action(Cur_Tmp);
}
void sev_seg_action(unsigned char tmp)
{ 
    tmpL = tmp % 10; //to obtain the low digit 
    tmpH = tmp /10; // to obtain the high digit
    if(sev_seg_on)
    {
        if(is_low_seg)
        { 
            Sev_Seg_High_Pin = 0;
            Sev_Seg_Low_Pin = 1;
            Sev_Seg_PORT = display7s(tmpL);
        }
        else 
        {
            Sev_Seg_Low_Pin = 0;
            Sev_Seg_High_Pin = 1;
            Sev_Seg_PORT = display7s(tmpH);
        }
        is_low_seg = !is_low_seg;
        }
    else 
        Sev_Seg_PORT = 0;
}

void clear_disp()
{ 
    Sev_Seg_PORT = 0;  
    //and every led
}
void off_stat_action()
{ 
    Sev_Seg_PORT = 0;  
    Heat_Led_Indicator = 0;
    Heater_Elem_Pin = 0;
    Cool_Element_On = 0;
}
void get_data_from_eprom()
{ 
      Wanted_Tmp = e2pext_r(E2PROM_ADDR);
      if(Wanted_Tmp < 20) // this check to avoid worst case when it fail to obtain the data from the eeprom
          Wanted_Tmp = 60;
}
void set_data_to_eprom()
{ 
    e2pext_w(E2PROM_ADDR, Wanted_Tmp);
}
