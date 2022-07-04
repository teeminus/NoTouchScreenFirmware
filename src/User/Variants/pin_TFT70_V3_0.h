#ifndef _PIN_TFT70_V3_0_H_ // modify to actual filename !!!
#define _PIN_TFT70_V3_0_H_ // modify to actual filename !!!

//MCU type (STM32F10x, STM32F2xx, STM32F4xx)
#include "stm32f4xx.h"

// LCD resolution, font and icon size
#ifndef TFT_RESOLUTION
  #define TFT_RESOLUTION
  #include "./Resolution/TFT_800X480.h"
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
  #define SSD_DCLK_FREQUENCY   30 // 30Mhz

  #define SSD_HOR_PULSE_WIDTH  1
  #define SSD_HOR_BACK_PORCH   46
  #define SSD_HOR_FRONT_PORCH  210

  #define SSD_VER_PULSE_WIDTH  3
  #define SSD_VER_BACK_PORCH   33
  #define SSD_VER_FRONT_PORCH  22
#endif

#define STM32_HAS_FSMC // FSMC 8080 interface(high speed), or normal IO interface(low speed)
#ifndef LCD_DATA_16BIT
  #define LCD_DATA_16BIT 1 // LCD data 16bit or 8bit
#endif

// Debug disable, free pins for other function
//#define DISABLE_JTAG  // free JTAG(PB3/PB4) for SPI3
//#define DISABLE_DEBUG // free all pins

// LCD Backlight pin (PWM can adjust brightness)
#define LCD_LED_PIN            PD12
#define LCD_LED_PIN_ALTERNATE  GPIO_AF_TIM4
#define LCD_LED_PWM_CHANNEL    _TIM4_CH1

// Knob LED Color pins
#ifndef KNOB_LED_COLOR_PIN
  #define KNOB_LED_COLOR_PIN       PC7
  #define WS2812_FAST_WRITE_HIGH() GPIOC->BSRRL = 1 << 7
  #define WS2812_FAST_WRITE_LOW()  GPIOC->BSRRH = 1 << 7
#endif

// Neopixel LEDs number
#ifndef NEOPIXEL_PIXELS
  #define NEOPIXEL_PIXELS 2
#endif

// SD Card SPI pins
#define SD_SPI_SUPPORT
#ifdef SD_SPI_SUPPORT
  #define SD_LOW_SPEED  7 // 2^(SPEED+1) = 256 frequency division
  #define SD_HIGH_SPEED 0 // 2 frequency division
  #define SD_SPI        _SPI1
  #define SD_CS_PIN     PA4
#endif

// SD Card CD detect pin
#define SD_CD_PIN     PC4

// ST7920 Simulator SPI pins
#define ST7920_SPI    _SPI2

// LCD Encoder support
#define LCD_ENCA_PIN    PA8
#define LCD_ENCB_PIN    PC9
#define LCD_BTN_PIN     PC8
#define LCD_ENC_EN_PIN  PC6

// PS_ON
#ifndef PS_ON_PIN
  #define PS_ON_PIN      PC12 // The string on TFT35 V3.0 board(PA12) is wrong, PC12 is the correct IO
#endif

#endif
