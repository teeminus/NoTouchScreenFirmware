#include "includes.h"
#include "GPIO_Init.h"

#if defined(KNOB_RGB_ENABLE)

// total 2.5us, run in 400Khz
#define NEOPIXEL_T0H_US 0.35  // Neopixel code 0 high level hold time in us
#define NEOPIXEL_T1H_US 2.15  // Neopixel code 1 high level hold time in us
uint16_t cycle, code_0_tim_h_cnt, code_1_tim_h_cnt;

void KnobLed_Init() {
    // Init hardware pin
    GPIO_InitSet(KNOB_LED_COLOR_PIN, MGPIO_MODE_OUT_PP, 0);
    GPIO_SetLevel(KNOB_LED_COLOR_PIN, 0);

    // Init timer
    RCC->APB1ENR |= 1 << 4;
    TIM6->CNT = 0;
    TIM6->PSC = 1 - 1;
    TIM6->SR = (uint16_t)~(1 << 0);

    // Calculate timings
    cycle = TIM7->PSC * (0.000001 * (NEOPIXEL_T0H_US + NEOPIXEL_T1H_US)) / 2 - 1;  // Neopixel frequency
    code_0_tim_h_cnt = cycle * (NEOPIXEL_T0H_US / (NEOPIXEL_T0H_US + NEOPIXEL_T1H_US));  // Code 0, High level hold time,
    code_1_tim_h_cnt = cycle - code_0_tim_h_cnt;

    // Turn on knob LED
    KnobLed_On();
}

void KnobLed_Set(uint32_t color) {
    // Disable interrupt, avoid disturbing the timing of WS2812
    __disable_irq();

    // Prepare timer
    TIM6->ARR = cycle;
    TIM6->CR1 |= 0x01;

    // Loop over all LEDs
    for (uint8_t led_num = 0; led_num < NEOPIXEL_PIXELS; ++led_num) {
        // Loop over all bits
        for (uint8_t bit = 0; bit < 24; ++bit, color <<= 1) {
            // Clear timer counter
            TIM6->CNT = 0;

            // Set high level
            WS2812_FAST_WRITE_HIGH();

            // Check if bit is set and wait accordingly
            if (color & (1 << 23)) {
                while (TIM6->CNT < code_1_tim_h_cnt);
            } else {
                while (TIM6->CNT < code_0_tim_h_cnt);
            }

            // Set low level
            WS2812_FAST_WRITE_LOW();
            
            // Wait for time to elapse
            while (!TIM6->SR);
            TIM6->SR = 0;
        }
    }

    // Stop timer
    TIM6->CR1 &= ~0x01;

    // Enable interrupt
    __enable_irq();
}

void KnobLed_On() {
    KnobLed_Set(KNOB_RGB_COLOR);
}

void KnobLed_Off() {
    KnobLed_Set(0x000000);
}

#endif // KNOB_RGB_ENABLE