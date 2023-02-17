/*
 * This ESP32 code is created by esp32io.com
 *
 * This ESP32 code is released in the public domain
 *
 * For more detail (instruction and wiring diagram), visit https://esp32io.com/tutorials/esp32-button-toggle-led
 */

#include <ezButton.h>

#define BUTTON_PIN 33  // ESP32 pin GIOP16, which connected to button
#define LED_PIN    21  // ESP32 pin GIOP18, which connected to led

ezButton button(BUTTON_PIN);  // create ezButton object that attach to pin 7;

// variables will change:
int led_state = LOW;   // the current state of LED

void setup() {
  Serial.begin(9600);         // initialize serial
  pinMode(LED_PIN, OUTPUT);   // set ESP32 pin to output mode
  button.setDebounceTime(50); // set debounce time to 50 milliseconds
}

void loop() {
  button.loop(); // MUST call the loop() function first

  if (button.isPressed()) {
    Serial.println("The button is pressed");

    // toggle state of LED
    led_state = !led_state;

    // control LED arccoding to the toggleed sate
    digitalWrite(LED_PIN, led_state);
  }
}
