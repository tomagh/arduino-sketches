#include "TButton.c"

TButton* button;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  button = TButton_init(12);
}

void loop() {
  switch (TButton_update(button)) {
    case TButtonDown: {
      Serial.print("start; ");
      Serial.print(button->clicks);
      Serial.print("-th click");
      Serial.println("");
    } break;
    case TButtonUp: {
      Serial.print("finish ");
      Serial.print(button->clicks);
      Serial.print("-th click; ");
      Serial.print(button->longPressDuration);
      Serial.print(" long presses");
      Serial.println("");
    } break;
    case TButtonLongPress: {
      Serial.print("long press for the ");
      Serial.print(button->longPressDuration);
      Serial.print("-th time, with ");
      Serial.print(button->clicks);
      Serial.print("clicks before");
      Serial.println("");

      button->clicks = 0; // recet clicks
    } break;
    case TButtonMulticlickComplete: {
      if (button->clicks > 0) { // skip zeroed click after long press events
        Serial.print("multiclick complete with ");
        Serial.print(button->clicks);
        Serial.print("click in a row");
        Serial.println("");
      }
    } break;
    default: break; // nothing to do
  }
}

