
#include "DHT.h"
#include "Wire.h"
#include "LiquidCrystal_I2C.h"

#define DHTTYPE DHT12

// Pin definitions
const int dhtPin = 2;
const int buttonPin = 3;
const int ledPin = 4;
const int buzzerPin = 5;

// Debounce configuration
const int debounceDelay = 50;
int lastButtonState = HIGH;
long lastDebounceTime = 0;
bool systemIsOn = false;

// DHT sensor read configuration
unsigned long lastDHTReadTime = 0;
const unsigned long dhtReadInterval = 2000;

// LCD setup
LiquidCrystal_I2C lcd(0x27, 16, 2);

// DHT sensor
DHT dht(dhtPin, DHTTYPE);

void setup() {
  pinMode(dhtPin, INPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  Serial.begin(9600);
  dht.begin();
  digitalWrite(ledPin, LOW);
  noTone(buzzerPin);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("System Ready!");
}

void loop() {
  handleButtonPress();

  if (systemIsOn && millis() - lastDHTReadTime > dhtReadInterval) {
    lastDHTReadTime = millis();
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    if (isnan(temperature) || isnan(humidity)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }

    updateLCD(temperature, humidity);
    alertIfNeeded(temperature, humidity);
  }
}

void handleButtonPress() {
  int reading = digitalRead(buttonPin);
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading == LOW && lastButtonState == HIGH) {
      systemIsOn = !systemIsOn;
      Serial.println(systemIsOn ? "Monitoring ON" : "Monitoring OFF");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(systemIsOn ? "Monitoring..." : "System Paused");
    }
  }

  lastButtonState = reading;
}

void updateLCD(float temp, float hum) {
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temp);
  lcd.print("C   ");

  lcd.setCursor(0, 1);
  lcd.print("Hum: ");
  lcd.print(hum);
  lcd.print("%   ");
}

void alertIfNeeded(float temp, float hum) {
  // Simple threshold alert
  if (temp > 30 || hum > 70) {
    digitalWrite(ledPin, HIGH);
    tone(buzzerPin, 1000); // 1 kHz
  } else {
    digitalWrite(ledPin, LOW);
    noTone(buzzerPin);
  }
}
