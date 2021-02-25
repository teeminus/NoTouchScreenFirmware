#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LCD_ENCODER_SUPPORT (defined(LCD_ENCA_PIN) && defined(LCD_ENCB_PIN) && defined(LCD_BTN_PIN))
#define LCD_ENCODER_A_SET 1
#define LCD_ENCODER_B_SET 2
#define LCD_ENCODER_BTN_SET 4

void Encoder_Init();
uint8_t Encoder_Read();

#ifdef __cplusplus
}
#endif