#include QMK_KEYBOARD_H
#ifdef AUDIO_ENABLE
#include "muse.h"
#endif

#include "eeprom.h"

#include "mmalecki.h"
#include "qmk_rc.h"

enum planck_layers {
  _BASE,
  _LOWER,
  _RAISE,
  _ADJUST,
  _FN,
};

#define EXPAND(...) LAYOUT_planck_grid(__VA_ARGS__)

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = EXPAND( \
    KC_ESC,  QWERTY_L3,                                   QWERTY_R3,                                   KC_BSPC,
    KC_TAB,  QWERTY_L2,                                   QWERTY_R2,                                   KC_QUOTE,
    KC_LCTL, QWERTY_L1,                                   QWERTY_R1,                                   KC_ENTER,
    KC_LSFT, TD(TD_LBRACKETS), KC_LGUI,  KC_LALT, LOWER,  MT(MOD_LSFT, KC_SPACE), KC_NO, RAISE, KC_RALT, KC_RGUI, TD(TD_RBRACKETS), MO(_FN)
  ),

  [_LOWER] = EXPAND( \
    KC_GRV,  NUMBER_SYMBOLS_L,                            NUMBER_SYMBOLS_R,                            XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, LOWER_SYMBOLS_R,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LCBR, KC_LBRC, KC_RBRC, KC_RCBR, XXXXXXX, XXXXXXX, KC_BSLASH, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
  ),

  [_RAISE] = EXPAND( \
    KC_TILD, NUMBERS_L,                                   NUMBERS_R,                                   XXXXXXX,
    XXXXXXX, NUMBERS_L,                                   NUMBERS_R,                                   XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
  ),

  [_ADJUST] = EXPAND( \
    F_L,                                                  F_R,
    XXXXXXX, RGB_L1,                             XXXXXXX, AU_R1,            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    RESET,   RGB_L2,                             XXXXXXX, AU_R2,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
  ),

  [_FN] = EXPAND( \
    FN_L3,                                                FN_R3,
    FN_L2,                                                FN_R2,
    FN_L1,                                                FN_R1,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
  ),

};

extern bool g_suspend_state;
extern rgb_config_t rgb_matrix_config;

void keyboard_post_init_user(void) {
#ifdef RGB_MATRIX_ENABLE
  rgb_matrix_enable();
  rgb_matrix_mode(RGB_MATRIX_NONE);
  rgb_matrix_set_color_all(0x22, 0x8b, 0x22);
#endif
}

#ifdef AUDIO_ENABLE
bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

void matrix_scan_user(void) {
    if (muse_mode) {
        if (muse_counter == 0) {
            uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
            if (muse_note != last_muse_note) {
                stop_note(compute_freq_for_midi_note(last_muse_note));
                play_note(compute_freq_for_midi_note(muse_note), 0xF);
                last_muse_note = muse_note;
            }
        }
        muse_counter = (muse_counter + 1) % muse_tempo;
    }
}

bool music_mask_user(uint16_t keycode) {
    switch (keycode) {
    case RAISE:
    case LOWER:
        return false;
    default:
        return true;
    }
}
#endif

uint32_t layer_state_set_user(uint32_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

#ifdef RAW_ENABLE
#define QMK_RC_BUFFER_MAX 64
uint8_t qmk_rc_buffer[QMK_RC_BUFFER_MAX] = {};

void raw_hid_receive(uint8_t *data, uint8_t length) {
  qmk_rc_receive(qmk_rc_buffer, QMK_RC_BUFFER_MAX, data, length);
}
#endif
