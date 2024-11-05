// made by orgllk
// 1.0
// home automation
#include <Arduino.h>

#define echopin 5    // yellow sensor
#define trigpin 4    // violet sensor
#define motor 11     // relay
//
//
#define ultledc 12   // ultrasonic button check
#define motorledc 13 // motor button check
///
///
#define globelled 6  // ON
#define ultled 7     // ultrasonic LED
#define motorled 10  // motor LED
///
///
char val;
long duration;
int distance;
////////////////////
/////////////////////
////////////////////
//////////////////////
//////////////////////
/////SUPERATION////////////////
#define ledPin 9   // LED of outside home
#define buttone 3
#define motor  2
#define ire 8
unsigned long previousMillis = 0;  // Stores the time when last checked
const unsigned long oneDay = 86400000;  // One day in milliseconds (24 hours)
const unsigned long sevenPM = 19 * 60 * 60 * 1000;  // 7 PM in milliseconds
const unsigned long eightAM = (24 + 8) * 60 * 60 * 1000;  // 8 AM next day in milliseconds (32 hours total)

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);  // Ensure the LED is off initially
//////////////////////////
/////////////////////
////////SUPARATION//////////////////
  pinMode(trigpin, OUTPUT); 
  pinMode(echopin, INPUT); 
  pinMode(motor, OUTPUT);
  Serial.begin(9600); 
  //
  //
  pinMode(globelled, OUTPUT);
  pinMode(ultled, OUTPUT);
  pinMode(motorled, OUTPUT);
  //pinMode(calls, OUTPUT);
  pinMode(ultledc, INPUT);   // Set pin modes for buttons
  pinMode(motorledc, INPUT);
}

void loop() {
  unsigned long currentMillis = millis();  // Get the current time

  // If it's between 7 PM and 8 AM the next day, turn on the LED
  if ((currentMillis - previousMillis >= sevenPM) && (currentMillis - previousMillis < eightAM)) {
    digitalWrite(ledPin, HIGH);  // Turn on the LED at 7 PM
    digitalWrite(ire,HIGH);
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
/// //////////////////
/////////////////////////
/////////////////////////////
////////////////////////////////////////
void autopump() {
   digitalWrite(globelled, HIGH); // Global light on
  
  if (Serial.available() > 0) {
    char input = Serial.read(); // Read one byte from the serial buffer
    
    if (input == '0') {
      hi();
     // digitalWrite(calls, HIGH);
    } else {
     return hi() ;
      //digitalWrite(calls, LOW);
    }
  }
  ///
  ///
  int x = digitalRead(ultledc); // Read ultrasonic button state
  int y = digitalRead(motorledc); // Read motor button state
  ///
  ///
  if (x == LOW) {
    digitalWrite(ultled, HIGH);
  } else {
    digitalWrite(ultled, LOW);
  }
  ///
  ///
  
  if (y == LOW) {
    digitalWrite(motorled, HIGH);
  } else {
    digitalWrite(motorled, LOW);
  }
  
  
}
///////////////////////////////////////
//////////////////////////////////////
//////////////////////////////////////
void hi() {
  digitalWrite(trigpin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(trigpin, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(trigpin, LOW); 

  duration = pulseIn(echopin, HIGH); 
  distance = duration * 0.034 / 2; 
  Serial.println(distance);
  
  if (distance <= 83) {
    digitalWrite(motor, HIGH);
    Serial.println("Off ");
    digitalWrite(motorled, HIGH);
  } else {
    digitalWrite(motor, LOW);
    Serial.println("On ");
    digitalWrite(motorled, LOW);
  }
  
  delay(1000); // Adjust delay as needed (e.g., 1 second)
}
