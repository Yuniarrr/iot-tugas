#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <analogWrite.h>

#define BLYNK_TEMPLATE_ID "TMPLdXYvA4rC"
#define BLYNK_TEMPLATE_NAME "Remote Control"
#define BLYNK_AUTH_TOKEN "arJse34qMId67T-vGs5QpqRi3qGljLBV"

char ssid[] = "OPPO A16";
char pass[] = "halo1234";

int motorPin1 = 27;
int motorPin2 = 26;
int power = 0; // Power
BlynkTimer timer;

void setup() {
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  Serial.println("Setup...");

  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
}

// Power
BLYNK_WRITE(V5) // Executes when the value of virtual pin 0 changes
{
  if(param.asInt() == 1)
  {
    power = 1;
    Serial.println("[STATUS] Power on!");
  }
  else
  {
    power = 0;
    Serial.println("[STATUS] Power off!");  
  }
}

BLYNK_WRITE(V0) // Executes when the value of virtual pin 0 changes
{
  if(param.asInt() == 1)
  {
    // execute this code if the switch widget is now ON
    analogWrite(motorPin1, 255);  // Set digital pin 2 HIGH
    analogWrite(motorPin2, 0);  // Set digital pin 2 HIGH
    Serial.println(param.asInt());
  }
  else
  {
    // execute this code if the switch widget is now OFF
    analogWrite(motorPin1, 0);  // Set digital pin 2 HIGH
    analogWrite(motorPin2, 0);  // Set digital pin 2 LOW
    Serial.println(param.asInt());    
  }
}

void loop() {
  Blynk.run();
  // Set the motor speed to half of maximum speed (range is 0-255)
  // analogWrite(motorPin1, 128);
  // analogWrite(motorPin2, 0);

  // Wait for 2 seconds
  // delay(2000);

  // Set the motor speed to full maximum speed
  // analogWrite(motorPin1, 255);
  // analogWrite(motorPin2, 0);

  // Wait for 2 seconds
  // delay(2000);

  // Stop the motor
  // analogWrite(motorPin1, 0);
  // analogWrite(motorPin2, 0);

  // Wait for 2 seconds
  // delay(2000);
}
