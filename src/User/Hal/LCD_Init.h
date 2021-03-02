#ifndef _LCD_INIT_H_
#define _LCD_INIT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "variants.h"

#if LCD_DATA_16BIT == 1
  #define LCD_WR_16BITS_DATA(c) do{ LCD_WR_DATA(c); }while(0)
#else
  #define LCD_WR_16BITS_DATA(c) do{ LCD_WR_DATA(((c)>>8)&0xFF); LCD_WR_DATA((c)&0xFF); }while(0)
#endif

void LCD_RefreshDirection(void);
void LCD_Init(RCC_ClocksTypeDef* rccClocks, uint16_t ui16BackColor);

#ifdef LCD_LED_PIN
void LCD_LED_On();
void LCD_LED_Off();
#endif

#ifdef __cplusplus
}
#endif

#endif
