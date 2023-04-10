#include <analogWrite.h>
// Define pins
#define IN1 27
#define IN2 26

void setup() {
  // Set up pins as output
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  // Set up serial communication
  Serial.begin(9600);
}

void loop() {
  // Move forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  // Set speed
  analogWrite(IN1, 255);
  analogWrite(IN2, 255);

  // Wait for 1 second
  delay(1000);

  // Move backward
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  // Set speed
  analogWrite(IN1, 255);
  analogWrite(IN2, 255);

  // Wait for 1 second
  delay(1000);
}
