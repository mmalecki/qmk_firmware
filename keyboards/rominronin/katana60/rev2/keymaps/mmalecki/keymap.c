/* Copyright 2019 rominronin
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

#include "mmalecki.h"

// MacOS based definitions.
#define K_SPCFN LT(SYMB, KC_SPACE) // Tap for space, hold for symbols layer
#define K_PRVWD LALT(KC_LEFT)      // Previous word
#define K_NXTWD LALT(KC_RIGHT)     // Next word
#define K_LSTRT LGUI(KC_LEFT)      // Start of line
#define K_LEND  LGUI(KC_RIGHT)     // End of line
#define UNDO    LGUI(KC_Z)         // UNDO
#define CUT     LGUI(KC_X)         // CUT
#define COPY    LGUI(KC_C)         // COPY
#define PASTE   LGUI(KC_V)         // PASTE

enum layer_names {
  BASE,
  FN,
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  QMKBEST = SAFE_RANGE,
  QMKURL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT_1_c(/* Base */
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,     KC_5,    KC_6,      LCTL(KC_Z), KC_7,    KC_8,    KC_9, KC_0,    KC_MINS, KC_EQL,  KC_GRAVE,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,     KC_T,    KC_LBRC,   KC_RBRC,    KC_Y,    KC_U,    KC_I, KC_O,    KC_P,    KC_BSPC,
    KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,     KC_G,    KC_BSLASH, KC_QUOTE,   KC_H,    KC_J,    KC_K, KC_L,    KC_SCLN, KC_ENTER,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,     KC_B,    KC_PGUP,   KC_DEL,     KC_PGDN, KC_N,    KC_M, KC_COMM, KC_DOT,  KC_SLSH, MO(FN),
    KC_LSFT, KC_LCTL, KC_LGUI, KC_LALT, KC_SPACE, KC_ENT,  KC_SPACE,  KC_RALT,    KC_RGUI, MO(FN)
  ),
  [FN] = LAYOUT_1_c(
    _______, _______, _______, _______, _______,  _______, _______,    _______,   _______, _______, _______, _______, _______,  _______, _______,
    _______, _______, _______, _______, _______,  _______, _______,    _______,   _______, _______, _______, _______, KC_UP,    _______,
    _______, _______, _______, _______, TERRAFORM, GIT,    _______,    _______,   _______, _______, _______, KC_LEFT, KC_RIGHT, _______,
    _______, _______, _______, GIT_COMMIT_MSG, _______, _______, _______, _______,  _______, _______, _______, _______, _______,  KC_DOWN, _______,
    _______, _______, _______, _______, _______,  _______, _______,    _______,   _______, _______
  ),
};
