#ifndef GLOBAL_VAR_H
#define GLOBAL_VAR_H
extern unsigned int Cur_Tmp;
extern unsigned char Wanted_Tmp;
//*****************Variable that hold task ticks************
extern unsigned char Tick_Sens;
extern unsigned char Tick_Sens_Read;
extern unsigned char Tick_Heat_Element;
extern unsigned char Tick_Sev_Seg;
extern unsigned int Tick_Sett_mode_Time;

//**********************************************************
extern __bit In_Sett_Mode;
extern __bit On_Stat;
extern __bit Heat_Element_On;
extern __bit Cool_Element_On;
extern __bit sev_seg_on;
#define MaxTmp (75)
#define MinTmp (35)
#define Max_Sensor_Tick (10)
#define Max_Sensor_Tick_Read (10)
#define Max_Heat_Tick (100)//this is used to determine Tick elapsed before heat led toggle 
#define Max_Sev_Seg_Tick  (100)// elapsed Ticks before seven segment toggle
#define Max_Tmp_Stt_Time (5)// elapsed Tick before leaving temperature setting mode
#define E2PROM_ADDR (0)
#endif 

