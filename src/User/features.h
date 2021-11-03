#pragma once

// Screen colors
#define LCD_COLOR_FOREGROUND WHITE
#define LCD_COLOR_BACKGROUND BLACK

// Enable fullscreen mode
#define LCD_FULLSCREEN

// Mirror screen horizontally
//#define LCD_MIRROR_HORIZONTALLY

// Mirror screen vertically
//#define LCD_MIRROR_VERTICALLY

// Rotate screen by 180°
//#define LCD_ROTATE_180
#if defined(LCD_ROTATE_180)
    #define LCD_MIRROR_HORIZONTALLY
    #define LCD_MIRROR_VERTICALLY
#endif

// Enable LCD backlight idle off
//#define LCD_IDLE_OFF
#if defined(LCD_IDLE_OFF)
    #define LCD_IDLE_TIMEOUT_SEC 5
#endif

// Enable LCD backlight beeing controlled by PWM
//#define LCD_PWM_DIMMER
#if defined(LCD_PWM_DIMMER)
    #define LCD_LED_PWM_ON_BRIGHTNESS 100
    #define LCD_LED_PWM_OFF_BRIGHTNESS 2
#endif

// Enable SPI data received indicator
//#define SPI_DATA_RECEIVED_INDICATOR

// Rotary knob long press duration for SPI restart
#define SPI_RESTART_KNOB_PRESS_DURATION 3