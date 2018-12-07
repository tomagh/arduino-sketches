// set this values for your best expitiance
#include "inttypes.h"

#define BTN_CONTACTS_BOUNCE_DELAY 1000
#define BTN_TICKS_DOWN_FOR_LONG_PRESS 100000
#define BTN_TICKS_UP_FOR_MULTI_CLICK 30000

typedef struct {
  uint8_t pin:5; // pin number, 0..31. Increase field size for more values.

  uint8_t down:1; // 1 if button pin has HIGH signal
  uint32_t idle; // number of updates withing the .down value did not change
  uint8_t clicks; // number of clicks in a row
  uint8_t longPressDuration;
} TButton;

typedef enum {
  TButtonIdle, // nothing did change
  TButtonDown, // button pressed
  TButtonUp, // button released
  TButtonMulticlickComplete, // multiclick complete
  TButtonLongPress, // button is pressed long enough
  TButtonLongPressComplete, // button is pressed long enough
} TButtonEvent;

extern TButton* TButton_init(uint8_t pin);
extern TButtonEvent TButton_update(TButton *btn);

