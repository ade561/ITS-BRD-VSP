#ifndef _INTERRUPT_H_
#define _INTERRUPT_H_

#include "stm32f4xx_hal.h"
void initISR(void);


// IRQ-Handler deklarieren � optional, aber klar dokumentiert
void EXTI9_5_IRQHandler(void);

#endif
