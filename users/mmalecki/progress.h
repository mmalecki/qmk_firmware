#define CHANNEL_BITS 2
#define PROGRESS_BITS 6

#define CHANNELS (1 << CHANNEL_BITS)
#define MAX_PROGRESS ((1 << PROGRESS_BITS) - 1)

typedef union {
  uint8_t raw;
  struct {
    uint8_t channel  : CHANNEL_BITS;
    uint8_t progress : PROGRESS_BITS;
  };
} hid_progress_msg_t;

typedef enum {
  CLEAR,
  PROGRESS,
  DONE
} indicator_state_t;

void switch_progress_channel(uint8_t channel);
