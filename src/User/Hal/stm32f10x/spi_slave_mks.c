#include "spi_slave.h"
#include "spi.h"
#include "GPIO_Init.h"
#include "stdlib.h"
#include "stm32f10x_conf.h"

#if defined(MKS_32_V1_4) || defined (MKS_28_V1_0)

#if defined(ST7920_SPI)
//TODO:
//now support SPI3 and PB1 CS only
//more compatibility changes are needed
//Config for SPI Channel
#if ST7920_SPI == _SPI1
  #define ST7920_SPI_NUM          SPI1
#elif ST7920_SPI == _SPI2
  #define ST7920_SPI_NUM          SPI2
#elif ST7920_SPI == _SPI3
  #define ST7920_SPI_NUM          SPI3
#endif

volatile CIRCULAR_QUEUE *spi_queue = NULL;

void SPI_Enable(u8 mode)
{
  ST7920_SPI_NUM->CR1 = (0<<15)        // 0:2-line 1: 1-line
                      | (0<<14)        // in bidirectional mode 0:read only 1: read/write
                      | (0<<13)        // 0:disable CRC 1:enable CRC
                      | (0<<12)        // 0:Data phase (no CRC phase) 1:Next transfer is CRC (CRC phase)
                      | (0<<11)        // 0:8-bit data frame 1:16-bit data frame
                      | (1<<10)        // 0:Full duplex 1:Receive-only
                      | (1<<9)         // 0:enable NSS 1:disable NSS (Software slave management)
                      | (0<<8)         // This bit has an effect only when the SSM bit is set. The value of this bit is forced onto the NSS pin and the IO value of the NSS pin is ignored
                      | (0<<7)         // 0:MSB 1:LSB
                      | (7<<3)         // bit3-5   000:fPCLK/2    001:fPCLK/4    010:fPCLK/8     011:fPCLK/16
                                       //          100:fPCLK/32   101:fPCLK/64   110:fPCLK/128   111:fPCLK/256
                      | (0<<2)         // 0:Slave 1:Master
                      | (mode<<1)      // CPOL
//                      | (mode<<0);   // CPHA
                      | (1<<0);        // always use 1 instead of "mode"!

  ST7920_SPI_NUM->CR2 |= 1<<6;         // RX buffer not empty interrupt enable SPI_I2S_IT_RXNE
  ST7920_SPI_NUM->CR1 |= (1<<6);
}

void SPI_Slave(CIRCULAR_QUEUE *queue)
{
  // initializes the initial queue indexes before the queue is used.
  // Otherwise, dirty values will let the system probably freeze when the queue is used
  spi_queue = queue;
  spi_queue->index_r = spi_queue->index_w = 0;

  // Reset SPI3
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI3, ENABLE);
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI3, DISABLE);

  // Init SPI
  // if enabled, it avoids any SPI3 CS pin usage and free the MISO (PB4 pin) for encoder pins
#ifndef SPI3_PIN_SMART_USAGE
  SPI_GPIO_Init(ST7920_SPI);
  GPIO_InitSet(SPI3_CS_PIN, MGPIO_MODE_IPU, 0);
#endif

  // Configure SPI interrupt
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel = SPI3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  // Enable SPI clock
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3, ENABLE);

  // if enabled, it avoids any SPI3 CS pin usage and free the MISO (PB4 pin) for encoder pins
#ifndef SPI3_PIN_SMART_USAGE // not needed, you can also comment out this line! ?????????????????
  // Connect GPIOB1 to the interrupt line
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource1);

  // Set interrupt line 1 bit external falling edge interrupt
  EXTI_InitTypeDef EXTI_InitStructure;
  EXTI_InitStructure.EXTI_Line = EXTI_Line1;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  // Enable CS interrupt
  NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  // Check if we need to enable the SPI interface
  if ((GPIOB->IDR & (1<<1)) != 0) {
    SPI_Enable(1);
  }
#else
  // Enable SPI
  SPI_Enable(0);
#endif
}

void SPI_SlaveDeinit() {
  // Disable interrupts
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel = SPI3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
  NVIC_Init(&NVIC_InitStructure);
  NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
  NVIC_Init(&NVIC_InitStructure);

  // Reset SPI
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI3, ENABLE);
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI3, DISABLE);
}

void EXTI1_IRQHandler(void)
{
  // Check CS pin
  if ((GPIOB->IDR & (1<<1)) != 0) {
    // Enable SPI
    SPI_Enable(1);
  } else {
    // Reset SPI3
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI3, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI3, DISABLE);
  }

  // Clear interrupt status register
  EXTI->PR = 1<<1;
}

void SPI3_IRQHandler(void)
{
  spi_queue->data[spi_queue->index_w] = ST7920_SPI_NUM->DR;
  spi_queue->index_w = (spi_queue->index_w + 1) % CIRCULAR_QUEUE_SIZE;
}

bool SPI_SlaveGetData(uint8_t *data)
{
  if (spi_queue->index_r != spi_queue->index_w)
  {
    *data = spi_queue->data[spi_queue->index_r];
    spi_queue->index_r = (spi_queue->index_r + 1) % CIRCULAR_QUEUE_SIZE;
    return true;
  }
  return false;
}

#endif             // endif for #if defined(ST7920_SPI)

#endif             // endif for #if defined(MKS_32_V1_4) || defined (MKS_28_V1_0)
