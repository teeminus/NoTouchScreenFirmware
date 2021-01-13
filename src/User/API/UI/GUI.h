#ifndef _GUI_H_
#define _GUI_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

enum
{
  LEFT=0,
  RIGHT,
  CENTER,
  TOP,
  BOTTOM,
};

typedef enum
{
  GUI_TEXTMODE_TRANS,
  GUI_TEXTMODE_NORMAL,
}GUI_TEXT_MODE;

typedef enum
{
  GUI_NUMMODE_SPACE,
  GUI_NUMMODE_ZERO,
}GUI_NUM_MODE;

typedef struct
{
  int16_t x, y;
}GUI_POINT;

typedef struct
{
  int16_t x0, y0, x1, y1;
}GUI_RECT;


void LCD_SetCursor(uint16_t Xpos, uint16_t Ypos);
void LCD_SetWindow(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey);

void GUI_SetColor(uint16_t color);
uint16_t GUI_GetColor(void);
void GUI_SetBkColor(uint16_t bkcolor);
uint16_t GUI_GetBkColor(void);
void GUI_SetTextMode(GUI_TEXT_MODE mode);
GUI_TEXT_MODE GUI_GetTextMode(void);
void GUI_SetNumMode(GUI_NUM_MODE mode);
GUI_NUM_MODE GUI_GetNumMode(void);

void GUI_Clear(uint16_t color);
void GUI_DrawPoint(uint16_t x, uint16_t y);
void GUI_FillRect(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey);
void GUI_FillPrect(const GUI_RECT *rect);
void GUI_ClearRect(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey);
void GUI_ClearPrect(const GUI_RECT *rect);
void GUI_FillRectColor(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint16_t color);
void GUI_FillRectArry(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint8_t *arry);
void GUI_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void GUI_HLine(uint16_t x1, uint16_t y, uint16_t x2);
void GUI_VLine(uint16_t x1, uint16_t y1, uint16_t y2);
void GUI_DrawRect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void GUI_DrawPrect(const GUI_RECT *rect);
void GUI_DrawCircle(uint16_t x0, uint16_t y0, uint16_t r);
void GUI_FillCircle(uint16_t x0, uint16_t y0, uint16_t r);

void GUI_SetRange(int16_t x0, int16_t y0, int16_t x1, int16_t y1);
void GUI_CancelRange(void);
void GUI_DrawPixel(int16_t x, int16_t y, uint16_t color);

#ifdef __cplusplus
}
#endif

#endif
