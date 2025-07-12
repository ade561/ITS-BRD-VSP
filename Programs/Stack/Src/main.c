#include "delay.h"
#include "stm32f429xx.h"
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
#include "net/ethernetif.h"

 
extern void initITSboard(void);
extern void initLCDTouch(void);
 
volatile uint32_t currentTime, oldTime;
volatile uint32_t scheduleTime = 0;
volatile uint8_t heartbeatStatus = 0;
volatile uint8_t keepAliveCounter = 0;
 
/* Definitionen */
#define TASK_COUNT 4
#define CONNECTIVITY_CHECK_INTERVAL 250
#define MAX_MISSED_ACKS 10
 
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
    {HeartbeatTask, 0, 100, true},  // Heartbeat alle 100 ms
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
    oldTime = HAL_GetTick();
    while (1) {
        Scheduler();  // Aufruf des Schedulers in der Endlosschleife
    }
}
 
/* Heartbeat-Task */
/* Heartbeat-Task */
void HeartbeatTask(void) {
    if (heartbeatStatus == 1) {
    if ((oldTime - currentTime) > CONNECTIVITY_CHECK_INTERVAL) {
        if (keepAliveCounter > MAX_MISSED_ACKS) {
                disconnectServer();
                heartbeatStatus = 0;
                GUI_clear(WHITE);
                lcdGotoXY(DEFAULT_XCORD, DEFAULT_XCORD);
                lcdPrintlnS("Verbindung getrennt zum Roboter.");
                lcdPrintlnS("Falls erneut verbunden werden soll, bitte LAN Kabel anstecken & S7 Taster betaetigen.");
            }
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
    scheduleTime = HAL_GetTick();  // Simulierte Zeit fortschreiben
    currentTime = HAL_GetTick();
    for (uint8_t i = 0; i < TASK_COUNT; i++) {
        if (taskList[i].isEnabled && scheduleTime >= taskList[i].nextExecutionTime) {
            taskList[i].taskFunction();  // Task ausführen
            taskList[i].nextExecutionTime = scheduleTime + taskList[i].offset; // Nächste Ausführungszeit
        }
    }
}