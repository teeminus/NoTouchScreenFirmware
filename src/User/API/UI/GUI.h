#ifndef _GUI_H_
#define _GUI_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

void GUI_Clear(uint16_t color);
void GUI_FillRectColor(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint16_t color);

#ifdef __cplusplus
}
#endif

#endif
