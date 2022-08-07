#pragma once

#ifdef __cplusplus
extern "C" {
#endif

void KnobLed_Init(uint32_t PCLK1_Frequency);

void KnobLed_On();
void KnobLed_Off();

#ifdef __cplusplus
}
#endif