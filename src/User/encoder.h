#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LCD_ENCODER_SUPPORT (defined(LCD_ENCA_PIN) && defined(LCD_ENCB_PIN) && defined(LCD_BTN_PIN))

void Encoder_Init();
uint8_t Encoder_Read();

#ifdef __cplusplus
}
#endif