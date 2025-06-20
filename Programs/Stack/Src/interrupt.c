#include "interrupt.h"
#include "stm32f4xx_hal.h"
#include "input.h"       // enth�lt processButtonInput()

#define DEBOUNCE_MS 50
static uint32_t last_irq_time[8] = {0};
extern volatile int inputModeActive;


void initISR() {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOFEN;      // Clock für GPIOF aktivieren
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;     // Clock für SYSCFG aktivieren

    // EXTI für PF0 bis PF7 einrichten
    for (int i = 0; i <= 7; i++) {
        // Jeder EXTIx liegt im EXTICR[x/4], an Position (x%4)*4
        int reg_index = i / 4;
        int pos = (i % 4) * 4;

        SYSCFG->EXTICR[reg_index] &= ~(0xF << pos);
        SYSCFG->EXTICR[reg_index] |= (0x5 << pos); // 0x5 = Port F

        EXTI->IMR |= (1 << i);   // Interrupt aktivieren
        EXTI->RTSR |= (1 << i);  // Rising Edge
        EXTI->FTSR |= (1 << i);  // Falling Edge (optional für Toggle)
    }

    // Einzelne EXTI-IRQ aktivieren
    NVIC_SetPriority(EXTI0_IRQn, 0);
    NVIC_EnableIRQ(EXTI0_IRQn);

    NVIC_SetPriority(EXTI1_IRQn, 0);
    NVIC_EnableIRQ(EXTI1_IRQn);

    NVIC_SetPriority(EXTI2_IRQn, 0);
    NVIC_EnableIRQ(EXTI2_IRQn);

    NVIC_SetPriority(EXTI3_IRQn, 0);
    NVIC_EnableIRQ(EXTI3_IRQn);

    NVIC_SetPriority(EXTI4_IRQn, 0);
    NVIC_EnableIRQ(EXTI4_IRQn);

    // EXTI5–EXTI9 laufen über gemeinsamen Handler
    NVIC_SetPriority(EXTI9_5_IRQn, 0);
    NVIC_EnableIRQ(EXTI9_5_IRQn);
}



void EXTI0_IRQHandler(void) {
    if (EXTI->PR & (1 << 0)) {
        int button = isButtonPressed();
        if (button != BUTTON_OUT_OF_SCOPE && inputModeActive == 0) {
            processButtonInput(button);
        }
        EXTI->PR |= (1 << 0);
    }
}

void EXTI1_IRQHandler(void) {
    if (EXTI->PR & (1 << 1)) {
        int button = isButtonPressed();
        if (button != BUTTON_OUT_OF_SCOPE && inputModeActive == 0) {
            processButtonInput(button);
        }
        EXTI->PR |= (1 << 1);
    }
}

void EXTI2_IRQHandler(void) {
    if (EXTI->PR & (1 << 2)) {
        int button = isButtonPressed();
        if (button != BUTTON_OUT_OF_SCOPE && inputModeActive == 0) {
            processButtonInput(button);
        }
        EXTI->PR |= (1 << 2);
    }
}

void EXTI3_IRQHandler(void) {
    if (EXTI->PR & (1 << 3)) {
        int button = isButtonPressed();
        if (button != BUTTON_OUT_OF_SCOPE && inputModeActive == 0) {
            processButtonInput(button);
        }
        EXTI->PR |= (1 << 3);
    }
}

void EXTI4_IRQHandler(void) {
    if (EXTI->PR & (1 << 4)) {
        int button = isButtonPressed();
        if (button != BUTTON_OUT_OF_SCOPE && inputModeActive == 0) {
            processButtonInput(button);
        }
        EXTI->PR |= (1 << 4);
    }
}


void EXTI9_5_IRQHandler(void) {
    for (int i = 5; i <= 7; i++) {
        if (EXTI->PR & (1 << i)) {
            int button = isButtonPressed();
            if (button != BUTTON_OUT_OF_SCOPE && inputModeActive == 0) {
                processButtonInput(button);
            }
            EXTI->PR |= (1 << i);
        }
    }
}

