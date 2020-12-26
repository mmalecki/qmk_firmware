SRC += muse.c mmalecki.c progress.c
# Set any rules.mk overrides for your specific keymap here.
# See rules at https://docs.qmk.fm/#/config_options?id=the-rulesmk-file
CONSOLE_ENABLE = no
AUDIO_ENABLE = yes
COMMAND_ENABLE = no
MOUSEKEY_ENABLE = no
TAP_DANCE_ENABLE = yes
RGB_MATRIX_ENABLE = yes
RAW_ENABLE = yes

# I make my own rules here
PROGRESS_ENABLE = yes
