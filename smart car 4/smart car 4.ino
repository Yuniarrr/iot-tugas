#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#define BLYNK_TEMPLATE_ID "TMPLsJJCElAx"
#define BLYNK_TEMPLATE_NAME "Smart Car"
#define BLYNK_AUTH_TOKEN "1usK5tT-9oKTMALn9JdESkW0PqqFrJIS"

char ssid[] = "password";
char pass[] = "azril1337";

int ENA = 12;
int ENB = 14;
int motor1_pin1 = 27;
int motor1_pin2 = 26;
int motor2_pin1 = 25;
int motor2_pin2 = 33;

int power = 0;
int maju = 0;
int mundur = 0;
int kanan = 0;
int kiri = 0;
int speed = 0;

const int frequency = 500;
const int pwm_channel1 = 0;
const int pwm_channel2 = 1;
const int resolution = 8;
void setup() {
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  Serial.println("Setup...");

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(motor1_pin1, OUTPUT);
  pinMode(motor1_pin2, OUTPUT);
  pinMode(motor2_pin1, OUTPUT);
  pinMode(motor2_pin2, OUTPUT);

  ledcSetup(pwm_channel1, frequency, resolution);
  ledcSetup(pwm_channel2, frequency, resolution);
  ledcAttachPin(ENA, pwm_channel1);
  ledcAttachPin(ENB, pwm_channel2);
}

BLYNK_WRITE(V0)
{
  power = param.asInt();
  Serial.println((String)"Power : "+power);
}

BLYNK_WRITE(V1)
{
  speed = param.asInt();
  Serial.println((String)"Speed: "+speed);
}

BLYNK_WRITE(V2)
{
  maju = param.asInt();
  Serial.println((String)"Maju: "+maju);
}

BLYNK_WRITE(V3)
{
  kanan = param.asInt();
  Serial.println((String)"Kanan: "+kanan);
}

BLYNK_WRITE(V4)
{
  mundur = param.asInt();
  Serial.println((String)"Mundur: "+mundur);
}

BLYNK_WRITE(V5)
{
  kiri = param.asInt();
  Serial.println((String)"Kiri: "+kiri);
}

void moveControl()
{
  if(power == 1) {
    if (maju == 1) {
      digitalWrite(motor1_pin1, HIGH);
      digitalWrite(motor1_pin2, LOW);
      digitalWrite(motor2_pin1, HIGH);
      digitalWrite(motor2_pin2, LOW);
      ledcWrite(pwm_channel1, speed);
      ledcWrite(pwm_channel2, speed);
    } else if (mundur == 1) {
      digitalWrite(motor1_pin1, LOW);
      digitalWrite(motor1_pin2, HIGH);
      digitalWrite(motor2_pin1, LOW);
      digitalWrite(motor2_pin2, HIGH);
      ledcWrite(pwm_channel1, speed);
      ledcWrite(pwm_channel2, speed);
    } else if (kanan == 1) {
      digitalWrite(motor1_pin1, HIGH);
      digitalWrite(motor1_pin2, LOW);
      digitalWrite(motor2_pin1, LOW);
      digitalWrite(motor2_pin2, HIGH);
      ledcWrite(pwm_channel1, speed);
      ledcWrite(pwm_channel2, speed/2);
    } else if (kiri == 1) {
      digitalWrite(motor1_pin1, LOW);
      digitalWrite(motor1_pin2, HIGH);
      digitalWrite(motor2_pin1, HIGH);
      digitalWrite(motor2_pin2, LOW);
      ledcWrite(pwm_channel1, speed/2);
      ledcWrite(pwm_channel2, speed);
    } else {
      digitalWrite(motor1_pin1, LOW);
      digitalWrite(motor1_pin2, LOW);
      digitalWrite(motor2_pin1, LOW);
      digitalWrite(motor2_pin2, LOW);
    }
  }
}

void loop() {
  Blynk.run();
  moveControl();
}
