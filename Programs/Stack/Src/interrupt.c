#include "interrupt.h"
#include "stm32f4xx_hal.h"
#include "input.h"       // enthält processButtonInput()

#define DEBOUNCE_MS 50
static uint32_t last_irq_time[8] = {0};

void initISR() {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOFEN;      // Clock für GPIOF aktivieren
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;     // Clock für SYSCFG aktivieren

    // EXTI für PF7 einrichten
    int i = 7;
    // EXTI7 liegt im EXTICR[1], an Position 4-7
    int reg_index = i / 4; 
    int pos = (i % 4) * 4;

    SYSCFG->EXTICR[reg_index] &= ~(0xF << pos);   // Entfernen der alten Auswahl
    SYSCFG->EXTICR[reg_index] |= (0x5 << pos);     // 0x5 = Port F (PF7)

    EXTI->RTSR |= (1 << i);  // Rising Edge für PF7
    EXTI->FTSR |= (1 << i);  // Falling Edge für PF7 (optional, wenn du Toggle möchtest)
    EXTI->IMR |= (1 << i);   // Interrupt für PF7 aktivieren

    // NVIC für EXTI7
    NVIC_SetPriority(EXTI9_5_IRQn, 0);  // Höchste Priorität
    NVIC_EnableIRQ(EXTI9_5_IRQn);       // Interrupt für EXTI9_5 aktivieren (dieser beinhaltet EXTI7)
}

void EXTI9_5_IRQHandler(void) {
    if (EXTI->PR & (1 << 7)) {  // Wenn Interrupt für PF7 ausgelöst wurde
        EXTI->PR |= (1 << 7);  // Interrupt-Flag zurücksetzen

        // Verhindern, dass der Interrupt sofort wieder ausgelöst wird
        uint32_t current_time = HAL_GetTick();
        if (current_time - last_irq_time[7] > DEBOUNCE_MS) {
            last_irq_time[7] = current_time;  // Update der Zeit des letzten Interrupts

            // Hier kannst du die Eingabeverarbeitung durchführen
            int button = isButtonPressed();
            if (button != BUTTON_OUT_OF_SCOPE) {
                processButtonInput(button);
            }
        }
    }
}
