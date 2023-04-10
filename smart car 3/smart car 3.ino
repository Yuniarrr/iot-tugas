#define BLYNK_PRINT Serial
// #include <ESP8266WiFi.h>
// #include <BlynkSimpleEsp8266.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <analogWrite.h>

// Right Side
int IN1_pin = 27; 
int IN2_pin = 26;

// Left Side
int IN3_pin = 25;
int IN4_pin = 33;

// #define IN3_pin       25   //13 
// #define IN4_pin       33   //15 

char auth[] = "arJse34qMId67T-vGs5QpqRi3qGljLBV";  //Blynk Authentication Token
char ssid[] = "password";           //WIFI Name
char pass[] = "azril1337";           //WIFI Password

void moveControl(int X, int Y)
{
    int PWM1 = map(X, 0, 255, -255, 255);
    int PWM2 = map(Y, 0, 255, -255, 255);

    Serial.println((String)"PWM1:"+PWM1+", PWM2:"+PWM2);

    if (PWM1 > 0) {
      Serial.println("Belok kanan");
      digitalWrite(IN1_pin, HIGH);
      digitalWrite(IN2_pin, LOW);
    } else {
      Serial.println("Belok kiri");
      digitalWrite(IN1_pin, LOW);
      digitalWrite(IN2_pin, HIGH);
    }
    if (PWM2 > 0) {
      Serial.println("Maju");
      digitalWrite(IN3_pin, HIGH);
      digitalWrite(IN4_pin, LOW);
    } else {
      Serial.println("Mundur");
      digitalWrite(IN3_pin, LOW);
      digitalWrite(IN4_pin, HIGH);
    }

    // Mengatur kecepatan putaran roda
    analogWrite(IN1_pin, abs(PWM1));
    analogWrite(IN2_pin, abs(PWM1));
    analogWrite(IN3_pin, abs(PWM2));
    analogWrite(IN4_pin, abs(PWM2));    
}

void setup()
{
    Serial.begin(9600);
    Blynk.begin(auth, ssid, pass);

    pinMode(IN1_pin, OUTPUT);
    pinMode(IN2_pin, OUTPUT);
    pinMode(IN3_pin, OUTPUT);
    pinMode(IN4_pin, OUTPUT);

    // digitalWrite(IN1_pin, LOW);
    // digitalWrite(IN2_pin, LOW);
    // digitalWrite(IN3_pin, LOW);
    // digitalWrite(IN4_pin, LOW);
}


void loop()
{
    Blynk.run();
}


BLYNK_WRITE(V1)
{
    int x = param[0].asInt();
    int y = param[1].asInt();
    Serial.println((String)"x:"+x+", y:"+y);
    moveControl(x,y);
}