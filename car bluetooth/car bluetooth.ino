#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

int ENA = 12;
int ENB = 14;
int motor1_pin1 = 27;
int motor1_pin2 = 26;
int motor2_pin1 = 25;
int motor2_pin2 = 33;

char m;

const int frequency = 500;
const int pwm_channel1 = 0;
const int pwm_channel2 = 1;
const int resolution = 8;
int speed = 255;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("Bledek666");

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

void loop() {
  m = (char)SerialBT.read();

  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }

  if (SerialBT.available()) {
    Serial.print("Received");
    Serial.println(m);

    if (m=='0') {
      speed = 0;
    } else if (m=='1'||m=='2'||m=='3'||m=='4'||m=='5'||m=='6'||m=='7'||m=='8'||m=='9') {
      speed = (m-'0') * 26;
    } else if (m=='q') {
      speed = 255;
    }

    Serial.println((String)"Speed: "+speed);

    if (m=='F') {
      digitalWrite(motor1_pin1, HIGH);
      digitalWrite(motor1_pin2, LOW);
      digitalWrite(motor2_pin1, HIGH);
      digitalWrite(motor2_pin2, LOW);
      ledcWrite(pwm_channel1, speed);
      ledcWrite(pwm_channel2, speed);
    } else if (m=='B') {
      digitalWrite(motor1_pin1, LOW);
      digitalWrite(motor1_pin2, HIGH);
      digitalWrite(motor2_pin1, LOW);
      digitalWrite(motor2_pin2, HIGH);
      ledcWrite(pwm_channel1, speed);
      ledcWrite(pwm_channel2, speed);
    } else if (m=='R') {
      digitalWrite(motor1_pin1, LOW);
      digitalWrite(motor1_pin2, HIGH);
      digitalWrite(motor2_pin1, HIGH);
      digitalWrite(motor2_pin2, LOW);
      ledcWrite(pwm_channel1, speed);
      ledcWrite(pwm_channel2, speed);
    } else if (m=='L') {
      digitalWrite(motor1_pin1, HIGH);
      digitalWrite(motor1_pin2, LOW);
      digitalWrite(motor2_pin1, LOW);
      digitalWrite(motor2_pin2, HIGH);
      ledcWrite(pwm_channel1, speed);
      ledcWrite(pwm_channel2, speed);
    } else if (m=='I') {
      digitalWrite(motor1_pin1, LOW);
      digitalWrite(motor1_pin2, LOW);
      digitalWrite(motor2_pin1, HIGH);
      digitalWrite(motor2_pin2, LOW);
      ledcWrite(pwm_channel1, speed);
      ledcWrite(pwm_channel2, speed);
    } else if (m=='G') {
      digitalWrite(motor1_pin1, HIGH);
      digitalWrite(motor1_pin2, LOW);
      digitalWrite(motor2_pin1, LOW);
      digitalWrite(motor2_pin2, LOW);
      ledcWrite(pwm_channel1, speed);
      ledcWrite(pwm_channel2, speed);
    } else if (m=='J') {
      digitalWrite(motor1_pin1, LOW);
      digitalWrite(motor1_pin2, LOW);
      digitalWrite(motor2_pin1, LOW);
      digitalWrite(motor2_pin2, HIGH);
      ledcWrite(pwm_channel1, speed);
      ledcWrite(pwm_channel2, speed);
    } else if (m=='H') {
      digitalWrite(motor1_pin1, LOW);
      digitalWrite(motor1_pin2, HIGH);
      digitalWrite(motor2_pin1, LOW);
      digitalWrite(motor2_pin2, LOW);
      ledcWrite(pwm_channel1, speed);
      ledcWrite(pwm_channel2, speed);
    } else {
      digitalWrite(motor1_pin1, LOW);
      digitalWrite(motor1_pin2, LOW);
      digitalWrite(motor2_pin1, LOW);
      digitalWrite(motor2_pin2, LOW);
    }
  }
}
