int ENA = 18;
int IN1 = 5;
int IN2 = 4;

const int frequency = 500;
const int pwm_channel = 0;
const int resolution = 8;

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT); 
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  ledcSetup(pwm_channel, frequency, resolution);
  ledcAttachPin(ENA, pwm_channel);
}

void loop() {
  setDirection();
  delay(1000);
  changeSpeed();
  delay(1000);
}

void setDirection() {

  ledcWrite(pwm_channel, 255);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  delay(5000);
  
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  delay(5000);
  
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}

void changeSpeed() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  
  for (int i = 0; i < 256; i++) {;
  ledcWrite(pwm_channel,i);
    delay(20);
  }
  
  for (int i = 255; i >= 0; --i) {
  ledcWrite(pwm_channel,i);
    delay(20);
  }
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}