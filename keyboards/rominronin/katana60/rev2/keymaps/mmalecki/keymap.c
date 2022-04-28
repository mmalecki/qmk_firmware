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

#define EXPAND(...) LAYOUT_1_c(__VA_ARGS__)

enum layer_names {
  BASE,
  FN,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = EXPAND( \
    KC_ESC,  NUMBERS_L,                                    LCTL(KC_Z), NUMBERS_R,                         KC_MINS, KC_EQL,  KC_GRAVE,
    KC_TAB,  QWERTY_L3,                                    KC_LBRC,   KC_RBRC,    QWERTY_R3,                                KC_BSPC,
    KC_LCTL, QWERTY_L2,                                    KC_BSLASH, KC_QUOTE,   QWERTY_R2,                                KC_ENTER,
    KC_LSFT, QWERTY_L1,                                    KC_PGUP,   KC_DEL,     KC_PGDN, QWERTY_R1,                       MO(FN),
    KC_LSFT, KC_LCTL, KC_LGUI, KC_LALT, MT(MOD_LSFT, KC_SPACE), KC_ENT, KC_SPACE, KC_RALT, KC_RGUI, MO(FN)
  ),
  [FN] = EXPAND( \
    RESET,   F_L,                                                     _______,    F_R,                                      _______,
    FN_L3,                                                 _______,   _______,    FN_R3,
    FN_L2,                                                 _______,   _______,    FN_R2,
    FN_L1,                                                 _______,   _______,    _______, FN_R1,
    _______, _______, _______, _______, _______,  _______, _______,    _______,   _______, _______
  ),
};
