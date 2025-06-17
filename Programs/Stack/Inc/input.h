/**
 ******************************************************************************
 * @file    input.h
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

#ifndef _INPUT_H
#define	_INPUT_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "keypad.h"
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

//DEFINES
#define OCTETT_SIZE 8
#define MAX_ROBOTS 253
#define MAX_BUTTONS 8
#define BUTTON_OUT_OF_SCOPE 25000
#define IDR_MASK_PIN(n) (0x01U << (n))



int isButtonPressed();
int processKeypadInput();
void processButtonInput(int button);

int myAtoi(const char* str);
#endif