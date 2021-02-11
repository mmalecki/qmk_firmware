#ifdef KEYBOARD_planck_ez
  #define _SAFE_RANGE EZ_SAFE_RANGE
#else
  #define _SAFE_RANGE SAFE_RANGE
#endif

#define MT_LSFT_SPC MT(MOD_LSFT, KC_SPACE)

enum userspace_custom_keycodes {
  GIT = _SAFE_RANGE,
  GIT_COMMIT_MSG,
  TERRAFORM,
#ifdef PROGRESS_ENABLE
  KC_PROGRESS_0,
  KC_PROGRESS_1,
  KC_PROGRESS_2,
  KC_PROGRESS_3,
#endif
};

enum tap_dances {
  TD_LBRACKETS,
  TD_RBRACKETS
};
