#ifndef _CIRCULAR_QUEUE_H_
#define _CIRCULAR_QUEUE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define CIRCULAR_QUEUE_SIZE (2050 * 5)

typedef struct
{
  uint8_t  data[CIRCULAR_QUEUE_SIZE];                      // Data buffer
  uint16_t index_r;                                        // Ring buffer read position
  uint16_t index_w;                                        // Ring buffer write position
} CIRCULAR_QUEUE;

#ifdef __cplusplus
}
#endif

#endif
