
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

/*********************************************************************************************************************/
/*---------------------------------------------Function Implementations----------------------------------------------*/
/*********************************************************************************************************************/

void LCD_Begin(LCD *LCD_Struct)
{
    _LCD = LCD_Struct;

    //Keep Enable pin low.
    IfxPort_setPinLow(LCD_Struct->E->port, LCD_Struct->E->pinIndex);
    IfxPort_setPinLow(LCD_Struct->RS->port, LCD_Struct->RS->pinIndex);
    IfxPort_setPinLow(LCD_Struct->RW->port, LCD_Struct->RW->pinIndex);
    LCD_Delay_ms(10);

    //Function set config.
    LCD_Send_command(LCD_FUNCTIONSET | LCD_FUNCTION_LENGTH_4 | LCD_FUNCTION_LINES_2 | LCD_FUNCTION_FONT_5X8);
    LCD_Delay_ms(5);

    //Display on/off, cursor blink config.
    LCD_Send_command(LCD_DISPLAYONOFFCTRL | LCD_ONOFF_DISPLAY_ON | LCD_ONOFF_CURSORBLINK_ON | LCD_ONOFF_CURSOR_ON);
    LCD_Delay_ms(5);

    //Entry mode congig.
    LCD_Send_command(LCD_ENTRYMODESET | LCD_ENTRY_RIGHT | LCD_SHIFT_CURSOR_LEFT);
    LCD_Delay_ms(5);

    LCD_ClearScreen(LCD_Struct);

    LCD_Home(LCD_Struct);

    LCD_Delay_ms(500);
}

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

    if((col > 15) | (col < 0))
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

void LCD_PutChar(LCD *LCD_Struct, uint8 c)
{
    _LCD = LCD_Struct;
    LCD_Send_data(c);
    LCD_Delay_ms(1);

    //Move cursor 1 forward
    if((LCD_Struct->row == 1) && (LCD_Struct->col == 15))
        LCD_SetCursor(LCD_Struct, 0, 2);
    if((LCD_Struct->row == 2) && (LCD_Struct->col == 15))
        LCD_SetCursor(LCD_Struct, 0, 1);
    else
        LCD_SetCursor(LCD_Struct, LCD_Struct->col + 1,LCD_Struct->row);
}

void LCD_PutStr(LCD *LCD_Struct, uint8 *s)
{
    _LCD = LCD_Struct;

    for(; *s != 0; ++s){
        LCD_PutChar(LCD_Struct, *s);
    }
}

void LCD_Send_command(uint8 cmd)
{
    IfxPort_setPinState(_LCD->RS->port, _LCD->RS->pinIndex, IfxPort_State_low);
    IfxPort_setPinState(_LCD->RW->port, _LCD->RW->pinIndex, IfxPort_State_low);

    LCD_Write_4bits(cmd>>4);
    LCD_Write_4bits(cmd);
}

void LCD_Send_data(uint8 data)
{
    IfxPort_setPinState(_LCD->RS->port, _LCD->RS->pinIndex, IfxPort_State_high);
    IfxPort_setPinState(_LCD->RW->port, _LCD->RW->pinIndex, IfxPort_State_low);

    LCD_Write_4bits(data>>4);
    LCD_Write_4bits(data);
}
