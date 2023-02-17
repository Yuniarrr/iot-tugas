bool nyala = false;
void setup() {
  // initialize digital pin GIOP18 as an output.
  pinMode(18, OUTPUT);
  pinMode(23, INPUT_PULLUP);
}

// the loop function runs over and over again forever
void loop() {
  if(nyala) {
    digitalWrite(18, HIGH);
  } else {
    digitalWrite(18, LOW);
  }

  if(digitalRead(23) == LOW) {
    nyala = !nyala;
  }
}