// made by orgllk-jagat
// 0.2.1
// home auto 
// updated on 7/2/25
#include <Arduino.h>
char val;
long duration;
int distance;
#define autoButton              13  // motor automation global on 
#define globalLED               12  // ON
#define ultrasonicLED           2   // ultrasonic LED
#define motorLED                3   // motor LED
#define ultrasonicButtonCheck   4   // ultrasonic button check
#define echoPin                 5   // ultrasonic sensor
#define trigPin                 6   // ultrasonic sensor
#define motor                   7   // relay
#define motorButtonLED          A1  // RELAY MOTOR BUTTON LED 
#define motorAlarm              A2  // ARalM FOR MOTOR 
/////MOTOR/////
//-----X-----//
///END///
//-----X-----//
#define ledPin                   8  // LED of outside home
#define buttonE                  9  // button for curtain for turning on the motor for curtain 
#define motorHS                 10  // house motor for curtain
#define irigationsenser         A3  // senser for moister of soil
#define irigationsenserbutton   A4  // button to turn on and of moister senser 
#define pumprelay               A5  // RELAY for turning the pump of irrigartion
// #define ire       11
// #define homeButton   A1
unsigned long previousMillis = 0;  // Stores the time when last checked
const unsigned long oneDay = 86400000;  // One day in milliseconds (24 hours)
const unsigned long sevenPM = 19 * 60 * 60 * 1000;  // 7 PM in milliseconds
const unsigned long eightAM = (24 + 8) * 60 * 60 * 1000;  // 8 AM next day in milliseconds (32 hours total)
int sensorValue = 0;
////END////
//---X---//
void setup() {
  pinMode(ledPin,       OUTPUT);
  digitalWrite(ledPin,  LOW);  // Ensure the LED is off initially
  pinMode(trigPin,      OUTPUT); 
  pinMode(echoPin,      INPUT); 
  pinMode(motor,        OUTPUT);
  pinMode(motorAlarm,   OUTPUT);
  Serial.begin(9600); 
  /////end//////
  //----X----//
  pinMode(motorHS,                 OUTPUT); 
  pinMode(globalLED,               OUTPUT);
  pinMode(ultrasonicLED,           OUTPUT);
  pinMode(motorLED,                OUTPUT);
  pinMode(ultrasonicButtonCheck,   INPUT);   // Set pin modes for buttons
  pinMode(motorButtonLED,          INPUT);
  pinMode(autoButton,              INPUT);
  pinMode(pumprelay,               OUTPUT);
  pinMode(irigationsenserbutton,   INPUT);
  // pinMode(homeButton,   INPUT);
  //pinMode(motorAlarm, OUTPUT);
}
void home (){
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
  if (digitalRead(buttonE) == HIGH){
    digitalWrite(motorHS ,HIGH);
  }else{
    digitalWrite(motorHS ,LOW);
  }
    ////////////////////
    //-------x-------//
    ////////////////////
    ////irigation/////
sensorValue = analogRead(irigationsenser);
  // Print the sensor value to the Serial Monitor
Serial.print("Soil Moisture Value: ");
Serial.println(sensorValue);
if (digitalRead(irigationsenserbutton) == HIGH){
  // Check if the soil is dry
  if (sensorValue > 600) {
    // Turn the LED on
    digitalWrite(pumprelay, HIGH); //turn the pump on when soil is dry
  } 
  if (sensorValue > 100){
    // Turn the LED off
    digitalWrite(pumprelay, LOW); // turn it  of
  }
}

}
////////////
//--X--//
void loop() {
  digitalWrite(globalLED, HIGH); // Global light on
  if (digitalRead(autoButton) == HIGH){
    autopump();
  }
  ////home////
  if (digitalRead(autoButton) == HIGH){
    home();
  }
}
//-------------X-----------// 
///////////////////////////// 
//-------------X-----------// 
void autopump() {  
  if (Serial.available() > 0) {
    char input = Serial.read(); // Read one byte from the serial buffer
    
    if (input == '0') {
      hi();
    } else {
      hi();
    }
  }
  ///
  ///
  int x = digitalRead(ultrasonicButtonCheck); // Read ultrasonic button state
  int y = digitalRead(motorButtonLED); // Read motor button state
  ///
  ///
  if (x == LOW) { // should be hotwired
    digitalWrite(ultrasonicLED, HIGH);
  } else {
    digitalWrite(ultrasonicLED, LOW);
  }
  ///
  ///
  if (y == LOW) { // should be hotwired
    digitalWrite(motorLED, HIGH);
  } else {
    digitalWrite(motorLED, LOW);
  }
}
///////////////////////////
//////////////////////////
void hi() {
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW); 

  duration = pulseIn(echoPin, HIGH); 
  distance = duration * 0.034 / 2; 
  Serial.println(distance);
  
  if (distance <= 83) {
    digitalWrite(motor, HIGH);
    Serial.println("Off");
    digitalWrite(motorLED, HIGH);
    digitalWrite(motorAlarm  , HIGH);

  } else {
    digitalWrite(motor, LOW);
    Serial.println("On");
    digitalWrite(motorLED, LOW);
    digitalWrite(motorAlarm  , LOW);
  }
  
  delay(1000); // Adjust delay as needed (e.g., 1 second)
}
