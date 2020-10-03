//in this source file we will abstract port that we will connected to e
//external peripheral 
#ifndef PORT_H
#define PORT_H

#define On_Off_Sw PORTBbits.RB3 //this button will use to toggle the board between on and off state
#define On_Off_Sw_TRIS TRISBbits.TRISB3
#define Up_Temp_Sw  PORTBbits.RB4 //this button will use to enter to temperature setting mode or increase the Wanted Temp
#define Up_Temp_Sw_TRIS TRISBbits.TRISB4
#define Down_Temp_Sw PORTBbits.RB5 //this button will use to enter to temperature setting mode or decrease  the Wanted Temp
#define Down_Temp_Sw_TRIS TRISBbits.TRISB5
#define Heat_Led_Indicator PORTBbits.RB1// this will toggle when heating element on and on when cooling element on otherwise it will be off  
#define Heat_Led_Indicator_TRIS TRISBbits.TRISB1
//Seven segment display 
#define Sev_Seg_PORT PORTD
#define Sev_Seg_TRIS TRISD
#define Sev_Seg_Low_Pin PORTAbits.RA4// to display the low digit 
#define Sev_Seg_High_Pin PORTAbits.RA3 // to display the high digit
#define Sev_Seg_Low_TRIS TRISAbits.TRISA4
#define Sev_Seg_High_TRIS TRISAbits.TRISA3
// end Seven segment display 
// ---> Heater && Cooler 
#define Heater_Elem_Pin PORTCbits.RC5// to control the statue of heater element 
#define Cooler_Elem_Pin PORTCbits.RC2// to control the statue of cooler element 
#define Heater_Elem_TRIS TRISCbits.TRISC5
#define Cooler_Elem_TRIS TRISCbits.TRISC2
//Heater && Cooler <-------
//-----> Heat sensor  
#define Heat_Sensor_TRIS TRISAbits.TRISA2
// Heat sensor   <---------  
// ------> I2C
//RC3 RC4
// I2C <--------
#endif
