#include "GUI.h"
#include "includes.h"

void LCD_SetWindow(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey)
{
  LCD_WR_REG(0x2A);
  LCD_WR_DATA(sx>>8);LCD_WR_DATA(sx&0xFF);
  LCD_WR_DATA(ex>>8);LCD_WR_DATA(ex&0xFF);
  LCD_WR_REG(0x2B);
  LCD_WR_DATA(sy>>8);LCD_WR_DATA(sy&0xFF);
  LCD_WR_DATA(ey>>8);LCD_WR_DATA(ey&0xFF);
}

void GUI_Clear(uint16_t color)
{
  uint32_t index=0;
  LCD_SetWindow(0, 0, LCD_WIDTH-1, LCD_HEIGHT-1);
  LCD_WR_REG(0x2C);
  for(index=0; index<LCD_WIDTH*LCD_HEIGHT; index++)
  {
    LCD_WR_16BITS_DATA(color);
  }
}

void GUI_FillRectColor(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint16_t color)
{
  uint16_t i=0, j=0;
  LCD_SetWindow(sx, sy, ex-1, ey-1);
  LCD_WR_REG(0x2C);
  for(i=sx; i<ex; i++)
  {
    for(j=sy; j<ey; j++)
    {
      LCD_WR_16BITS_DATA(color);
    }
  }
}
