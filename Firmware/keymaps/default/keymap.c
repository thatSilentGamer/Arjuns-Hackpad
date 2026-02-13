#include QMK_KEYBOARD_H

// Custom keycodes for our special functions
enum custom_keycodes {
    RGB_CYCLE = SAFE_RANGE,  // RGB cycle including OFF
    ENC_TOG                   // Encoder mode toggle
};

// Track encoder mode (0=Volume, 1=Brightness, 2=Media, 3=Scroll)
static uint8_t encoder_mode = 0;

// Track RGB state (0=OFF, 1-10=different modes)
static uint8_t rgb_mode_state = 1;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        RGB_CYCLE,  ENC_TOG,     KC_MPLY,        KC_MNXT,
        C(KC_C),    C(KC_V),     C(KC_Z),        C(S(KC_Z))
    )
};

// Handle custom keycodes
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RGB_CYCLE:
            if (record->event.pressed) {
                rgb_mode_state++;
                if (rgb_mode_state > 10) {  // 10 modes + OFF = 11 total states
                    rgb_mode_state = 0;
                }
                
                if (rgb_mode_state == 0) {
                    // Turn OFF
                    rgblight_disable();
                } else {
                    // Turn on and set mode
                    if (!rgblight_is_enabled()) {
                        rgblight_enable();
                    }
                    rgblight_mode(rgb_mode_state);
                }
            }
            return false;
            
        case ENC_TOG:
            if (record->event.pressed) {
                encoder_mode = (encoder_mode + 1) % 4;  // Cycle through 4 modes
            }
            return false;
    }
    return true;
}

// Handle encoder rotation based on current mode
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        switch (encoder_mode) {
            case 0:  // Volume mode
                if (clockwise) {
                    tap_code(KC_VOLU);
                } else {
                    tap_code(KC_VOLD);
                }
                break;
                
            case 1:  // Brightness mode
                if (clockwise) {
                    tap_code(KC_BRIU);
                } else {
                    tap_code(KC_BRID);
                }
                break;
                
            case 2:  // Media mode
                if (clockwise) {
                    tap_code(KC_MNXT);
                } else {
                    tap_code(KC_MPRV);
                }
                break;
                
            case 3:  // Scroll mode
                if (clockwise) {
                    tap_code(KC_WH_D);
                } else {
                    tap_code(KC_WH_U);
                }
                break;
        }
    }
    return false;
}

#ifdef OLED_ENABLE
bool oled_task_user(void) {
    // Display hackpad title
    oled_write_P(PSTR("HACKPAD v1.0\n"), false);
    oled_write_P(PSTR("------------\n"), false);
    
    // Display encoder mode
    oled_write_P(PSTR("Encoder: "), false);
    switch (encoder_mode) {
        case 0:
            oled_write_P(PSTR("Volume\n"), false);
            break;
        case 1:
            oled_write_P(PSTR("Brightness\n"), false);
            break;
        case 2:
            oled_write_P(PSTR("Media\n"), false);
            break;
        case 3:
            oled_write_P(PSTR("Scroll\n"), false);
            break;
    }
    
    // Display RGB status
    oled_write_P(PSTR("\nRGB: "), false);
    if (rgb_mode_state == 0) {
        oled_write_P(PSTR("OFF"), false);
    } else {
        oled_write_P(PSTR("Mode "), false);
        oled_write(get_u8_str(rgb_mode_state, ' '), false);
    }
    
    return false;
}
#endif