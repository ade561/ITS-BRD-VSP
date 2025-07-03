/**
 ******************************************************************************
 * @file    main.c
 * @author  Martin Becke
 * @brief   Kleines Testprogramm fuer lwip
 ******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "delay.h"
#define STM32F429xx
#include <arm_compat.h>

#include "LCD_GUI.h"
#include "stm32f4xx_hal.h"
#include <stdint.h>

#include "LCD_GUI.h"
#include "LCD_Touch.h"

#include "lcd.h"

#include "led.h"
#include "lwip_interface.h"
#include "interrupt.h"
#include "tcp_server.h"
#include "output.h"
#include "input.h"
#include "udp_client.h"
#include "timer.h"
#include "message.h"

extern void initITSboard(void);
extern void initLCDTouch(void);

volatile uint64_t currentTime, oldTime;
volatile uint8_t heartbeatStatus = 0;
volatile uint8_t keepAliveCounter = 0; 


/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void) {
    initITSboard();
    GUI_init(DEFAULT_BRIGHTNESS);
    TP_Init(false);
 //   initISR();
    if (!checkVersionFlashFonts()) Error_Handler();

    lcdPrintlnS("UDP-Client");

    init_lwip_stack();
    netif_config();
    udp_client_init();
    initTimer();
    currentTime = TIM2->CNT;
    oldTime = TIM2->CNT;



int button = 0;
	while(1){
    //Heartbeat
        if((oldTime - currentTime) < HEARTBEAT_INTERVAL) {
          if(keepAliveCounter > 10){
            if(heartbeatStatus == 1) {
            connectionLost();
            heartbeatStatus = 0;
            currentTime = oldTime;
          }
          }else{
            keepAliveCounter++;
          }
        }
		// 1: Snapshot of all Sensors and Actuators
		check_input();
		button  = isButtonPressed();
	
		// 2: Update the Values + do the logic
		processButtonInput(button);
    delay(50); // Debounce delay for button presses
		// 3: Output
		
	}
}