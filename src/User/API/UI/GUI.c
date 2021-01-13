#include "GUI.h"
#include "includes.h"

uint16_t foreGroundColor = WHITE;
uint16_t backGroundColor = BLACK;
GUI_TEXT_MODE guiTextMode = GUI_TEXTMODE_NORMAL;
GUI_NUM_MODE guiNumMode = GUI_NUMMODE_SPACE;

void LCD_SetWindow(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey)
{
  LCD_WR_REG(0x2A);
  LCD_WR_DATA(sx>>8);LCD_WR_DATA(sx&0xFF);
  LCD_WR_DATA(ex>>8);LCD_WR_DATA(ex&0xFF);
  LCD_WR_REG(0x2B);
  LCD_WR_DATA(sy>>8);LCD_WR_DATA(sy&0xFF);
  LCD_WR_DATA(ey>>8);LCD_WR_DATA(ey&0xFF);
}

void GUI_SetColor(uint16_t color)
{
  foreGroundColor = color;
}

uint16_t GUI_GetColor(void)
{
  return foreGroundColor;
}

void GUI_SetBkColor(uint16_t bkcolor)
{
  backGroundColor = bkcolor;
}

uint16_t GUI_GetBkColor(void)
{
  return backGroundColor;
}

void GUI_SetTextMode(GUI_TEXT_MODE mode)
{
  guiTextMode = mode;
}

GUI_TEXT_MODE GUI_GetTextMode(void)
{
  return guiTextMode;
}
void GUI_SetNumMode(GUI_NUM_MODE mode)
{
  guiNumMode = mode;
}

GUI_NUM_MODE GUI_GetNumMode(void)
{
  return guiNumMode;
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

static uint8_t pixel_limit_flag = 0;
static GUI_RECT pixel_limit_rect;

void GUI_SetRange(int16_t x0, int16_t y0, int16_t x1, int16_t y1)
{
  pixel_limit_flag = 1;
  pixel_limit_rect.x0 = x0;
  pixel_limit_rect.x1 = x1;
  pixel_limit_rect.y0 = y0;
  pixel_limit_rect.y1 = y1;
}

void GUI_CancelRange(void)
{
  pixel_limit_flag = 0;
}

void GUI_DrawPixel(int16_t x, int16_t y, uint16_t color)
{
  if(pixel_limit_flag == 1
    &&(x <  pixel_limit_rect.x0
     ||x >= pixel_limit_rect.x1
     ||y <  pixel_limit_rect.y0
     ||y >= pixel_limit_rect.y1))
    return ;

  LCD_SetWindow(x, y, x, y);
  LCD_WR_REG(0x2C);
  LCD_WR_16BITS_DATA(color);
}

void GUI_DrawPoint(uint16_t x, uint16_t y)
{
  LCD_SetWindow(x, y, x, y);
  LCD_WR_REG(0x2C);
  LCD_WR_16BITS_DATA(foreGroundColor);
}

void GUI_FillRect(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey)
{
  uint16_t i=0, j=0;
  LCD_SetWindow( sx, sy, ex-1, ey-1);
  LCD_WR_REG(0x2C);
  for(i=sx; i<ex; i++)
  {
    for(j=sy; j<ey; j++)
    {
      LCD_WR_16BITS_DATA(foreGroundColor);
    }
  }
}

void GUI_FillPrect(const GUI_RECT *rect)
{
  GUI_FillRect(rect->x0, rect->y0, rect->x1, rect->y1);
}

void GUI_ClearRect(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey)
{
  uint16_t i=0, j=0;
  LCD_SetWindow( sx, sy, ex-1, ey-1);
  LCD_WR_REG(0x2C);
  for(i=sx; i<ex; i++)
  {
    for(j=sy; j<ey; j++)
    {
      LCD_WR_16BITS_DATA(backGroundColor);
    }
  }
}

void GUI_ClearPrect(const GUI_RECT *rect)
{
  GUI_ClearRect(rect->x0, rect->y0, rect->x1, rect->y1);
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
void GUI_FillRectArry(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint8_t *arry)
{
  uint16_t i=0, j=0, color;
  LCD_SetWindow(sx, sy, ex-1, ey-1);
  LCD_WR_REG(0x2C);
  for(i=sx; i<ex; i++)
  {
    for(j=sy; j<ey; j++)
    {
      color = *arry;
      arry++;
      color = (color<<8) | (*arry);
      arry++;
      LCD_WR_16BITS_DATA(color);
    }
  }
}

//����
//x1,y1:�������?
//x2,y2:�յ�����
void GUI_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
  uint16_t t;
  int xerr=0, yerr=0, delta_x, delta_y, distance;
  int incx, incy, uRow, uCol;
  delta_x = x2 - x1; //������������
  delta_y = y2 - y1;
  uRow = x1;
  uCol = y1;
  if(delta_x > 0)
    incx = 1; //���õ�������
  else if(delta_x == 0)
    incx = 0;//��ֱ��
  else
  { incx = -1; delta_x = -delta_x;}

  if(delta_y > 0)
    incy = 1;
  else if(delta_y == 0)
    incy = 0;//ˮƽ��
  else
  { incy = -1; delta_y = -delta_y;}

  if(delta_x > delta_y)
    distance = delta_x; //ѡȡ��������������
  else
    distance = delta_y;

  for(t=0; t <= distance+1; t++ )//�������?
  {
    GUI_DrawPoint(uRow,uCol);//����
    xerr += delta_x;
    yerr += delta_y;
    if(xerr > distance)
    {
      xerr -= distance;
      uRow += incx;
    }
    if(yerr > distance)
    {
      yerr -= distance;
      uCol += incy;
    }
  }
}

#include "math.h"
void GUI_DrawAngleLine(uint16_t x, uint16_t y, uint16_t r, int16_t angle)
{
  uint16_t ex,ey;
  float a = angle * 3.1415926f / 180;
  ex = x + cos(a) * r;
  ey = y - sin(a) * r;
  GUI_DrawLine(x, y, ex, ey);
}
void GUI_HLine(uint16_t x1, uint16_t y, uint16_t x2)
{
  uint16_t i=0;
  LCD_SetWindow(x1, y, x2-1, y);
  LCD_WR_REG(0x2C);
  for(i=x1; i<x2; i++)
  {
    LCD_WR_16BITS_DATA(foreGroundColor);
  }
}
void GUI_VLine(uint16_t x, uint16_t y1, uint16_t y2)
{
  uint16_t i=0;
  LCD_SetWindow(x, y1, x, y2-1);
  LCD_WR_REG(0x2C);
  for(i=y1; i<y2; i++)
  {
    LCD_WR_16BITS_DATA(foreGroundColor);
  }
}


//������
//(x1,y1),(x2,y2):���εĶԽ�����
void GUI_DrawRect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
  GUI_HLine(x1, y1, x2);
  GUI_HLine(x1, y2-1, x2);
  GUI_VLine(x1, y1, y2);
  GUI_VLine(x2-1, y1, y2);
}

void GUI_DrawPrect(const GUI_RECT *rect)
{
  GUI_DrawRect(rect->x0, rect->y0, rect->x1, rect->y1);
}

//��ָ��λ�û�һ��ָ����С��Բ
//(x,y):���ĵ�
//r    :�뾶
void GUI_DrawCircle(uint16_t x0, uint16_t y0, uint16_t r)
{
  int16_t a = 0,
  b = r,
  di = 3 - (r << 1);             //�ж��¸���λ�õı�־

  while(a <= b)
  {
    GUI_DrawPoint(x0+a, y0-b);             //5
    GUI_DrawPoint(x0+b, y0-a);             //0
    GUI_DrawPoint(x0+b, y0+a);             //4
    GUI_DrawPoint(x0+a, y0+b);             //6
    GUI_DrawPoint(x0-a, y0+b);             //1
    GUI_DrawPoint(x0-b, y0+a);
    GUI_DrawPoint(x0-a, y0-b);             //2
    GUI_DrawPoint(x0-b, y0-a);             //7
    a++;
    //ʹ��Bresenham�㷨��Բ
    if(di<0)
      di += (a<<2) + 6;
    else
    {
      di += 10 + ((a-b)<<2);
      b--;
    }
  }
}
void  GUI_FillCircle(uint16_t x0, uint16_t y0, uint16_t r)
{
  int16_t  draw_x0, draw_y0;			// ��ͼ���������?
  int16_t  draw_x1, draw_y1;
  int16_t  draw_x2, draw_y2;
  int16_t  draw_x3, draw_y3;
  int16_t  draw_x4, draw_y4;
  int16_t  draw_x5, draw_y5;
  int16_t  draw_x6, draw_y6;
  int16_t  draw_x7, draw_y7;
  int16_t  fill_x0, fill_y0;			// �������ı�����ʹ�ô�ֱ�����?
  int16_t  fill_x1;
  int16_t  xx, yy;					// ��Բ���Ʊ���

  int16_t  di;						// ���߱���

  /* �������� */
  if(0 == r) return;

  /* �����?4�������?(0��90��180��270��)��������ʾ */
  draw_x0 = draw_x1 = x0;
  draw_y0 = draw_y1 = y0 + r;
  if(draw_y0 < LCD_HEIGHT)
  {
    GUI_DrawPoint(draw_x0, draw_y0);	// 90��
  }

  draw_x2 = draw_x3 = x0;
  draw_y2 = draw_y3 = y0 - r;
  if(draw_y2 >= 0)
  {
    GUI_DrawPoint(draw_x2, draw_y2);	// 270��
  }

  draw_x4 = draw_x6 = x0 + r;
  draw_y4 = draw_y6 = y0;
  if(draw_x4 < LCD_WIDTH)
  {
    GUI_DrawPoint(draw_x4, draw_y4);	// 0��
    fill_x1 = draw_x4;
  }
  else
  {
    fill_x1 = LCD_WIDTH;
  }

  fill_y0 = y0;							// �������������ʼ��fill_x0
  fill_x0 = x0 - r;						// �����������������fill_y1
  if(fill_x0<0)
  fill_x0 = 0;

  GUI_HLine(fill_x0, fill_y0, fill_x1);

  draw_x5 = draw_x7 = x0 - r;
  draw_y5 = draw_y7 = y0;
  if(draw_x5 >= 0)
  {
    GUI_DrawPoint(draw_x5, draw_y5);	// 180��
  }
  if(1==r) return;

  /* ʹ��Bresenham�����л�Բ */
  di = 3 - 2*r;							// ��ʼ�����߱���
  xx = 0;
  yy = r;
  while(xx < yy)
  {
    if(di<0)
    {
      di += 4*xx + 6;
    }
    else
    {
      di += 4*(xx - yy) + 10;

      yy--;
      draw_y0--;
      draw_y1--;
      draw_y2++;
      draw_y3++;
      draw_x4--;
      draw_x5++;
      draw_x6--;
      draw_x7++;
    }

    xx++;
    draw_x0++;
    draw_x1--;
    draw_x2++;
    draw_x3--;
    draw_y4++;
    draw_y5++;
    draw_y6--;
    draw_y7--;

    /* Ҫ�жϵ�ǰ���Ƿ�����Ч��Χ�� */
    if((draw_x0 <= LCD_WIDTH) && (draw_y0 >= 0))
    {
      GUI_DrawPoint(draw_x0, draw_y0);
    }
    if((draw_x1 >= 0) && (draw_y1 >= 0))
    {
      GUI_DrawPoint(draw_x1, draw_y1);
    }

    /* �ڶ���ˮֱ�����?(�°�Բ�ĵ�) */
    if(draw_x1 >= 0)
    {  /* �������������ʼ��fill_x0 */
      fill_x0 = draw_x1;
      /* �������������ʼ��fill_y0 */
      fill_y0 = draw_y1;
      if(fill_y0 > LCD_HEIGHT)
        fill_y0 = LCD_HEIGHT;
      if(fill_y0 < 0)
        fill_y0 = 0;
      /* �����������������fill_x1 */
      fill_x1 = x0*2 - draw_x1;
      if(fill_x1 > LCD_WIDTH)
        fill_x1 = LCD_WIDTH;
      GUI_HLine(fill_x0, fill_y0, fill_x1);
    }

    if((draw_x2 <= LCD_WIDTH) && (draw_y2 <= LCD_HEIGHT) )
    {
      GUI_DrawPoint(draw_x2, draw_y2);
    }

    if((draw_x3 >= 0) && (draw_y3 <= LCD_HEIGHT) )
    {
      GUI_DrawPoint(draw_x3, draw_y3);
    }

    /* ���ĵ㴹ֱ�����?(�ϰ�Բ�ĵ�) */
    if(draw_x3 >= 0)
    {  /* �������������ʼ��fill_x0 */
      fill_x0 = draw_x3;
      /* �������������ʼ��fill_y0 */
      fill_y0 = draw_y3;
      if(fill_y0 > LCD_HEIGHT)
        fill_y0 = LCD_HEIGHT;
      if(fill_y0 < 0)
        fill_y0 = 0;
      /* �����������������fill_x1 */
      fill_x1 = x0*2 - draw_x3;
      if(fill_x1 > LCD_WIDTH)
        fill_x1 = LCD_WIDTH;
      GUI_HLine(fill_x0, fill_y0, fill_x1);
    }

    if((draw_x4 <= LCD_WIDTH) && (draw_y4 >= 0))
    {
      GUI_DrawPoint(draw_x4, draw_y4);
    }
    if((draw_x5 >= 0) && (draw_y5 >= 0))
    {
      GUI_DrawPoint(draw_x5, draw_y5);
    }

    /* �����㴹ֱ�����?(�ϰ�Բ�ĵ�) */
    if(draw_x5 >= 0)
    {  /* �������������ʼ��fill_x0 */
      fill_x0 = draw_x5;
      /* �������������ʼ��fill_y0 */
      fill_y0 = draw_y5;
      if(fill_y0 > LCD_HEIGHT)
        fill_y0 = LCD_HEIGHT;
      if(fill_y0 < 0)
        fill_y0 = 0;
      /* �����������������fill_x1 */
      fill_x1 = x0*2 - draw_x5;
      if(fill_x1 > LCD_WIDTH)
        fill_x1 = LCD_WIDTH;
      GUI_HLine(fill_x0, fill_y0, fill_x1);
    }

    if((draw_x6 <= LCD_WIDTH) && (draw_y6 <= LCD_HEIGHT))
    {
      GUI_DrawPoint(draw_x6, draw_y6);
    }

    if((draw_x7 >= 0) && (draw_y7 <= LCD_HEIGHT))
    {
      GUI_DrawPoint(draw_x7, draw_y7);
    }

    /* �ڰ˵㴹ֱ�����?(�ϰ�Բ�ĵ�) */
    if(draw_x7 >= 0)
    {  /* �������������ʼ��fill_x0 */
      fill_x0 = draw_x7;
      /* �������������ʼ��fill_y0 */
      fill_y0 = draw_y7;
      if(fill_y0 > LCD_HEIGHT)
        fill_y0 = LCD_HEIGHT;
      if(fill_y0 < 0)
        fill_y0 = 0;
      /* �����������������fill_x1 */
      fill_x1 = x0*2 - draw_x7;
      if(fill_x1 > LCD_WIDTH)
        fill_x1 = LCD_WIDTH;
      GUI_HLine(fill_x0, fill_y0, fill_x1);
    }
  }
}
