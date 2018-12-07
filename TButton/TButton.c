#include "TButton.h"
#include "Arduino.h"

TButton* TButton_init(uint8_t pin)
{
  TButton* result = (TButton*)malloc(sizeof(TButton));
  memset(result, 0, sizeof(TButton));
  result->pin = pin;
  pinMode(result->pin, INPUT_PULLUP);
  result->down = digitalRead(result->pin) ? 0 : 1;
  result->clicks = 0;
  return result;
}

TButtonEvent TButton_update(TButton *btn)
{
  if (btn->down != (digitalRead(btn->pin) ? 0 : 1)) {
    if (btn->idle < BTN_CONTACTS_BOUNCE_DELAY) {
      return TButtonIdle;
    }
    btn->down = !btn->down;
    btn->idle = 0;

    if (btn->down) {
      btn->clicks++;
    }

    return btn->down ? TButtonDown : TButtonUp;
  } else {
    if (btn->idle + 1 != 0) { // overflow protect
      btn->idle += 1;

      if (btn->down) {
        if (btn->idle == BTN_TICKS_DOWN_FOR_LONG_PRESS) {
          btn->longPressDuration += 1;
          btn->idle = 0; // keep idle value under overflow
          return TButtonLongPress;
        }
      } else {
        if (btn->idle == BTN_TICKS_UP_FOR_MULTI_CLICK) {
          if (btn->clicks > 0) {
            return TButtonMulticlickComplete;
          } else {
            return TButtonIdle;
          }
        } else if (btn->idle == (BTN_TICKS_UP_FOR_MULTI_CLICK + 1)) {
          btn->clicks = 0;
          btn->longPressDuration = 0;
        }
      }
    }
    return TButtonIdle;
  }
}
