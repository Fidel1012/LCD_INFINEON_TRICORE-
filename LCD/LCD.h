
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

/*********************************************************************************************************************/
/*------------------------------------------------------Macros-------------------------------------------------------*/
/*********************************************************************************************************************/

/*********************************************************************************************************************/
/*-----------------------------------------------------Defines-------------------------------------------------------*/
/*********************************************************************************************************************/

/*
 * @LCD COMMANDS
 * @brief: The commands to set up the LCD
 */
#define LCD_CLEARDISPLAY        0X01U   //Clears entire display and set DDRAM address in address counter.
#define LCD_RETURNHOME          0X02U   //Sets DDRAM address o in address counter. Returns display to original position.
#define LCD_ENTRYMODESET        0X04U   //Sets cursor  move direction an specifies display shift.
#define LCD_DISPLAYONOFFCTRL    0X08U   //Sets entire display on/off, cursor on/off and blinking of cursor position character.
#define LCD_CURSORDISPLAYSHIFT  0X10U   //Moves cursor and shifts display without changing DDRAM contents.
#define LCD_FUNCTIONSET         0X20U   //Sets interface length, number of display lines and character font.
#define LCD_SETCGRAMADDR        0X40U   //Sets CGRAM address. CGRAM data is sent and received after this setting.
#define LCD_SETDDRAMADDR        0X80U   //Sets DDRAM address. DDRAM data is sent and received after this setting.
#define LCD_READBUSYFLAG        0X100U  //Reads busy flags indicating internal operation is being performed.

/*
 * @ENTRY MODE SET
 * @brief: Entry modes to write in ENTRY MODE SET command.
 */
#define LCD_ENTRY_RIGHT 0X02U   //Cursor/blink moves to right and DDRAM address is increased by 1.
#define LCD_ENTRY_LEFT  0X00U   //Cursor/blink moves to left and DDRAM in decreased by 1.
/*NOTAS FIDEL: AGREGAR FUNCIONALIDAD DEL BIT S*/

/*
 * @ON/OFF CONTROL
 * @brief: Bits of display ON/OFF control, these bits are used with DISPLAY ON/OFF CONTROL command.
 */
#define LCD_ONOFF_CURSORBLINK_ON    0X01U   //Cursor blink is on.
#define LCD_ONOFF_CURSORBLINK_OFF   0X00U   //Cursor blink if off.
#define LCD_ONOFF_CURSOR_ON         0X02U   //Cursor is turned on.
#define LCD_ONOFF_CURSOR_OFF        0X00U   //Cursor is disappeared in current display, but I/D register remains its data.
#define LCD_ONOFF_DISPLAY_ON        0X40U   //Entire display is turned on.
#define LCD_ONOFF_DISPLAY_OFF       0X00U   //Display is turned off, but display data is remained in DDRAM.

/*
 * @CURSOR OR DISPLAY SHIFT
 * @brief: Shifting of right/left cursor position or display writing o reading of display data.
 */
#define LCD_SHIFT_CURSOR_LEFT   0X00U   //Shifts the cursor position to the left, address counter is decreased by 1.
#define LCD_SHIFT_CURSOR_RIGHT  0X01U   //Shifts the cursor position to the right, address counter is increased by 1.
#define LCD_SHIFT_DISPLAY_LEFT  0X02U   //Shifts the entire display to the left, the cursor follows the display shift.
#define LCD_SHIFT_DISPLAY_RIGHT 0X03U   //Shifts the entire display to the right, the cursor follows the display shift.

/*
 * @FUNCTION SET
 * @brief: Set the length, number of lines and character font.
 */
#define LCD_FUNCTION_FONT_5X8   0X00U   //5x8 dot format display mode.
#define LCD_FUNCTION_FONT_5X11  0X04U   //5x11 dot format display mode.
#define LCD_FUNCTION_LINES_1    0X00U   //1 line display mode.
#define LCD_FUNCTION_LINES_2    0X08U   //2 lines display mode.
#define LCD_FUCNTION_LENGTH_4   0X00U   //4-Bit bus mode with MPU.
#define LCD_FUNCTION_LENGTH_8   0X10U   //8-Bit bus mode with MPU.

/*********************************************************************************************************************/
/*-------------------------------------------------Global variables--------------------------------------------------*/
/*********************************************************************************************************************/

/*********************************************************************************************************************/
/*-------------------------------------------------Data Structures---------------------------------------------------*/
/*********************************************************************************************************************/
 
/*********************************************************************************************************************/
/*--------------------------------------------Private Variables/Constants--------------------------------------------*/
/*********************************************************************************************************************/

/*********************************************************************************************************************/
/*------------------------------------------------Function Prototypes------------------------------------------------*/
/*********************************************************************************************************************/


#endif /* LCD_LCD_H_ */
