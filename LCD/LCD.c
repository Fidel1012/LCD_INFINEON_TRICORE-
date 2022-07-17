
/**********************************************************************************************************************
 * \file    LCD.c
 * \brief
 * \version V1.0.0
 * \date    15 jul. 2022
 * \author  Fidel
 *********************************************************************************************************************/



/*********************************************************************************************************************/
/*-----------------------------------------------------Includes------------------------------------------------------*/
/*********************************************************************************************************************/
#include "LCD.h"
#include <Stm/Std/IfxStm.h>

/*********************************************************************************************************************/
/*-------------------------------------------------------Macros------------------------------------------------------*/
/*********************************************************************************************************************/

/*STM Module uses to generate a delay function*/
#define STM             &MODULE_STM0

/*This macro set the state of a pin
 * if arg > 0, the pin will be high
 * if arg = 0, the pin will be low
 */
#define STATE(arg)  ((arg) ? IfxPort_State_high : IfxPort_State_low)

/*********************************************************************************************************************/
/*-------------------------------------------------Private Variables-------------------------------------------------*/
/*********************************************************************************************************************/

/*
 * @LCD pointer private use
 * @brief: This pointer is for private use for this file.
 */
static LCD * _LCD = NULL;

/*********************************************************************************************************************/
/*-------------------------------------------------Private Functions-------------------------------------------------*/
/*********************************************************************************************************************/

/*
 * @LCD_delay_ms.
 * @brief Low-level function to delay in ms.
 */
static void LCD_Delay_ms(uint32_t time_ms)
{
    sint32 delay_ms = IfxStm_getTicksFromMilliseconds(STM, time_ms);
    IfxStm_waitTicks(STM, delay_ms);
}

/*
 * @LCD_Enable
 * @brief: Function to enable the LCD.
 */
static void LCD_Enable(void)
{
    IfxPort_setPinHigh(_LCD->E->port,_LCD->E->pinIndex);
    LCD_Delay_ms(1);
    IfxPort_setPinLow(_LCD->E->port,_LCD->E->pinIndex);
    LCD_Delay_ms(1);
    IfxPort_setPinHigh(_LCD->E->port,_LCD->E->pinIndex);
}

/*
 * @LCD_Write_4bits.
 * @brief: Function to write 4 bits on the LCD.
 */
static void LCD_Write_4bits(uint8 data)
{
    IfxPort_setPinState(_LCD->DB4->port,_LCD->DB4->pinIndex, STATE(data & 0X01U));
    IfxPort_setPinState(_LCD->DB5->port,_LCD->DB5->pinIndex, STATE(data & 0X02U));
    IfxPort_setPinState(_LCD->DB6->port,_LCD->DB6->pinIndex, STATE(data & 0X04U));
    IfxPort_setPinState(_LCD->DB7->port,_LCD->DB7->pinIndex, STATE(data & 0X08U));
    LCD_Enable();
}

/*
 * @LCD_Send_command
 * @brief: With RS = 0, RW = 0 a command byte is sent.
 */
static void LCD_Send_command(uint8 cmd)
{
    IfxPort_setPinState(_LCD->RS->port, _LCD->RS->pinIndex, IfxPort_State_low);
    IfxPort_setPinState(_LCD->RW->port, _LCD->RW->pinIndex, IfxPort_State_low);

    LCD_Write_4bits(cmd>>4);
    LCD_Write_4bits(cmd);
}

/*
 * @LCD_Send_data
 * @brief: With RS = 1, RW = 0 a data byte is sent.
 */
static void LCD_Send_data(uint8 data)
{
    IfxPort_setPinState(_LCD->RS->port, _LCD->RS->pinIndex, IfxPort_State_high);
    IfxPort_setPinState(_LCD->RW->port, _LCD->RW->pinIndex, IfxPort_State_low);

    LCD_Write_4bits(data>>4);
    LCD_Write_4bits(data);
}

/*********************************************************************************************************************/
/*---------------------------------------------Function Implementations----------------------------------------------*/
/*********************************************************************************************************************/

void LCD_ClearScreen(LCD *LCD_Struct)
{
    _LCD = LCD_Struct;
    LCD_Send_command(LCD_CLEARDISPLAY);
    LCD_Delay_ms(1);
}

void LCD_Home(LCD *LCD_Struct)
{
    _LCD = LCD_Struct;
    LCD_Send_command(LCD_RETURNHOME);
    LCD_Delay_ms(1);
    LCD_Struct->col = 0;
    LCD_Struct->row = 0;
}

void LCD_SetCursor(LCD *LCD_Struct, uint8 col, uint8 row)
{
    _LCD = LCD_Struct;
    uint8 temp_col;

    if((col > 16) | (col < 0))
    {
        col = 0;
    }

    if((row > 2) | (col < 1))
    {
        col = 1;
    }

    temp_col = col;

    if(row == 2)
    {
        temp_col += 0X40U;
    }

    LCD_Send_command(LCD_SETDDRAMADDR | temp_col);
    LCD_Delay_ms(1);
    LCD_Struct->col = col;
    LCD_Struct->row = row;

}
