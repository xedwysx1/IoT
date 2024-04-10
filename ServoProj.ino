#include <Servo.h>

Servo myservo;
Servo myservo1;
const int trigPin = 5;
const int echoPin = 6;
int pos1 = 0;
int pos2 = 180; // atvirksciai idetas

float duration, distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  myservo.attach(7);
  myservo1.attach(8);  
  Serial.begin(9600);
}

void loop() {
  // Measure distance
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration * 0.0343) / 2;
  Serial.print("Distance: ");
  Serial.println(distance);
  delay(100);
  
  // Abi servo pavaros juda kartu.
  for (pos1 = 0, pos2 = 180; pos1 <= 180 && pos2 >= 0; pos1 += 1, pos2 -= 1) { 
   if (distance >=20) {
    myservo.write(pos1);
    myservo1.write(pos2);
    delay(15);           
    } 
    else {
       myservo.write(0);
       myservo1.write(0);
       break;
    }
              
  }
  for (pos1 = 180, pos2 = 0; pos1 >= 0 && pos2 <= 180; pos1 -= 1, pos2 += 1) { 
   if (distance >=20) {
    myservo.write(pos1);
    myservo1.write(pos2);
    delay(15);           
    } 
    else {
       myservo.write(0);
       myservo1.write(0);
       break;
    }                 
  }
}
