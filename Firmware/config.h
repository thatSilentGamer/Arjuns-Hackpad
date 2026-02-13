#pragma once

// OLED Configuration
#define I2C_DRIVER I2CD1
#define I2C1_SDA_PIN GP6
#define I2C1_SCL_PIN GP7

// Optional: Customize OLED timeout (milliseconds)
#define OLED_TIMEOUT 30000

// Optional: OLED brightness (0-255)
#define OLED_BRIGHTNESS 128

// Optional: Flip OLED display if mounted upside down
// #define OLED_DISPLAY_180

// RGB Configuration
#define RGBLIGHT_SLEEP  // Turn off RGB when computer sleeps

// Encoder configuration
#define ENCODER_RESOLUTION 4
