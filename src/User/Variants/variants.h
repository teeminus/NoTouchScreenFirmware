#ifndef _VARIANTS_H_
#define _VARIANTS_H_

/*
* hardware source
* TIM3 for Buzzer timer
* TIM6 for Neopixel RGB
* TIM7 for OS Timer
*/

// Type of LCD driver, now support[ILI9488, ILI9341, ST7789, HX8558, SSD1963].
#define ILI9488 0
#define ILI9341 1
#define ST7789  2
#define HX8558  3
#define SSD1963 4

#if defined(TFT24_V1_1)
  #include "pin_TFT24_V1_1.h"
#elif defined(TFT28_V3_0)
  #include "pin_TFT28_V3_0.h"
#elif defined(TFT35_V3_0)
  #include "pin_TFT35_V3_0.h"
#elif defined(TFT43_V3_0)
  #include "pin_TFT43_V3_0.h"
#elif defined(TFT50_V3_0)
  #include "pin_TFT50_V3_0.h"
#elif defined(TFT70_V3_0)
  #include "pin_TFT70_V3_0.h"
#elif defined(TFT35_E3_V3_0)
  #include "pin_TFT35_E3_V3_0.h"
#elif defined(TFT35_B1_V3_0)
  #include "pin_TFT35_B1_V3_0.h"
#elif defined(MKS_32_V1_4)
  #include "pin_MKS_TFT32_V1_4.h"
#elif defined(MKS_28_V1_0)
  #include "pin_MKS_TFT28_V1_0.h"
#endif

#define LCD_DRIVER_IS(n) (TFTLCD_DRIVER == n)

#endif
