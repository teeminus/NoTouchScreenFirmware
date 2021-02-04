#include "includes.h"

#include "myfatfs.h"
#include "ff.h"

#include "St7920Emulator.hpp"

#define ST7920_GXROWS  128
#define ST7920_GYROWS  64
#define ST7920_GXSTART ((LCD_WIDTH - ST7920_DOTSIZE * ST7920_GXROWS) / 2)
#define ST7920_GYSTART ((LCD_HEIGHT - ST7920_DOTSIZE * ST7920_GYROWS) / 2)

void clearDisplay() {
  // Clear ST7920 gui rect
  GUI_FillRectColor(ST7920_GXSTART,
                    ST7920_GYSTART,
                    ST7920_GXSTART + ST7920_DOTSIZE * ST7920_GXROWS,
                    ST7920_GYSTART + ST7920_DOTSIZE * ST7920_GYROWS,
                    BLACK);
}
void drawByte(uint8_t x, uint8_t y, uint8_t d) {
  // Loop over all bits
  for (uint8_t i = 0; i < 8; ++i, ++x) {
    // Check if bit is set
    if ((d & (1 << i)) > 0) {
      GUI_FillRectColor(ST7920_GXSTART + x * ST7920_DOTSIZE,
                        ST7920_GYSTART + y * ST7920_DOTSIZE,
                        ST7920_GXSTART + (x + 1)* ST7920_DOTSIZE,
                        ST7920_GYSTART + (y + 1)* ST7920_DOTSIZE,
                        WHITE);
    } else {
      GUI_FillRectColor(ST7920_GXSTART + x * ST7920_DOTSIZE,
                        ST7920_GYSTART + y * ST7920_DOTSIZE,
                        ST7920_GXSTART + (x + 1)* ST7920_DOTSIZE,
                        ST7920_GYSTART + (y + 1)* ST7920_DOTSIZE,
                        BLACK);
    }
  }
}

int main(void)
{
  // Set vector table offset
  SCB->VTOR = VECT_TAB_FLASH;

  // Get clock frequency
  RCC_ClocksTypeDef rccClocks;
  RCC_GetClocksFreq(&rccClocks);

  // Init NVIC priority group
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

  // Init delay
  Delay_init(rccClocks.HCLK_Frequency);

  // Mount SD card
  if(mountSDCard())
  {
    // Check if firmware binary exists
    if (f_file_exists(FIRMWARE_NAME ".bin"))
    {
      // Check of old firmware binary exists
      if (f_file_exists(FIRMWARE_NAME ".CUR"))
      {
        // Delete old firmware binary
        f_unlink(FIRMWARE_NAME ".CUR");
      }

      // Rename current firmware binary
      f_rename(FIRMWARE_NAME ".bin", FIRMWARE_NAME ".CUR");
    }
  }

  // Init LCD
  LCD_Init();

  // Clear screen
  GUI_Clear(BLACK);

  // Show title
  const uint8_t pTitle[] = {0x7F, 0x02, 0x04, 0x08, 0x7F, 0x38, 0x44, 0x44, 0x44, 0x38, 0x01, 0x01, 0x7F, 0x01, 0x01, 0x38, 0x44, 0x44, 0x44, 0x38, 0x3C, 0x40, 0x20, 0x7C, 0x00, 0x38, 0x44, 0x44, 0x44, 0x28, 0x7F, 0x04, 0x04, 0x78, 0x00, 0x7F, 0x09, 0x09, 0x09, 0x01, 0x3C, 0x60, 0x30, 0x60, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x20, 0x40, 0x20, 0x1F, 0x00, 0x42, 0x7F, 0x40, 0x00, 0x00, 0x60, 0x60, 0x00, 0x00, 0x00, 0x42, 0x7F, 0x40, 0x00};
  for (uint16_t i = 0, x = (LCD_WIDTH - sizeof(pTitle) / 5 * 6) / 2; i < sizeof(pTitle); ++i, ++x) {
    for (uint8_t y = 0; y < 8; ++y) {
      if ((pTitle[i] & (1 << y)) > 0) {
        GUI_FillRectColor(x, y, x + 1, y + 1, WHITE);
      }
    }
    if ((i % 5) == 4) {
      ++x;
    }
  }

  // Create emulator handle
  St7920Emulator st7920Emulator(clearDisplay, drawByte);

  // Init slave SPI
  SPI_Slave();

  // Endless loop
  uint8_t data;
  while(true)
  {
    // Check if SPI data is available
    if (SPI_SlaveGetData(&data))
    {
      // Parse data
      st7920Emulator.parseSerialData(data);
    }
  }
}
