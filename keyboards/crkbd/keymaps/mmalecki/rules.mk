OLED_DRIVER_ENABLE  = yes
RGBLIGHT_ENABLE = yes
#RGB_MATRIX_ENABLE = yes
TAP_DANCE_ENABLE = yes
RAW_ENABLE = yes

CFLAGS += -flto
SRC += mmalecki.c qmk_rc.c
