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
 
/* Definitionen */
#define TASK_COUNT 4
 
/* Struktur für eine Task */
typedef struct {
  void (*taskFunction)(void);  // Funktionspointer zur Task
  uint32_t nextExecutionTime;  // Zeitpunkt für die nächste Ausführung
  uint32_t offset;             // Offset für die nächste Ausführung
  bool isEnabled;              // Aktivierungsflag
} Task_t;
 
/* Funktionsdeklarationen */
void HeartbeatTask(void);
void ButtonTask(void);
void InputTask(void);
void Scheduler(void);
 
/* Globale Variablen */
Task_t taskList[TASK_COUNT] = {
    {HeartbeatTask, 0, 100, true},  // Heartbeat alle 1000 ms
    {ButtonTask, 0, 50, true},       // Button-Verarbeitung alle 50 ms
    {InputTask, 0, 10, true},        // Eingabe alle 10 ms
};
 
int main(void) {
    initITSboard();  // Initialisierung des ITS Boards
    GUI_init(DEFAULT_BRIGHTNESS);  // Initialisierung des LCD Boards mit Touch
    TP_Init(false);                // Initialisierung des LCD Boards mit Touch
 
    // Begrüßungstext
    lcdPrintlnS("UDP-Client");
 
    // Initialisiere den Stack
    init_lwip_stack();
 
    // Setup Interface
    netif_config();
    udp_client_init();
    // Test in Endlosschleife
    while (1) {
        Scheduler();  // Aufruf des Schedulers in der Endlosschleife
    }
}
 
/* Heartbeat-Task */
void HeartbeatTask(void) {
    if (((oldTime - currentTime) < HEARTBEAT_INTERVAL)) {
        if (keepAliveCounter > 10) {
            if (heartbeatStatus == 1) {
                connectionLost();
                heartbeatStatus = 0;
                currentTime = oldTime;
            }
        } else {
            keepAliveCounter++;
        }
    }
}
 
/* Button-Task - Entprellung der Tasten */
void ButtonTask(void) {
    static int button = 0;
    button = isButtonPressed();
    processButtonInput(button);
}
 
/* Eingabe-Task */
void InputTask(void) {
    check_input();
}
 
/* Scheduler-Funktion */
void Scheduler(void) {
    currentTime = HAL_GetTick();  // Simulierte Zeit fortschreiben
    for (uint8_t i = 0; i < TASK_COUNT; i++) {
        if (taskList[i].isEnabled && currentTime >= taskList[i].nextExecutionTime) {
            taskList[i].taskFunction();  // Task ausführen
            taskList[i].nextExecutionTime = currentTime + taskList[i].offset; // Nächste Ausführungszeit
        }
    }
}