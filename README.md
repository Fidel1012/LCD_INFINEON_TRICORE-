# LCD LIB INFINEON TRICORE AURIX iLLD - TC27xD
## INTRODUCTION 

The aim of this project is to provide a simple library for AURIX Microcontroller TC27xD to use LCD 16X2 HD447, nevertheless, it can be used with the INFINEON iLLD libraries. 

## USAGE

* Put LCD.H into your Inc/folder and LCD.c into Src/. 

* Set pins: Into the file LCD_PINSET.h you can set the pins to be used for LCD. You can add this file into Inc/folder, or you can paste its content into the main.c

* The function LCD_Init() returns a LCD pointer. This pointer will be used as a handle. 

* The function LCD_Begin() sets the parameters of the LCD, the default parameters are:
    * 4 BITS MODE
    * 2 LINES
    * 5x8 FONT
    * CURSOR BLINK ON
    * CURSOR BLINK OFF
    * ENTRY MODE RIGHT
    * DDRAM DECREASE POSITIONS
Feel free to modified this function if you need another parameters, you can find the parameters into LCD.h.

* Into the file Cpu0_main.c it can be found a example of use.

### IMPORTANT NOTE

This version of the library doesn't cover the generation of character over the LCD. 

