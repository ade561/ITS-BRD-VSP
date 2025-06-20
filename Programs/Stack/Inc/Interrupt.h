#ifndef _INTERRUPT_H_
#define _INTERRUPT_H_

#include "input.h"

void initISR(void);


// IRQ-Handler deklarieren – optional, aber klar dokumentiert
void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);
void EXTI2_IRQHandler(void);
void EXTI3_IRQHandler(void);
void EXTI4_IRQHandler(void);
void EXTI9_5_IRQHandler(void);

#endif
