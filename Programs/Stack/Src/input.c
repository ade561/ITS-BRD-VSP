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

#include <stdio.h>
#include "stm32f4xx_hal.h"
#include "init.h"
#include "delay.h"
#include "LCD_GUI.h"
#include "LCD_Demos.h"
#include "lcd.h"
#include "fontsFLASH.h"
#include "LCD_Touch.h"
#include "error.h"
#include "keypad.h"
#include "terminal.h"
#include "keypad.h"
#include "input.h"
#include "output.h"
#include "terminal.h"
#include "udp_client.h"
#include "message.h"
#include "led.h"


static int shiftButtonPressed = 0;
static const int nonShiftCommands[NON_SHIFT_NUM_COMMAND_CASES] = {
    MOVE_RIGHT, MOVE_LEFT, MOVE_UP, MOVE_DOWN, MOVE_FORWARD, MOVE_BACKWARDS
};
static const int shiftCommands[SHIFT_NUM_COMMAND_CASES] = {
    OPEN_GRIP, CLOSE_GRIP
};

int isButtonPressed(){
	int button = 0;
	for(int i = 0; i < MAX_BUTTONS; i++){
		 char gpiofPinXPressed = (IDR_MASK_PIN(i) != (GPIOF->IDR & IDR_MASK_PIN(i)));
		if(gpiofPinXPressed == 1){
			button = i;
            delay(50);
			break;
		}else{
			button = BUTTON_OUT_OF_SCOPE;
		}
	}
	return button;
}


void processButtonInput(int button) {


    // Check if shift button is pressed
    if(shiftButtonPressed) {
        if (button >= 0 && button < SHIFT_NUM_COMMAND_CASES) {
            sendMsg(shiftCommands[button]);
        }else {
        switch (button) {
            case 6:
                shiftButtonPressed = 0;
                toggleGPIO(&led_pins[6]);
                break;
            case 7: {
                GUI_clear(WHITE);
                lcdGotoXY(DEFAULT_XCORD, DEFAULT_YCORD);
                lcdPrintlnS("gebe einen Roboter an: ");
                int ledNumber = processKeypadInput();
                selectServer(ledNumber);
                setLed(ledNumber, GPIOX_D_LED, LED_ON);
                break;
            }
            default:
                break;
            }
     }
    }else {
        
    //shiftButtonPressed = 0; 
    if(button >= 0 && button < NON_SHIFT_NUM_COMMAND_CASES) {
        sendMsg(nonShiftCommands[button]);
    } else {
        switch (button) {
            case 6:
                shiftButtonPressed = 1;  // Toggle shift state
                toggleGPIO(&led_pins[6]);
                break;
            case 7: {
                disconnectServer();
                GUI_clear(WHITE);
                lcdGotoXY(DEFAULT_XCORD, DEFAULT_YCORD);
                lcdPrintlnS("gebe einen Roboter an: ");
                int ledNumber = processKeypadInput();
                selectServer(ledNumber);
                setLed(ledNumber, GPIOX_D_LED, LED_ON);
                break;
            }
            default:
                break;
        }
    }
}
}



/**
 * @brief  Verarbeitet Tastendrücke und generiert eine Zahl aus Bits.
 *         2x dieselbe Taste = Eingabe beenden.
 * @return resultierende Zahl (0–254)
 */
int processKeypadInput(void) {
    bool seen[8] = {false};  // gemerkte Tastendrücke
    int lastButton = -1;      // Index der zuletzt gedrückten Taste
    int actualNumber = 0;

    while (1) {
        int button = isButtonPressed();
        if (button < 0 || button >= 8) {
            HAL_Delay(50);  // kleine Entprellpause
            continue;
        }

        // Wenn dieselbe Taste erneut gedrückt -> beenden
        if (button == lastButton && actualNumber != 0) {
            return actualNumber;
        }

        // Wenn Taste zum ersten Mal gedrückt, Zahl updaten
        if (!seen[button]) {
            seen[button] = true;
            actualNumber |= (1 << button);  // Bit setzen
        }
        lastButton = button;

        HAL_Delay(200);  // Pause, um mehrfaches Erkennen zu vermeiden
    }
}




int myAtoi(const char* str) {
    int result = 0;
    
    while (*str == ' ') {
        str++;
    }

    while (*str >= '0' && *str <= '9') {
        result = result * 10 + (*str - '0');
        str++;
    }
    return result;
}
