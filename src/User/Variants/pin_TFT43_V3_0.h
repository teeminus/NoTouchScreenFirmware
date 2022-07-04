#ifndef _PIN_TFT43_V3_0_H_ // modify to actual filename !!!
#define _PIN_TFT43_V3_0_H_ // modify to actual filename !!!

#ifndef TFT_RESOLUTION
  #define TFT_RESOLUTION
  #include "./Resolution/TFT_480X272.h"
#endif

// LCD interface
#ifndef TFTLCD_DRIVER
  #define TFTLCD_DRIVER SSD1963  // Type of LCD driver, now support[ILI9488, ILI9341, ST7789, HX8558, SSD1963].
  #define TFTLCD_DRIVER_SPEED         0x10 // SSD1963 needs slower speed
  #define TFTLCD_0_DEGREE_REG_VALUE   0x00
  #define TFTLCD_180_DEGREE_REG_VALUE 0x03
#endif

#ifndef SSD1963_LCD_PARA
  #define SSD1963_LCD_PARA
  #define SSD_DCLK_FREQUENCY   12 // 12Mhz

  #define SSD_HOR_PULSE_WIDTH  1
  #define SSD_HOR_BACK_PORCH   43
  #define SSD_HOR_FRONT_PORCH  2

  #define SSD_VER_PULSE_WIDTH  1
  #define SSD_VER_BACK_PORCH   12
  #define SSD_VER_FRONT_PORCH  1
#endif

// Neopixel LEDs number
#ifndef NEOPIXEL_PIXELS
  #define NEOPIXEL_PIXELS 2
#endif

#include "pin_TFT35_E3_V3_0.h"

#endif
