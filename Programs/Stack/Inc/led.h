#ifndef LED_H
#define LED_H

#include "stm32f429xx.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_cortex.h"

// Define a struct to represent a GPIO pin
typedef struct {
    GPIO_TypeDef* port; // GPIO port number
    uint16_t pin;  // GPIO pin number
} GPIO_Pin;


// GPIO configuration
static const GPIO_Pin led_pins[] = {{GPIOE, GPIO_PIN_0}, {GPIOE, GPIO_PIN_1},
                                    {GPIOE, GPIO_PIN_2}, {GPIOE, GPIO_PIN_3},
                                    {GPIOE, GPIO_PIN_4}, {GPIOE, GPIO_PIN_5},
                                    {GPIOE, GPIO_PIN_6}, {GPIOE, GPIO_PIN_7}};

// Function to toggle the GPIO pin
void toggleGPIO(const GPIO_Pin* gpio);

#endif // LED_H 
