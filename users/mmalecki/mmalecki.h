#ifdef KEYBOARD_planck_ez
  #define _SAFE_RANGE EZ_SAFE_RANGE
#else
  #define _SAFE_RANGE SAFE_RANGE
#endif

enum userspace_custom_keycodes {
  GIT = _SAFE_RANGE,
  GIT_COMMIT_MSG,
  TERRAFORM,
};

enum tap_dances {
  TD_LBRACKETS,
  TD_RBRACKETS
};
