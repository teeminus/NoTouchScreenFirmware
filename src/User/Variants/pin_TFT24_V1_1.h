#ifndef _PIN_TFT24_V1_1_H_ // modify to actual filename !!!
#define _PIN_TFT24_V1_1_H_ // modify to actual filename !!!

//MCU type (STM32F10x, STM32F2xx)
#include "stm32f10x.h"

// LCD resolution, font and icon size
#ifndef TFT_RESOLUTION
  #define TFT_RESOLUTION
  #include "./Resolution/TFT_320X240.h"
#endif

// LCD interface
#ifndef TFTLCD_DRIVER
  #define TFTLCD_DRIVER ILI9341  // Type of LCD driver, now support[ILI9488, ILI9341, ST7789, HX8558].
  #define TFTLCD_DRIVER_SPEED         0x03
  #define TFTLCD_0_DEGREE_REG_VALUE   0X68
  #define TFTLCD_180_DEGREE_REG_VALUE 0XA8
#endif
//#define STM32_HAS_FSMC // FSMC 8080 interface(high speed), or normal IO interface(low speed)
#ifndef LCD_DATA_16BIT
  #define LCD_DATA_16BIT 1 // LCD data 16bit or 8bit
#endif

// Debug disable, free pins for other function
//#define DISABLE_JTAG  // free JTAG(PB3/PB4) for SPI3
#define DISABLE_DEBUG // free all pins

// LCD Backlight pin (PWM can adjust brightness)
#define LCD_LED_PIN            PA8
#define LCD_LED_PIN_ALTERNATE  0
#define LCD_LED_PWM_CHANNEL    _TIM1_CH1

// SD Card SPI pins
#define SD_SPI_SUPPORT
#ifdef SD_SPI_SUPPORT
  #define SD_LOW_SPEED  7 // 2^(SPEED+1) = 256 frequency division
  #define SD_HIGH_SPEED 1 // 2 frequency division
  #define SD_SPI        _SPI1
  #define SD_CS_PIN     PA4
#endif

// SD Card CD detect pin
#define SD_CD_PIN     PA13

// ST7920 Simulator SPI pins
#define ST7920_SPI    _SPI2

// LCD Encoder support
#define LCD_ENCA_PIN    PB0
#define LCD_ENCB_PIN    PB1
#define LCD_BTN_PIN     PB2
#define LCD_ENC_EN_PIN  PB11

#endif
