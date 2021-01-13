#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void Delay_init(uint32_t HCLK_Frequency);
void Delay_ms(uint16_t ms);
void Delay_us(uint32_t us);

#ifdef __cplusplus
}
#endif
