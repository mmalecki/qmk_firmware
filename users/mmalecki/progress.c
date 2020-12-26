#include QMK_KEYBOARD_H
#include "progress.h"

indicator_state_t indicator_states[CHANNELS] = { CLEAR, CLEAR, CLEAR, CLEAR };
uint8_t current_progress_channel = 0;
uint8_t channel_progress[CHANNELS];
uint8_t channel_progress_indicators[CHANNELS] = { 0, 1, 2, 3 };

bool is_indicator_led(uint8_t led) {
  for (int i = 0; i < CHANNELS; i++) {
    if (channel_progress_indicators[i] == led) {
      return true;
    }
  }
  return false;
}

void clear_progress(void) {
  for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
    rgb_matrix_set_color(i, 0, 0, 0);
  }
}

void redraw_indicators(void) {
  indicator_states[current_progress_channel] = CLEAR;
  for (int channel = 0; channel < CHANNELS; channel++) {
    uint8_t led = channel_progress_indicators[channel];
    if (indicator_states[channel] == PROGRESS)
      rgb_matrix_set_color(led, 0xff, 0xff, 0);
    else if (indicator_states[channel] == DONE)
      rgb_matrix_set_color(led, 0, 0xff, 0);
  }
}


void redraw_progress(void) {
  rgb_matrix_set_color(channel_progress_indicators[current_progress_channel], 0, 0, 0);

  uint8_t progress = channel_progress[current_progress_channel];
  uint8_t leds = round((double) (progress * DRIVER_LED_TOTAL) / ((1 << PROGRESS_BITS) - 1));
  clear_progress();
  for (int i = 0; i < leds; i++)
    rgb_matrix_set_color(i, 0xff, 0xff, 0);

  redraw_indicators();
}

void switch_progress_channel(uint8_t channel) {
  current_progress_channel = channel;
  redraw_progress();
}

void process_progress_msg(hid_progress_msg_t msg) {
  uint8_t channel = msg.channel;

  if (channel < CHANNELS) {
    channel_progress[channel] = msg.progress;
    if (channel == current_progress_channel) redraw_progress();
    else {
      if (msg.progress == MAX_PROGRESS)
        indicator_states[channel] = DONE;
      else
        indicator_states[channel] = PROGRESS;
      redraw_indicators();
    }
  }
}

void raw_hid_receive(uint8_t *data, uint8_t length) {
  for (int i = 0; i < length; i++) {
    hid_progress_msg_t msg;
    msg.raw = data[i];
    process_progress_msg(msg);
  }
}
