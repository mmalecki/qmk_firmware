#include QMK_KEYBOARD_H
#include "mmalecki.h"

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_LBRACKETS] = ACTION_TAP_DANCE_DOUBLE(KC_LBRACKET, KC_LPRN),
  [TD_RBRACKETS] = ACTION_TAP_DANCE_DOUBLE(KC_RBRACKET, KC_RPRN)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case TERRAFORM:
      if (record->event.pressed) {
        SEND_STRING("terraform ");
      }
      break;
    case GIT:
      if (record->event.pressed) {
        SEND_STRING("git ");
      }
      break;
    case GIT_COMMIT_MSG:
      if (record->event.pressed) {
        SEND_STRING("git commit -m ''"SS_TAP(X_LEFT));
      }
      break;
  }
  return true;
}
