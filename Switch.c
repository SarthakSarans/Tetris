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
    IOMUX->SECCFG.PINCM[PB1INDEX] = 0x00000081;

}
// return current state of switches
uint32_t Switch_In(void)
{
    return 0; // replace this your code
}
