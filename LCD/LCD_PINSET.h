/*
 * LCD_PINSET.h
 *
 *  Created on: 18 jul. 2022
 *      Author: Fidel
 */

#ifndef LCD_LCD_PINSET_H_
#define LCD_LCD_PINSET_H_

#include "Ifx_Types.h"
#include "IfxCpu.h"
#include "IfxScuWdt.h"

#define PIN_E   &MODULE_P15,3
#define PIN_RS  &MODULE_P15,2
#define PIN_RW  &MODULE_P02,0
#define PIN_DB4 &MODULE_P02,1
#define PIN_DB5 &MODULE_P10,4
#define PIN_DB6 &MODULE_P02,3
#define PIN_DB7 &MODULE_P02,5


void Pin_LCD_init(void)
{
    IfxPort_setPinModeOutput(PIN_E, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinModeOutput(PIN_RS, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinModeOutput(PIN_RW, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinModeOutput(PIN_DB4, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinModeOutput(PIN_DB5, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinModeOutput(PIN_DB6, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinModeOutput(PIN_DB7, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
}

#endif /* LCD_LCD_PINSET_H_ */
