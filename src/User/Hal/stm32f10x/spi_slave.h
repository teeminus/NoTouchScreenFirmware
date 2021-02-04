#ifndef _SPI_SLAVE_H_
#define _SPI_SLAVE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "CircularQueue.h"

void SPI_Slave(CIRCULAR_QUEUE *queue);
bool SPI_SlaveGetData(uint8_t *data);

#ifdef __cplusplus
}
#endif

#endif
