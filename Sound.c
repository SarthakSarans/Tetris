// Sound.c
// Runs on MSPM0
// Sound assets in sounds/sounds.h
// Jonathan Valvano
// 11/15/2021
#include <stdint.h>
#include <ti/devices/msp/msp.h>
#include "Sound.h"
#include "sounds/sounds.h"
#include "../inc/DAC5.h"
#include "../inc/Timer.h"

void SysTick_IntArm(uint32_t period, uint32_t priority)
{
  SysTick->CTRL = 0x00;       // disable during initialization
  SysTick->LOAD = period - 1; // set reload register
  // The ARM Cortex-M0+ only implements the most significant 2 bits of each 8-bit priority field (giving the 4 priority levels).
  SCB->SHP[1] = (SCB->SHP[1] & (~0xC0000000)) | priority << 30; // set priority (bits 31,30)
  SysTick->VAL = 0;                                             // clear count, cause reload
  SysTick->CTRL = 0x07;                                         // Enable SysTick IRQ and SysTick Timer
}
// initialize a 11kHz SysTick, however no sound should be started
// initialize any global variables
// Initialize the 5 bit DAC
void Sound_Init(void)
{
  // write this
  __disable_irq();
  SysTick_IntArm(80000000 / 11025, 0);
  __enable_irq();
  DAC_Init();
}

const uint8_t *SoundDataPtr;
uint32_t SoundDataCount;
void SysTick_Handler(void)
{ // called at 11 kHz
  // output one value to DAC if a sound is active
  // output one value to DAC if a sound is active
  if (SoundDataCount > 0)
  {
    DAC_Out(*SoundDataPtr);
    SoundDataPtr++;
    SoundDataCount--;
  }
}

//******* Sound_Start ************
// This function does not output to the DAC.
// Rather, it sets a pointer and counter, and then enables the SysTick interrupt.
// It starts the sound, and the SysTick ISR does the output
// feel free to change the parameters
// Sound should play once and stop
// Input: pt is a pointer to an array of DAC outputs
//        count is the length of the array
// Output: none
// special cases: as you wish to implement
void Sound_Start(const uint8_t *pt, uint32_t count)
{
  // write this
  __disable_irq();
  SoundDataPtr = pt;
  SoundDataCount = count;
  __enable_irq();
}
void Sound_Shoot(void)
{
  // write this
  Sound_Start(shoot, 4080);
}
void Sound_Killed(void)
{
  // write this
  Sound_Start(invaderkilled, 3377);
}
void Sound_Explosion(void)
{
  // write this
}
