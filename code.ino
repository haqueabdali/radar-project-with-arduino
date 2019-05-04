#include <Servo.h>
const int trigPin = 10;
const int echoPin = 11;
const int ledPin = 4;
const int buzz = 5;
long duration;
int distance;
int safetyDistance;
Servo myServo;
void setup() {
    pinMode(trigPin, OUTPUT); 
    pinMode(echoPin, INPUT);
    pinMode(buzz, OUTPUT);
    pinMode(ledPin, OUTPUT);
    Serial.begin(9600);
    myServo.attach(31);
    myServo.attach(33);
    myServo.attach(35);
    myServo.attach(37);
}
void loop() {
    for(int i=1;i<=180;i++){
        myServo.write(i);
        delay(30);
        distance = calculateDistance();
        Serial.print(i); 
        Serial.print("/n"); 
        Serial.print(distance);
        Serial.print("."); 
      safetyDistance = distance;
    if (safetyDistance <= 30 && safetyDistance >=1){
        digitalWrite(buzz, HIGH);
        digitalWrite(ledPin, HIGH);
        delay(safetyDistance);
        digitalWrite(buzz, LOW);
        digitalWrite(ledPin, LOW);
        delay(safetyDistance);
    
    }
    }
    
    for(int i=180;i>1;i--){
        myServo.write(i);
        delay(30);
        distance = calculateDistance();
        Serial.print(i);
        Serial.print(" /n");
        Serial.print(distance);
        Serial.print(".");
        safetyDistance = distance;
    if (safetyDistance <=30 && safetyDistance >=1){
        digitalWrite(buzz, HIGH);
        digitalWrite(ledPin, HIGH);
        delay(safetyDistance);
        digitalWrite(buzz, LOW);
        digitalWrite(ledPin, LOW);
        delay(safetyDistance);
    }
    
    }
    
}

int calculateDistance(){
    digitalWrite(trigPin, LOW);
    delay(2);
  
    digitalWrite(trigPin, HIGH);
    delay(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance= duration/58;
    return distance;
}
