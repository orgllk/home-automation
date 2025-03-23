#include <Arduino.h>
// made by orgllk-jagat
// 2.0
// Home Automation
// Updated on 8/2/25

// Declare variables for sensors and components
char val;  // Temporary storage for input
long duration;  // Duration of ultrasonic pulse
int distance;  // Calculated distance from ultrasonic sensor
int sensorValue = 0;  // Soil moisture sensor value
unsigned long previousMillis = 0;  // Stores the last checked time
const unsigned long oneDay = 86400000;  // One day in milliseconds (24 hours)
const unsigned long sevenPM = 19 * 60 * 60 * 1000;  // 7 PM in milliseconds
const unsigned long eightAM = (24 + 8) * 60 * 60 * 1000;  // 8 AM next day in milliseconds (32 hours)

// Define pins for components (fixed duplicates)
#define autoButton              13  // Motor automation global on
#define globalLED               12  // Global system indicator LED
#define motorLED                2   // Motor operation LED
#define motorButtonLED          14  // Relay motor button LED
#define motorAlarm              15  // Motor alarm for abnormal conditions
#define ledPin                  3   // LED for outside home indication
#define buttonE                 4   // Button to control curtain motor
#define motorHS                 5   // Curtain motor control pin
#define irigationsenser         19  // Soil moisture sensor pin
#define irigationsenserbutton   16  // Button for soil moisture sensor control
#define irepumprelay            17  // Relay to control irrigation pump
#define irepumpled              18  // LED indicator for irrigation pump
#define level1                  6   // Water level sensor for low level
#define level2                  7   // Water level sensor for mid level
#define top                     8   // Water level sensor for top level
#define motorRelay              9   // Motor relay control pin
#define chargeButton            10  // Button for charge control
#define charge                  11  // Charge control pin
#define chargeLED               20  // Charge status indicator LED
#define chargeCheck             21  // Charge check sensor
#define motorRelayLED           22  // Indicator for motor relay operation

void setup() {
  // Initialize output pins
  pinMode(ledPin, OUTPUT); digitalWrite(ledPin, LOW);  // Ensure LED is off initially
  pinMode(motor, OUTPUT); pinMode(motorAlarm, OUTPUT);
  pinMode(motorHS, OUTPUT); pinMode(globalLED, OUTPUT); pinMode(motorLED, OUTPUT);
  pinMode(irepumprelay, OUTPUT); pinMode(irepumpled, OUTPUT);
  pinMode(motorRelay, OUTPUT); pinMode(motorRelayLED, OUTPUT);
  pinMode(charge, OUTPUT); pinMode(chargeLED, OUTPUT);

  // Initialize input pins
  pinMode(motorButtonLED, INPUT); pinMode(autoButton, INPUT);
  pinMode(irigationsenserbutton, INPUT); pinMode(chargeCheck, INPUT);
  pinMode(level1, INPUT); pinMode(level2, INPUT); pinMode(top, INPUT);

  // Start serial communication
  Serial.begin(9600);
}

// Function to control home lights and curtains
void home() {
  unsigned long currentMillis = millis();  // Get current time
  // Check if current time is between 7 PM and 8 AM
  if ((currentMillis - previousMillis >= sevenPM) && (currentMillis - previousMillis < eightAM)) {
    digitalWrite(ledPin, HIGH);  // Turn on LED at 7 PM
  } else {
    digitalWrite(ledPin, LOW);   // Turn off LED at 8 AM
  }
  // Reset timer every 24 hours to avoid overflow
  if (currentMillis - previousMillis >= oneDay) {
    previousMillis = currentMillis;
  }

  // Curtain motor control based on button press
  if (digitalRead(buttonE) == HIGH) {
    digitalWrite(motorHS, HIGH);  // Turn on curtain motor
  } else {
    digitalWrite(motorHS, LOW);   // Turn off curtain motor
  }

  // Soil moisture sensor logic for irrigation
  sensorValue = analogRead(irigationsenser);  // Read soil moisture
  Serial.print("Soil Moisture Value: ");
  Serial.println(sensorValue);

  if (digitalRead(irigationsenserbutton) == HIGH) {  // If sensor is enabled
    if (sensorValue > 600) {  // Soil is dry
      digitalWrite(irepumpled, HIGH);  // Turn on pump
    } else if (sensorValue > 100) {  // Soil is moist
      digitalWrite(irepumprelay, LOW);  // Turn off pump
      digitalWrite(irepumpled, LOW);   // Turn off indicator
    }
  }
}

// Logic for motor automation and related functions
void autopump() {
  char input;
  if (Serial.available() > 0) {
    input = Serial.read();  // Read input from serial monitor
    hi();  // Placeholder for pump control logic
  }

  int y = digitalRead(motorButtonLED);  // Read motor button state
  if (y == LOW) {
    digitalWrite(motorLED, HIGH);  // Turn on motor LED
  } else {
    digitalWrite(motorLED, LOW);   // Turn off motor LED
  }
}

// Function to handle specific motor operations
void hi() {
  Serial.println("Auto Pump Running");
  if (digitalRead(autoButton) == HIGH) {
    digitalWrite(motor, HIGH);      // Turn on motor
    digitalWrite(motorLED, HIGH);  // Turn on motor LED
    digitalWrite(motorAlarm, HIGH);  // Trigger motor alarm
  } else {
    digitalWrite(motor, LOW);       // Turn off motor
    digitalWrite(motorLED, LOW);   // Turn off motor LED
    digitalWrite(motorAlarm, LOW);  // Reset motor alarm
  }
}

// Main program loop
void loop() {
  digitalWrite(globalLED, HIGH);  // Indicate system is active
  autopump();  // Run motor automation
  home();      // Run home functions

  // Water level logic for motor pump control
  if (digitalRead(level1) == HIGH && digitalRead(level2) == HIGH && digitalRead(top) == HIGH) {
    digitalWrite(motorRelay, HIGH);      // Turn off pump when full
    digitalWrite(motorRelayLED, HIGH);  // Indicate pump is off
  } else {
    digitalWrite(motorRelay, LOW);       // Turn on pump when not full
    digitalWrite(motorRelayLED, LOW);   // Indicate pump is on
  }

  // Charge control logic
  digitalWrite(charge, HIGH);  // Turn on charging by default
  if (digitalRead(chargeButton) == HIGH) {
    digitalWrite(charge, HIGH);  // Enable charging
  } else {
    digitalWrite(charge, LOW);   // Disable charging
  }
  if (digitalRead(chargeCheck) == HIGH) {
    digitalWrite(chargeLED, HIGH);  // Indicate charging is active
  } else {
    digitalWrite(chargeLED, LOW);   // Indicate charging is inactive
  }
}