
/**********************************************************************************************************************
 * \file    LCD.h
 * \brief
 * \version V1.0.0
 * \date    15 jul. 2022
 * \author  Fidel
 *********************************************************************************************************************/

#ifndef LCD_LCD_H_
#define LCD_LCD_H_

/*********************************************************************************************************************/
/*-----------------------------------------------------Includes------------------------------------------------------*/
/*********************************************************************************************************************/

#include "stdint.h"
#include "IfxPort.h"

/*********************************************************************************************************************/
/*-----------------------------------------------------Defines-------------------------------------------------------*/
/*********************************************************************************************************************/

//#define MODE_8_BITS

/*
 * @LCD COMMANDS
 * @brief: The commands to set up the LCD
 */
#define LCD_CLEARDISPLAY        0X01   //Clears entire display and set DDRAM address in address counter.
#define LCD_RETURNHOME          0X02   //Sets DDRAM address o in address counter. Returns display to original position.
#define LCD_ENTRYMODESET        0X04   //Sets cursor  move direction an specifies display shift.
#define LCD_DISPLAYONOFFCTRL    0X08   //Sets entire display on/off, cursor on/off and blinking of cursor position character.
#define LCD_CURSORDISPLAYSHIFT  0X10   //Moves cursor and shifts display without changing DDRAM contents.
#define LCD_FUNCTIONSET         0X20   //Sets interface length, number of display lines and character font.
#define LCD_SETCGRAMADDR        0X40   //Sets CGRAM address. CGRAM data is sent and received after this setting.
#define LCD_SETDDRAMADDR        0X80   //Sets DDRAM address. DDRAM data is sent and received after this setting.

/*
 * @ENTRY MODE SET
 * @brief: Entry modes to write in ENTRY MODE SET command.
 */
#define LCD_ENTRY_RIGHT 0X00   //Cursor/blink moves to right and DDRAM address is increased by 1.
#define LCD_ENTRY_LEFT  0X02   //Cursor/blink moves to left and DDRAM in decreased by 1.
/*NOTAS FIDEL: AGREGAR FUNCIONALIDAD DEL BIT S*/

/*
 * @ON/OFF CONTROL
 * @brief: Bits of display ON/OFF control, these bits are used with DISPLAY ON/OFF CONTROL command.
 */
#define LCD_ONOFF_CURSORBLINK_ON    0X01   //Cursor blink is on.
#define LCD_ONOFF_CURSORBLINK_OFF   0X00   //Cursor blink if off.
#define LCD_ONOFF_CURSOR_ON         0X02   //Cursor is turned on.
#define LCD_ONOFF_CURSOR_OFF        0X00   //Cursor is disappeared in current display, but I/D register remains its data.
#define LCD_ONOFF_DISPLAY_ON        0X04   //Entire display is turned on.
#define LCD_ONOFF_DISPLAY_OFF       0X00   //Display is turned off, but display data is remained in DDRAM.

/*
 * @CURSOR OR DISPLAY SHIFT
 * @brief: Shifting of right/left cursor position or display writing o reading of display data.
 */
#define LCD_SHIFT_CURSOR_LEFT   0X00   //Shifts the cursor position to the left, address counter is decreased by 1.
#define LCD_SHIFT_CURSOR_RIGHT  0X01   //Shifts the cursor position to the right, address counter is increased by 1.

/*
 * @FUNCTION SET
 * @brief: Set the length, number of lines and character font.
 */
#define LCD_FUNCTION_FONT_5X8   0X00   //5x8 dot format display mode.
#define LCD_FUNCTION_FONT_5X10  0X04   //5x10 dot format display mode.
#define LCD_FUNCTION_LINES_1    0X00   //1 line display mode.
#define LCD_FUNCTION_LINES_2    0X08   //2 lines display mode.
#define LCD_FUNCTION_LENGTH_4   0X00   //4-Bit bus mode with MPU.
#define LCD_FUNCTION_LENGTH_8   0X10   //8-Bit bus mode with MPU.

/*********************************************************************************************************************/
/*-------------------------------------------------Data Structures---------------------------------------------------*/
/*********************************************************************************************************************/

/*
 * @LCD_PIN_STUCTURE
 * @brief: Define a pin of LCD.
 */
typedef struct _LCD_PIN{
        Ifx_P *port;
        uint8 pinIndex;
}LCD_PIN;

/*
 *@LCD_STRUCTURE
 *@brief: Define all pins of LCD.
 */
typedef struct _LCD{
        LCD_PIN *E;
        LCD_PIN *RS;
        LCD_PIN *RW;

#ifdef  MODE_8_BITS
        LCD_PIN *DB0;
        LCD_PIN *DB1;
        LCD_PIN *DB2;
        LCD_PIN *DB3;
#endif
        LCD_PIN *DB4;
        LCD_PIN *DB5;
        LCD_PIN *DB6;
        LCD_PIN *DB7;

        uint8 col;
        uint8 row;
}LCD;


/*********************************************************************************************************************/
/*------------------------------------------------Function Prototypes------------------------------------------------*/
/*********************************************************************************************************************/

/*
 *@LCD_Init
 *@brief: Initialize LCD parameters an returns @ref LCD.
 *@param: Pointer to Enable pin structure, @ref LCD_PIN.
 *@param: Pointer to RS pin structure, @ref LCD_PIN.
 *@param: Pointer to RW pin structure, @ref LCD_PIN.
 *@param: Pointer to DB0 pin structure, @ref LCD_PIN.
 *@param: Pointer to DB1 pin structure, @ref LCD_PIN.
 *@param: Pointer to DB2 pin structure, @ref LCD_PIN.
 *@param: Pointer to DB3 pin structure, @ref LCD_PIN.
 *@param: Pointer to DB4 pin structure, @ref LCD_PIN.
 *@param: Pointer to DB5 pin structure, @ref LCD_PIN.
 *@param: Pointer to DB6 pin structure, @ref LCD_PIN.
 *@param: Pointer to DB7 pin structure, @ref LCD_PIN.
 */
LCD* LCD_Init(LCD_PIN *E, LCD_PIN *RS, LCD_PIN *RW,
#ifdef MODE_8_BITS
        LCD_PIN *DBO, LCD_PIN *DB1, LCD_PIN *DB2, LCD_PIN *DB3,
#endif
        LCD_PIN *DB4, LCD_PIN *DB5, LCD_PIN *DB6, LCD_PIN *DB7);

/*
 *@LCD_Begin
 *@brief: Set initial default parameters for the LCD.
 *@param: LCD_struct pointer to structure @ref LCD.
 */
void LCD_Begin(LCD *LCD_Struct);

/*
 * @LCD_ClearScreen
 * @brief: Clear display´s data and put set cursor position 0.
 * @param: LCD_struct pointer to structure @ref LCD.
 */
void LCD_ClearScreen(LCD *LCD_Struct);

/*
 * @LCD_Home
 * @brief: Bring the cursor to the top left position.
 * @param: LCD_struct pointer to structure @ref LCD.
 */
void LCD_Home(LCD *LCD_Struct);

/*
 * @LCD_SetCursor
 * @brief: Move the cursor to a specific position.
 *         If @col excedds 0x4F, i.e., the last column of 2nd line, then
 *         it is reset to 0x00, i.e., the 1st column of the 1st line.
 * @param: LCD_struct pointer to structure @ref LCD.
 * @param: Row position.
 * @param: Column position.
 */
void LCD_SetCursor(LCD *LCD_Struct, uint8 row, uint8 col);

/*
 * @LCD_PutChar
 * @brief: Put a char on the cursor.
 * @param: LCD_struct pointer to structure @ref LCD.
 * @param: Character to be put on the cursor.
 */
void LCD_PutChar(LCD *LCD_Struct, uint8 c);

/*
 * @LCD_PutStr
 * @brief: Put a string of chars from the current cursor position.
 * @param: LCD_struct pointer to structure @ref LCD.
 * @param: String to be put on the cursor.
 */
void LCD_PutStr(LCD *LCD_Struct, uint8 *s);

/*
 * @LCD_Send_command
 * @brief: With RS = 0, RW = 0 a command byte is sent.
 * @param: Command to be sent.
 */
void LCD_Send_command(uint8 cmd);

/*
 * @LCD_Send_data
 * @brief: With RS = 1, RW = 0 a data byte is sent.
 * @param: Byte data to be sent.
 */
void LCD_Send_data(uint8 data);


#endif /* LCD_LCD_H_ */
