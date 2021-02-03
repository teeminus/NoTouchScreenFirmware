#ifndef _PIN_MKS_TFT32_V1_4_H_ // modify to actual filename !!!
#define _PIN_MKS_TFT32_V1_4_H_ // modify to actual filename !!!

//MCU type (STM32F10x, STM32F2xx)
#include "stm32f10x.h"

// LCD resolution, font and icon size
#ifndef TFT_RESOLUTION
  #define TFT_RESOLUTION
  #include "./Resolution/TFT_320X240.h"
#endif

// LCD interface
#ifndef TFTLCD_DRIVER
  #define TFTLCD_DRIVER HX8558  // Type of LCD driver, now support[ILI9488, ILI9341, ST7789, HX8558].
  #define TFTLCD_0_DEGREE_REG_VALUE   0xA4
  #define TFTLCD_180_DEGREE_REG_VALUE 0X64
#endif
//#define STM32_HAS_FSMC // FSMC 8080 interface(high speed), or normal IO interface(low speed)
#ifndef LCD_DATA_16BIT
  #define LCD_DATA_16BIT 1 // LCD data 16bit or 8bit
#endif

// LCD Backlight pin (PWM can adjust brightness)
//#define LCD_LED_PIN            PD14

// SD Card SPI pins
#define SD_SPI_SUPPORT
#ifdef SD_SPI_SUPPORT
  #define SD_LOW_SPEED  7 // 2^(SPEED+1) = 256 frequency division
  #define SD_HIGH_SPEED 1 // 2 frequency division
  #define SD_SPI        _SPI1
  #define SD_CS_PIN     PD11
#endif

// SD Card CD detect pin
#define SD_CD_PIN     PB15

// ST7920 Simulator SPI pins
#define ST7920_SPI    _SPI3            // uncomment to enable Marlin mode

#endif
