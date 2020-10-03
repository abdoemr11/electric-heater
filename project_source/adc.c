#include <xc.h>
#include "adc.h"


void adc_init(void)
{
  ADCON1=0x02;
  ADCON0=0x41; 
}

unsigned int adc_amostra(unsigned char canal)
{

     switch(canal)
    {
      case 0:
        ADCON0=0x01;
        break;
      case 1:
        ADCON0=0x09;
        break;
      case 2:
        ADCON0=0x11;
        break;
    }   
   

    ADCON0bits.GO=1;
    while(ADCON0bits.GO == 1);

   return ((((unsigned int)ADRESH)<<2)|(ADRESL>>6));
}
