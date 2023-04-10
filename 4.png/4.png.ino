#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <analogWrite.h>

#define BLYNK_TEMPLATE_ID "TMPLdXYvA4rC"
#define BLYNK_TEMPLATE_NAME "Remote Control"
#define BLYNK_AUTH_TOKEN "arJse34qMId67T-vGs5QpqRi3qGljLBV"

char ssid[] = "password";
char pass[] = "azril1337";

int motor1_pin1 = 27;
int motor1_pin2 = 26;
int motor2_pin1 = 25;
int motor2_pin2 = 33;

int power = 0;

void setup() {
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  Serial.println("Setup...");

  pinMode(motor1_pin1, OUTPUT);
  pinMode(motor1_pin2, OUTPUT);
  pinMode(motor2_pin1, OUTPUT);
  pinMode(motor2_pin2, OUTPUT);
}

// BLYNK_WRITE(V0) // Executes when the value of virtual pin 0 changes
// {
//   if(param.asInt() == 1)
//   {
//     // execute this code if the switch widget is now ON
//     analogWrite(motor1_pin1, 255);  // Set digital pin 2 HIGH
//     analogWrite(motor1_pin2, 0);  // Set digital pin 2 HIGH
//     Serial.println(param.asInt());
//   }
//   else
//   {
//     // execute this code if the switch widget is now OFF
//     analogWrite(motor1_pin1, 0);  // Set digital pin 2 HIGH
//     analogWrite(motor1_pin2, 0);  // Set digital pin 2 LOW
//     Serial.println(param.asInt());    
//   }
// }

BLYNK_WRITE(V0)
{
    power = param.asInt();
    if (power == 1) {
      analogWrite(motor1_pin1, 255);
    } else {
      analogWrite(motor1_pin1, 0);
    }
    Serial.println((String)"Power : "+power);
}

// BLYNK_WRITE(V1)
// {
//     int X = param[0].asInt();
//     int Y = param[1].asInt();

//     Serial.println((String)"x:"+X+", y:"+Y);
    
//     int PWM1 = map(X, 0, 255, -255, 255);
//     int PWM2 = map(Y, 0, 255, -255, 255);

//     Serial.println((String)"PWM1:"+PWM1+", PWM2:"+PWM2);

//     if (power == 1) {
//       // Kuadran 1
//       if (x )
//       // if (PWM1 > 0) {
//       //   digitalWrite(motor1_pin1, HIGH);
//       //   digitalWrite(motor1_pin2, LOW);
//       //   analogWrite(motor1_pin1, abs(PWM1));
//       //   analogWrite(motor1_pin2, 0);
//       // } else {
//       //   digitalWrite(motor2_pin1, HIGH);
//       //   digitalWrite(motor2_pin2, LOW);
//       //   analogWrite(motor2_pin1, abs(PWM1));
//       //   analogWrite(motor2_pin2, 0);
//       // }

//       // if (PWM2 > 0) {
//       //   digitalWrite(motor2_pin1, HIGH);
//       //   digitalWrite(motor2_pin2, LOW);
//       //   analogWrite(motor2_pin1, abs(PWM2));
//       //   analogWrite(motor2_pin2, 0);
//       // } else {
//       //   Serial.println("Mundur");
//       //   digitalWrite(motor1_pin1, LOW);
//       //   digitalWrite(motor1_pin2, HIGH);
//       //   analogWrite(motor2_pin1, 0);
//       //   analogWrite(motor2_pin2, abs(PWM2));
//       // }
//     }

//     // Mengatur kecepatan putaran roda
//     // analogWrite(motor1_pin1, abs(PWM1));
//     // analogWrite(motor1_pin2, abs(PWM1));
//     // analogWrite(motor2_pin1, abs(PWM2));
//     // analogWrite(motor2_pin2, abs(PWM2));
// }

void loop() {
  Blynk.run();
  // Set the motor speed to half of maximum speed (range is 0-255)
  // analogWrite(motor1_pin1, 128);
  // analogWrite(motor1_pin2, 0);

  // Wait for 2 seconds
  // delay(2000);

  // Set the motor speed to full maximum speed
  // analogWrite(motor1_pin1, 255);
  // analogWrite(motor1_pin2, 0);

  // Wait for 2 seconds
  // delay(2000);

  // Stop the motor
  // analogWrite(motor1_pin1, 0);
  // analogWrite(motor1_pin2, 0);

  // Wait for 2 seconds
  // delay(2000);
}
