#include "includes.h"

#include "myfatfs.h"
#include "ff.h"

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
  GUI_SetColor(WHITE);
  GUI_SetBkColor(BLACK);

  // Init slave SPI
  CIRCULAR_QUEUE marlinQueue;
  SPI_Slave(&marlinQueue);

  // Endless loop
  uint8_t data;
  while(true)
  {
    // Check if SPI data is available
    if (SPI_SlaveGetData(&data))
    {
      // Parse data
      ST7920_ParseRecv(data);
    }
  }
}
