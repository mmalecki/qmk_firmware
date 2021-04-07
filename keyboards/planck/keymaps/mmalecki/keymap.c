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
  [_BASE] = LAYOUT_planck_grid(
    KC_ESCAPE,      KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,           KC_Y,           KC_U,           KC_I,           KC_O,           KC_P,           KC_BSPACE,
    KC_TAB,         KC_A,           KC_S,           KC_D,           KC_F,           KC_G,           KC_H,           KC_J,           KC_K,           KC_L,           KC_SCOLON,      KC_QUOTE,
    KC_LCTRL,       KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,           KC_N,           KC_M,           KC_COMMA,       KC_DOT,         KC_SLASH,       KC_ENTER,
    KC_LSHIFT,      TD(TD_LBRACKETS), KC_LGUI,      KC_LALT,        LOWER,          MT(MOD_LSFT, KC_SPACE), KC_NO,  RAISE,          KC_RALT,        KC_RGUI,        TD(TD_RBRACKETS), MO(_FN)
  ),

  [_LOWER] = EXPAND( \
    KC_GRAVE,       NUMBER_SYMBOLS_L,                                                               NUMBER_SYMBOLS_R,                                                               KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, LOWER_SYMBOLS_R,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_LBRACKET,    KC_RBRACKET,    KC_BSLASH,
    KC_LSHIFT,      KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_NO,          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),

  [_RAISE] = EXPAND( \
    KC_TILD,        NUMBERS_L,                                                                      NUMBERS_R,                                                                      KC_TRANSPARENT,
    KC_TRANSPARENT, NUMBERS_L,                                                                      NUMBERS_R,                                                                      KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_NO,          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),

  [_ADJUST] = LAYOUT_planck_grid(
    KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT, RESET,          KC_TRANSPARENT, KC_TRANSPARENT, TOGGLE_LAYER_COLOR, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_DELETE,      KC_TRANSPARENT, AU_ON,          AU_OFF,         AU_TOG,         KC_TRANSPARENT, KC_TRANSPARENT, RGB_TOG,        RGB_VAI,        RGB_VAD,        KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, MU_ON,          MU_OFF,         MU_TOG,         KC_TRANSPARENT, KC_TRANSPARENT, RGB_MOD,        RGB_HUI,        RGB_HUD,        KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_NO,          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),

  [_FN] = LAYOUT_planck_grid(
    KC_TRANSPARENT, KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,          KC_F6,          KC_F7,          KC_F8,          KC_F10,         KC_F11,         KC_F12,
    KC_CAPSLOCK,    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, TERRAFORM,      GIT,            KC_ASTR,        KC_SLASH,       KC_HOME,        KC_PGUP,        KC_UP,          KC_LEFT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, GIT_COMMIT_MSG, KC_TRANSPARENT, KC_TRANSPARENT, KC_PLUS,        KC_MINUS,       KC_END,         KC_PGDOWN,      KC_DOWN,        KC_RIGHT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_NO,          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
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
