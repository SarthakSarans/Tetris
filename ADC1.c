/* ADC1.c
 * Sarthak Sarans
 * Modified: put the date here
 * 12-bit ADC input on ADC1 channel 5, PB18
 */
#include <ti/devices/msp/msp.h>
#include "../inc/Clock.h"
#define ADCVREF_VDDA 0x000
#define ADCVREF_INT  0x200


void ADCinit(void){
// write code to initialize ADC1 channel 5, PB18
// Your measurement will be connected to PB18
// 12-bit mode, 0 to 3.3V, right justified
// software trigger, no averaging
    ADC1->ULLMEM.GPRCM.RSTCTL = 0xB1000003;
    ADC1->ULLMEM.GPRCM.PWREN = 0x26000001;
    Clock_Delay(24);
    ADC1->ULLMEM.GPRCM.CLKCFG = 0xA9000000;
    ADC1->ULLMEM.CLKFREQ = 7;
    ADC1->ULLMEM.CTL0 = 0x03010000;
    ADC1->ULLMEM.CTL1 = 0x00000000;
    ADC1->ULLMEM.CTL2 = 0x00000000;
    ADC1->ULLMEM.MEMCTL[0] = 5;
    ADC1->ULLMEM.SCOMP0 = 0;
    ADC1->ULLMEM.CPU_INT.IMASK = 0;

}

uint32_t ADCin(void){
  // write code to sample ADC1 channel 5, PB18 once
  // return digital result (0 to 4095)
    ADC1->ULLMEM.CTL0 |= 0x00000001;             // 1) enable conversions
    ADC1->ULLMEM.CTL1 |= 0x00000100;             // 2) start ADC
    uint32_t volatile delay=ADC1->ULLMEM.STATUS; // 3) time to let ADC start
    while((ADC1->ULLMEM.STATUS&0x01)==0x01){}    // 4) wait for completion
    return ADC1->ULLMEM.MEMRES[0];
}

// your function to convert ADC sample to distance (0.001cm)
// use main2 to calibrate the system fill in 5 points in Calibration.xls
//    determine constants k1 k2 to fit Position=(k1*Data + k2)>>12
uint32_t Convert(uint32_t input){
  int position = 0;
  position = (1751 * input + 16)>>12;
  return position;
}

uint32_t BlockMove(uint32_t pos){
        int scaled_value = (pos * 108 + 875) / 1750; // 875 = half of 1750 for rounding
        // Round scaled_value to the nearest multiple of 12
        int result = ((scaled_value + 6) / 12) * 12; // Add 6 (half of 12) for manual rounding
        return result+4;
}

// do not use this function
// it is added just to show you how SLOW floating point in on a Cortex M0+
float FloatConvert(uint32_t input){
  return 0.00048828125*input -0.0001812345;
}
