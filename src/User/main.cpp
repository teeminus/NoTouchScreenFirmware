#include "includes.h"

#include "myfatfs.h"
#include "ff.h"
#include "timer.h"

#include "St7920Emulator.hpp"

#define ST7920_GXROWS  128
#define ST7920_GYROWS  64
#define ST7920_GXSTART ((LCD_WIDTH - ST7920_DOTSIZE * ST7920_GXROWS) / 2)
#define ST7920_GYSTART ((LCD_HEIGHT - ST7920_DOTSIZE * ST7920_GYROWS) / 2)

//#define ROTATE_180
#if defined(ROTATE_180)
  #define FILLRECT(X,Y,W,H,C) \
  { \
    uint16_t x0 = LCD_WIDTH - (X) - (W) - 1; \
    uint16_t y0 = LCD_HEIGHT - (Y) - (H) - 1; \
    GUI_FillRectColor(x0, y0, x0 + W, y0 + H, C); \
  }
#else
  #define FILLRECT(X,Y,W,H,C) \
    GUI_FillRectColor(X, Y, X + W, Y + H, C);
#endif

void clearDisplay() {
  // Clear ST7920 gui rect
  FILLRECT(ST7920_GXSTART,
           ST7920_GYSTART,
           ST7920_DOTSIZE * ST7920_GXROWS,
           ST7920_DOTSIZE * ST7920_GYROWS,
           BLACK);
}
void drawByte(uint8_t x, uint8_t y, uint8_t d) {
  // Loop over all bits
  for (uint8_t i = 0; i < 8; ++i, ++x) {
    // Check if bit is set
    if ((d & (1 << i)) > 0) {
      FILLRECT(ST7920_GXSTART + x * ST7920_DOTSIZE,
               ST7920_GYSTART + y * ST7920_DOTSIZE,
               ST7920_DOTSIZE,
               ST7920_DOTSIZE,
               WHITE);
    } else {
      FILLRECT(ST7920_GXSTART + x * ST7920_DOTSIZE,
              ST7920_GYSTART + y * ST7920_DOTSIZE,
              ST7920_DOTSIZE,
              ST7920_DOTSIZE,
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

  // Disable JTAG
  #ifdef DISABLE_JTAG
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); // disable JTAG, enable SWD
  #endif

  // Disable SWJ
  #ifdef DISABLE_DEBUG
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE); //disable JTAG & SWD
  #endif

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
  LCD_Init(&rccClocks);

  // Clear screen
  GUI_Clear(BLACK);

  // Show title
  const uint8_t pTitle[] = {0x7F, 0x02, 0x04, 0x08, 0x7F, 0x38, 0x44, 0x44, 0x44, 0x38, 0x01, 0x01, 0x7F, 0x01, 0x01, 0x38, 0x44, 0x44, 0x44, 0x38, 0x3C, 0x40, 0x20, 0x7C, 0x00, 0x38, 0x44, 0x44, 0x44, 0x28, 0x7F, 0x04, 0x04, 0x78, 0x00, 0x7F, 0x09, 0x09, 0x09, 0x01, 0x3C, 0x60, 0x30, 0x60, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x20, 0x40, 0x20, 0x1F, 0x00, 0x42, 0x7F, 0x40, 0x00, 0x00, 0x60, 0x60, 0x00, 0x00, 0x62, 0x51, 0x49, 0x49, 0x46};
  for (uint16_t i = 0, x = (LCD_WIDTH - sizeof(pTitle) / 5 * 6) / 2; i < sizeof(pTitle); ++i, ++x) {
    for (uint8_t y = 0; y < 8; ++y) {
      if ((pTitle[i] & (1 << y)) > 0) {
        FILLRECT(x, y, 1, 1, WHITE);
      }
    }
    if ((i % 5) == 4) {
      ++x;
    }
  }

  // Create emulator handle
  St7920Emulator st7920Emulator(clearDisplay, drawByte);

  // Show startup message
  const uint8_t pStartupMessage[] = {0xF8, 0x30, 0x00, 0x00, 0x60, 0x00, 0xC0, 0xF8, 0x80, 0x00, 0xFA, 0x50, 0x30, 0x50, 0x40, 0x30, 0x70, 0x30, 0x90, 0x30, 0x20, 0x30, 0x00, 0x40, 0x50, 0x60, 0xD0, 0x70, 0x50, 0x60, 0xC0, 0x60, 0x10, 0x70, 0x40, 0x60, 0xF0, 0x70, 0x20, 0xF8, 0x90, 0x00, 0xFA, 0x70, 0x20, 0x60, 0x50, 0x60, 0x10, 0x60, 0x40, 0x70, 0x90};
  for (uint8_t i = 0; i < sizeof(pStartupMessage); ++i) {
    st7920Emulator.parseSerialData(pStartupMessage[i]);
  }
  st7920Emulator.reset(false);

  // Add first part of header line
  FILLRECT(0, 7, (LCD_WIDTH - sizeof(pTitle) / 5 * 6) / 2, 1, WHITE);

  // Init slave SPI
  CIRCULAR_QUEUE spiQueue;
  SPI_Slave(&spiQueue);

  // Check if lcd idle off is enabled
#if defined(LCD_IDLE_OFF)
  // Init timer
  Timer_Init(&rccClocks);

  // Loop veriables
  bool bScreenOn = true;
  uint8_t ui8CurrentEncoder;
  uint8_t ui8LastEncoder = 0;
  uint32_t ui32CurrentMs;
  uint32_t ui32LastActive = 0;
#endif

  // Add second part of header line
  FILLRECT((LCD_WIDTH + sizeof(pTitle) / 5 * 6) / 2, 7, (LCD_WIDTH - sizeof(pTitle) / 5 * 6) / 2, 1, WHITE);

  // Variables for SPI data received indicator
#if defined(SPI_DATA_RECEIVED_INDICATOR)
  uint16_t ui16X = 0, ui16Y = 0;
  uint16_t ui16Color = WHITE;
#endif

  // Endless loop
  uint8_t data;
  while(true) {
    // Check if SPI data is available
    if (SPI_SlaveGetData(&data)) {
      // Parse data
      st7920Emulator.parseSerialData(data);

      // Update SPI data received indicator
#if defined(SPI_DATA_RECEIVED_INDICATOR)
      // Draw new pixel
      FILLRECT(ui16X, ui16Y, 1, 1, ui16Color);

      // Move to next pixel
      if (ui16X < ((LCD_WIDTH - sizeof(pTitle) / 5 * 6) / 2 - 2)) {
        ++ui16X;
      } else if (ui16X == ((LCD_WIDTH - sizeof(pTitle) / 5 * 6) / 2 - 2)) {
        ui16X = (LCD_WIDTH + sizeof(pTitle) / 5 * 6) / 2;
      } else if (ui16X < (LCD_WIDTH - 1)) {
        ++ui16X;
      } else {
        ui16X = 0;

        // Wrap to next line
        if (ui16Y < 6) {
          ++ui16Y;
        } else {
          ui16Y = 0;

          // Invert color
          if (ui16Color == WHITE) {
            ui16Color = BLACK;
          } else {
            ui16Color = WHITE;
          }
        }
      }
#endif
    }

    // Check if lcd idle off is enabled
#if defined(LCD_IDLE_OFF)
    // Read current encoder value
    ui8CurrentEncoder = Encoder_Read();

    // Get current time
    ui32CurrentMs = Timer_GetTimerMs();

    // Compare to last value
    if (ui8CurrentEncoder != ui8LastEncoder) {
      // Store current value
      ui8LastEncoder = ui8CurrentEncoder;

      // Check if screen is off
      if (!bScreenOn) {
        // Turn on screen
        LCD_LED_On();

        // Set flag
        bScreenOn = true;
      }

      // Store current time
      ui32LastActive = ui32CurrentMs;
    }
    // Check if screen is on
    else if (bScreenOn) {
      // Get difference to last active timestamp
      if (ui32CurrentMs >= ui32LastActive) {
        ui32CurrentMs = ui32CurrentMs - ui32LastActive;
      } else {
        ui32CurrentMs = 0xFFFFFFFF - ui32LastActive + ui32CurrentMs + 1;
      }

      // Check inactivity time
      if (ui32CurrentMs >= LCD_IDLE_TIMEOUT_SEC * 1000) {
        // Turn off screen
        LCD_LED_Off();

        // Clear flag
        bScreenOn = false;
      }
    }
#endif
  }
}
