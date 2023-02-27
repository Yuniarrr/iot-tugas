/*
NOTE: PIN

DHT11 ESP32
GND   GND
DAT   IO21
VCC   3V3

BTN   ESP32
GND   GND
S0    IO25 
S1    IO33
S2    IO32
S3    IO35

OLED  ESP32
GND   GND
SDA   IO18
SCL   IO22
5V    VIN
*/

#include <DHT.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define DHT_SENSOR_PIN  21 // ESP32 pin GIOP21 connected to DHT11 sensor
#define DHT_SENSOR_TYPE DHT11
#define BLYNK_TEMPLATE_ID "TMPL2IWywrVQ"
#define BLYNK_TEMPLATE_NAME "Temperature Detector"
#define BLYNK_AUTH_TOKEN "AV2J9tdskGY480clqV3rAOU3O2ucKmdP"
#define BLYNK_PRINT Serial
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define BUTTON_HOME 25
#define BUTTON_HUMIDITY 33
#define BUTTON_TEMP_C 32 
#define BUTTON_TEMP_F 35

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "OPPO A16";
char pass[] = "halo1234";

// for button
int button_state = LOW;
int last_button_state;
int option = 0;
// Blynk Timer
BlynkTimer timer;

// Set for dht11 pin
DHT dht_sensor(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
float getHumidity()
{
  float humi = dht_sensor.readHumidity();
  
  if ( isnan(humi) ) {
    Serial.println("Failed to read humidity from DHT sensor!");
    return NULL;
  }

  return humi;
}

float getTempC()
{
  float tempC = dht_sensor.readTemperature();
  
  if ( isnan(tempC) ) {
    Serial.println("Failed to read temperature celcius from DHT sensor!");
    return NULL;
  }

  return tempC;
}

float getTempF()
{
  float tempF = dht_sensor.readTemperature(true);
  
  if ( isnan(tempF) ) {
    Serial.println("Failed to read temperature farenheit from DHT sensor!");
    return NULL;
  }
  
  return tempF;
}

void displayOnScreen(float data = 0, int type = NULL)
{
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);

  if(type == 1) {
    display.println("Humidity");
    display.setTextSize(3);
    display.setCursor(0, 30);
    display.print(data);
    display.print("%");
  } else if (type == 2) {
    display.println("Temperature(C)");
    display.setTextSize(3);
    display.setCursor(0, 30);
    display.print(data);
    display.print(" C");
  } else if (type == 3) {
    display.println("Temperature(F)");
    display.setTextSize(3);
    display.setCursor(0, 30);
    display.print(data);
    display.print(" F");
  } else {
    display.println("Temperature Detection");
    display.println("Btn 0: Home");
    display.println("Btn 1: Humidity");
    display.println("Btn 2: Temperature(C)");
    display.println("Btn 3: Temperature(F)");
  }
  
  display.display(); 
}

void myTimerEvent()
{
  float humi = getHumidity();
  float tempC = getTempC();
  float tempF = getTempF();

  // Logging
  Serial.print("Humidity: ");
  Serial.print(humi);
  Serial.print("%");
  Serial.print("  |  ");
  Serial.print("Temperature: ");
  Serial.print(tempC);
  Serial.print(" C  ~  ");
  Serial.print(tempF);
  Serial.println(" F");
  
  // Display on OLED
  if (option == 0) {
    displayOnScreen();
  } else if (option == 1) {
    displayOnScreen(humi, option);
  } else if (option == 2) {
    displayOnScreen(tempC, option);
  } else if (option == 3) {
    displayOnScreen(tempF, option);
  } else {
    displayOnScreen();
  }
  
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V0, humi);
  Blynk.virtualWrite(V1, tempC);
  Blynk.virtualWrite(V2, tempF);
}

void setup() {
  Wire.begin(18, 22);
  Serial.begin(9600);

  pinMode(BUTTON_HOME, INPUT_PULLUP);
  pinMode(BUTTON_HUMIDITY, INPUT_PULLUP);
  pinMode(BUTTON_TEMP_C, INPUT_PULLUP);
  pinMode(BUTTON_TEMP_F, INPUT_PULLUP);
  
  dht_sensor.begin(); // initialize the DHT sensor
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  delay(2000);  
  timer.setInterval(1000L, myTimerEvent);
}

void loop() {
  if (digitalRead(BUTTON_HOME) == LOW) {
    Serial.println("BUTTON_HOME pressed!");
    last_button_state = button_state;
    button_state = digitalRead(BUTTON_HOME);
    option = 0;
  } else if (digitalRead(BUTTON_HUMIDITY) == LOW) {
    Serial.println("BUTTON_HUMIDITY pressed!");
    last_button_state = button_state;
    button_state = digitalRead(BUTTON_HUMIDITY);
    option = 1;
  } else if (digitalRead(BUTTON_TEMP_C) == LOW) {
    Serial.println("BUTTON_TEMP_C pressed!");
    last_button_state = button_state;
    button_state = digitalRead(BUTTON_TEMP_C);
    option = 2;
  } else if (digitalRead(BUTTON_TEMP_F) == LOW) {
    Serial.println("BUTTON_TEMP_F pressed!");
    last_button_state = button_state;
    button_state = digitalRead(BUTTON_TEMP_F);
    option = 3;
  } else {

  }

  Blynk.run();
  timer.run(); // Initiates BlynkTimer
  delay(100);
}
