//made by orgllk-jagat
// 0.2 
// home auto 
// updated on 21/12/24
#include <Arduino.h>
char val;
long duration;
int distance;
#define autobutt  13  //  moter automation globel on 
#define globelled 12  //  ON
#define ultled    2   //  ultrasonic LED
#define motorled  3   //  motor LED
#define ultledc   4   //  ultrasonic button check
#define echopin   5   //  yellow sensor
#define trigpin   6   //  violet sensor
#define motor     7   //  relay
#define motorledc 13  //MOTER BUTTON led 
/////MOTER/////
//-----X-----//
///END///ND///
#define ledPin    8   // LED of outside home
#define buttone   9
#define motorhs   10  //house mt 
#define ire       11
#define homebut   A1
#define moteralrm A2 //ARM FOR MOTER 
unsigned long previousMillis = 0;  // Stores the time when last checked
const unsigned long oneDay = 86400000;  // One day in milliseconds (24 hours)
const unsigned long sevenPM = 19 * 60 * 60 * 1000;  // 7 PM in milliseconds
const unsigned long eightAM = (24 + 8) * 60 * 60 * 1000;  // 8 AM next day in milliseconds (32 hours total)
////END////
//---X---//
void setup() {
  pinMode(ledPin,  OUTPUT);
  digitalWrite(ledPin,LOW);  // Ensure the LED is off initially
  pinMode(trigpin, OUTPUT); 
  pinMode(echopin,  INPUT); 
  pinMode(motor,   OUTPUT);
  Serial.begin(9600); 
  /////end//////
  //----x----//
  pinMode(globelled, OUTPUT);
  pinMode(ultled,    OUTPUT);
  pinMode(motorled,  OUTPUT);
  pinMode(ultledc,   INPUT);   // Set pin modes for buttons
  pinMode(motorledc, INPUT);
  pinMode(autobutt,  INPUT);
  pinMode(homebut,   INPUT);
  //pinMode(moteralrm, OUTPUT);
}
void home (){
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
////////////
//--x--//
void loop() {
digitalWrite(globelled, HIGH); // Global light on
if (digitalRead(autobutt == HIGH)){
 autopump();
}else{
  return autopump ;
}
////home////
if (digitalRead(autobutt == HIGH)){
 home;
}else {
  return home ;
}
}
//-------------x-----------// 
///////////////////////////// 
//-----------x------------// 
void autopump() {  
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
  if (x == LOW) { //should be hotwired
    digitalWrite(ultled, HIGH);
  } else {
    digitalWrite(ultled, LOW);
  }
  ///
  ///
  if (y == LOW) {///should me hotwire
    digitalWrite(motorled, HIGH);
  
  } else {
    digitalWrite(motorled, LOW);
  }
}
///////////////////////////
//////////////////////////
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
