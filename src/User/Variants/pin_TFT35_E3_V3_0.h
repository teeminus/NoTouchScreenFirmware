#ifndef _PIN_TFT35_E3_V3_0_H_ // modify to actual filename !!!
#define _PIN_TFT35_E3_V3_0_H_ // modify to actual filename !!!

// Knob LED Color pins
#ifndef KNOB_LED_COLOR_PIN
  #define KNOB_LED_COLOR_PIN       PC7
  #define WS2812_FAST_WRITE_HIGH() GPIOC->BSRRL = 1 << 7
  #define WS2812_FAST_WRITE_LOW()  GPIOC->BSRRH = 1 << 7
#endif

// Neopixel LEDs number
#ifndef NEOPIXEL_PIXELS
  #define NEOPIXEL_PIXELS 4
#endif

#include "pin_TFT35_V3_0.h"

#endif
