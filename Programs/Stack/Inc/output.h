/**
 ******************************************************************************
 * @file    output.h
 * @author  Darius Dao
 *          HAW-Hamburg
 *          Labor für technische Informatik
 *          Berliner Tor  7
 *          D-20099 Hamburg
 * @version 1.0
 *
 * @date    11. Juni 2025
 ******************************************************************************
 */


#ifndef _OUTPUT_H
#define	_OUTPUT_H
#include <stdio.h>
#include <stdlib.h>
#include "stm32f4xx_hal.h"
#include "init.h"
#include "delay.h"
#include "LCD_GUI.h"
#include "LCD_Demos.h"
#include "lcd.h"
#include "fontsFLASH.h"
#include "LCD_Touch.h"
#include "error.h"
#include "terminal.h"


void setLed(int led);
void showText(char* text);


#endif