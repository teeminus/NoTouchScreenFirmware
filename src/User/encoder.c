#include "includes.h"
#include "GPIO_Init.h"

void Encoder_Init() {
  // Check if encoder is supported
  #if LCD_ENCODER_SUPPORT
    // Configure pins
    GPIO_InitSet(LCD_ENCA_PIN, MGPIO_MODE_IPU, 0);
    GPIO_InitSet(LCD_ENCB_PIN, MGPIO_MODE_IPU, 0);
    GPIO_InitSet(LCD_BTN_PIN, MGPIO_MODE_IPU, 0);

    // Check if encoder enable pin is present
    #if defined(LCD_ENC_EN_PIN)
      // Configure encoder enable pin
      GPIO_InitSet(LCD_ENC_EN_PIN, MGPIO_MODE_OUT_PP, 0);

      // Set encoder enable high
      GPIO_SetLevel(LCD_ENC_EN_PIN, 1);
    #endif
  #endif
}

uint8_t Encoder_Read() {
  // Return value
  uint8_t ui8Encoder = 0;

  // Check if encoder is supported
  #if LCD_ENCODER_SUPPORT
    // Check encoder pins
    if (GPIO_GetLevel(LCD_ENCA_PIN) == 0) {
        ui8Encoder += 1;
    }
    if (GPIO_GetLevel(LCD_ENCB_PIN) == 0) {
        ui8Encoder += 2;
    }
    if (GPIO_GetLevel(LCD_BTN_PIN) == 0) {
        ui8Encoder += 4;
    }
  #endif

  // Return result
  return ui8Encoder;
}