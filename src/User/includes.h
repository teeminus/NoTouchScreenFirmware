#ifndef _INCLUDES_H_
#define _INCLUDES_H_

#include "variants.h"

#define STRINGIFY_(M) #M
#define STRINGIFY(M) STRINGIFY_(M)
#define FIRMWARE_NAME STRINGIFY(HARDWARE) "." STRINGIFY(SOFTWARE_VERSION)

#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "features.h"
#include "delay.h"

#include "Colors.h"
#include "lcd.h"
#include "LCD_Init.h"
#include "GUI.h"

#include "CircularQueue.h"
#include "spi_slave.h"
#include "encoder.h"

#ifndef ST7920_SPI
  #error "No ST7920"
#endif
#if defined(LCD_PWM_DIMMER)
  #if !defined(LCD_LED_PIN)
    #error "LCD_PWM_DIMMER requires LCD_LED_PIN"
  #endif
  #if !defined(LCD_LED_PWM_CHANNEL)
    #error "LCD_PWM_DIMMER requires LCD_LED_PWM_CHANNEL"
  #endif
#endif
#if defined(LCD_IDLE_OFF)
  #if !LCD_ENCODER_SUPPORT
    #error "LCD_IDLE_OFF requires encoder"
  #endif
  #if !defined(LCD_LED_PIN)
    #error "LCD_IDLE_OFF requires LCD_LED_PIN"
  #endif
#endif

#endif
