/*
  Distance Measuring Device - Arduino Uno

  An HC-SR04 ultrasonic sensor measures the distance to an object and a
  16x2 I2C LCD shows it in centimetres.

  Library needed: "LiquidCrystal I2C" (Library Manager in the Arduino IDE).

  Change the pin numbers and the LCD address below to match your wiring.
  If the LCD stays blank, try address 0x3F instead of 0x27.
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int TRIG_PIN = 9;
const int ECHO_PIN = 10;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Distance:");
}

float readDistanceCm() {
  // 10 microsecond pulse on TRIG starts a measurement
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Time the echo pulse; sound travels about 0.0343 cm per microsecond,
  // and the pulse covers the trip there and back, so divide by 2
  long duration = pulseIn(ECHO_PIN, HIGH, 30000);
  if (duration == 0) return -1;  // nothing detected
  return duration * 0.0343 / 2;
}

void loop() {
  float cm = readDistanceCm();

  lcd.setCursor(0, 1);
  if (cm < 0) {
    lcd.print("Out of range    ");
  } else {
    lcd.print(cm, 2);
    lcd.print(" cm      ");
  }
  delay(300);
}
