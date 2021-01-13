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

#include "delay.h"

#include "Colors.h"
#include "lcd.h"
#include "LCD_Init.h"
#include "GUI.h"

#include "CircularQueue.h"
#include "spi_slave.h"

#include "ST7920_Simulator.h"

#ifndef ST7920_SPI
  #error "No ST7920"
#endif

#endif
