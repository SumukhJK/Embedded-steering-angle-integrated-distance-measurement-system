#include <Servo.h>

const int joyXPin = A0;  // Analog pin for X-axis of joystick
const int joyYPin = A1;  // Analog pin for Y-axis of joystick
const int triggerPin = 9;  // Digital pin for trigger of ultrasonic sensor
const int echoPin = 10;    // Digital pin for echo of ultrasonic sensor

Servo servoMotor;  // Create a servo object

void setup() {
  Serial.begin(9600); // Initialize serial communication
  servoMotor.attach(8); // Attach the servo to pin 8
  pinMode(triggerPin, OUTPUT); // Set trigger pin as OUTPUT
  pinMode(echoPin, INPUT);     // Set echo pin as INPUT
}

void loop() {
  int joyXValue = analogRead(joyXPin); // Read X-axis joystick value
  int joyYValue = analogRead(joyYPin); // Read Y-axis joystick value

  // Map joystick values to servo angles (0-180)
  int servoAngle = map(joyXValue, 0, 1023, 0, 180);

  // Move the servo to the mapped angle
  servoMotor.write(servoAngle);

  // Read distance from ultrasonic sensor
  long duration, distance;
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1; // Convert duration to distance in centimeters

  // Print servo angle and distance
  Serial.print("Servo Angle: ");
  Serial.print(servoAngle);
  Serial.print(", Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(100); // Add a small delay for stability
}
