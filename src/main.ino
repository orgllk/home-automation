#include <Arduino.h>

#define ledPin 8   // LED of outside home
#define buttone 7
#define motor 6
unsigned long previousMillis = 0;  // Stores the time when last checked
const unsigned long oneDay = 86400000;  // One day in milliseconds (24 hours)
const unsigned long sevenPM = 19 * 60 * 60 * 1000;  // 7 PM in milliseconds
const unsigned long eightAM = (24 + 8) * 60 * 60 * 1000;  // 8 AM next day in milliseconds (32 hours total)

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);  // Ensure the LED is off initially

}

void loop() {
  unsigned long currentMillis = millis();  // Get the current time

  // If it's between 7 PM and 8 AM the next day, turn on the LED
  if ((currentMillis - previousMillis >= sevenPM) && (currentMillis - previousMillis < eightAM)) {
    digitalWrite(ledPin, HIGH);  // Turn on the LED at 7 PM
  } else {
    digitalWrite(ledPin, LOW);   // Turn off the LED at 8 AM
  }

  // Reset time after 24 hours to prevent overflow
  if (currentMillis - previousMillis >= oneDay) {
    previousMillis = currentMillis;  // Reset previousMillis for the next 24 hours
  }
  if (digitalRead(buttone == HIGH)){
    digitalWrite(motor,HIGH);
  }else{
    digitalWrite(motor,LOW);
  }
}
