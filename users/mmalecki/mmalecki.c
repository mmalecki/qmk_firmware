#include QMK_KEYBOARD_H
#include "mmalecki.h"

#ifdef PROGRESS_ENABLE
#include "progress.h"
#endif

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
#ifdef PROGRESS_ENABLE
      case KC_PROGRESS_0: switch_progress_channel(0); break;
      case KC_PROGRESS_1: switch_progress_channel(1); break;
      case KC_PROGRESS_2: switch_progress_channel(2); break;
      case KC_PROGRESS_3: switch_progress_channel(3); break;
#endif
  }
  return true;
}
