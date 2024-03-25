#include <Servo.h>

const int trigPin = 9; // Trigger pin of HC-SR04
const int echoPin = 10; // Echo pin of HC-SR04
const int joyXPin = A0; // Joystick X-axis pin
const int joyYPin = A1; // Joystick Y-axis pin
const int servoPin = 11; // Servo motor pin

Servo servoMotor;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(joyXPin, INPUT);
  pinMode(joyYPin, INPUT);
  servoMotor.attach(servoPin);
}

void loop() {
  int distance = getDistance();
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  int joyXValue = analogRead(joyXPin);
  int joyYValue = analogRead(joyYPin);
  
  int servoAngle = map(joyXValue, 0, 1023, 0, 180); // Mapping joystick X-axis to servo angle
  
  servoMotor.write(servoAngle);

  delay(100); // Delay for stability
}

int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH);
  
  // Calculate distance
  int distance = duration * 0.034 / 2;
  
  return distance;
}
