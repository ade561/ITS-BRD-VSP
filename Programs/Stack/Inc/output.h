/**
 ******************************************************************************
 * @file    output.h
 * @author  Darius Dao
 *          HAW-Hamburg
 *          Labor f�r technische Informatik
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

#define LED_ON 1
#define LED_OFF 0
#define ALL_LEDS 16
#define GPIOX_E_LED  2
#define GPIOX_D_LED  3




void setLed(int led, int gpiox, int state);
void showText(char* text);


#endif