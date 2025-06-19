/**
 ******************************************************************************
 * @file    main.c
 * @author  TI Team
 *          HAW-Hamburg
 *          Labor f�r technische Informatik
 *          Berliner Tor  7
 *          D-20099 Hamburg
 * @version 1.1
 *
 * @date    17. Juli 2020
 * @brief   Rahmen fuer C Programme, die auf dem ITSboard ausgefuehrt werden.
 *
 *					25.04.2022 Tobias De Gasperis: printf hinzugefuegt
 ******************************************************************************
 */

#include "output.h"


void setLed(int led, int gpiox, int state){

	// GPIOX_D_LED
	if(gpiox == GPIOX_D_LED && state == LED_ON){
		GPIOD->BSRR = 0xFF << 16;
		GPIOD->BSRR = led;
	}
	else if(gpiox == GPIOX_D_LED && state == LED_OFF){
  		GPIOD->BSRR = 0xFF << 16;
	}

	// GPIOX_E_LED
	else if(gpiox == GPIOX_E_LED && state == LED_ON){
		GPIOE->BSRR = 0xFF << 16;
		GPIOE->BSRR = led; // Set the specific LED pin
	  }
	else if(gpiox == GPIOX_E_LED && state == LED_OFF){
		GPIOE->BSRR = 0xFF << 16;
	}
}
void showText(char* text);
