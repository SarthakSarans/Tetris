/*
 * Switch.c
 *
 *  Created on: 8/22/2024
 *      Author:
 */
#include <ti/devices/msp/msp.h>
#include "../inc/LaunchPad.h"
#include "Switch.h"
// LaunchPad.h defines all the indices into the PINCM table
void Switch_Init(void)
{
    IOMUX->SECCFG.PINCM[PB16INDEX] = 0x00040081; // rotate
    IOMUX->SECCFG.PINCM[PB17INDEX] = 0x00040081; // store
}
// return current state of switches
uint32_t Switch_In(void)
{
    return (GPIOB->DIN31_0 & 0x30000) >> 16; // replace this your code
}
