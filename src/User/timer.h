#pragma once

#include "variants.h"

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void Timer_Init(RCC_ClocksTypeDef* rccClocks);
uint32_t Timer_GetTimerMs();

#ifdef __cplusplus
}
#endif
