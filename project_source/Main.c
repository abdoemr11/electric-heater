#include "config_877A.h"
#include <xc.h>
#include "Init.h"
#include "global_var.h"
#include "Tasks.h"
#include "Crude_OS.h"
#include "eeprom_ext.h"


int main()
{ 
    //Initialize all module and component
    init_all();
    //Start Crude_OS tick
    tick_start();
    while(1)
    { 
        while(On_Stat)
        {
            on_off_toggle();
            temp_setting();
        }
        tick_stop();
        In_Sett_Mode = 0;
        while (!On_Stat)
        {
             off_stat_action();
            on_off_toggle();
        }
        get_data_from_eprom();
        tick_start();
    }
    return 0;
}
