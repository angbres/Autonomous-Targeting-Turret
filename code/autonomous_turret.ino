#include <Servo.h>

int pos = 0;
int state = 1;
Servo servo_2;
Servo servo_10; // FIRST RELEASE
Servo servo_9;  // SECOND RELEASE

int motor1Pin = 4;
int motor2Pin = 5;
int motor3Pin = 13;
int motor4Pin = 12;
int speedPin = 6;
int speed2Pin = 11;
int trig = A3;
int echo = A2;

float cm;
float timer;

long microsecondsToCentimeters(float microseconds) {
  return ((microseconds / 1000000.0 * 34300.0) / 2.0);
}

void setup() {
  pinMode(motor1Pin, OUTPUT);
  pinMode(motor2Pin, OUTPUT);
  pinMode(speedPin, OUTPUT);
  pinMode(motor3Pin, OUTPUT);
  pinMode(motor4Pin, OUTPUT);
  pinMode(speed2Pin, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  Serial.begin(9600);

  servo_2.attach(A0, 500, 2500);
  servo_10.attach(10, 500, 2500);
  servo_9.attach(9, 500, 2500);

  servo_10.write(140);
  servo_9.write(140);
}

void loop() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  timer = pulseIn(echo, HIGH, 50000);
  cm = microsecondsToCentimeters(timer);

  while ((cm > 35) || (cm == 0)) {
    digitalWrite(speedPin, LOW);
    digitalWrite(speed2Pin, LOW);

    servo_2.write(pos);
    if (state == 1) pos++;
    else pos--;

    if (pos == 180) state = -1;
    if (pos == 10) state = 1;

    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);

    timer = pulseIn(echo, HIGH, 50000);
    cm = microsecondsToCentimeters(timer);
    Serial.println("FINDING");
    delay(1);
  }

  while ((cm <= 35) && (cm != 0)) {
    digitalWrite(speedPin, LOW);
    digitalWrite(speed2Pin, LOW);

    servo_10.write(80);
    delay(750);
    servo_10.write(130);
    servo_9.write(80);
    delay(700);
    servo_9.write(120);
    delay(450);

    digitalWrite(speedPin, HIGH);
    digitalWrite(speed2Pin, HIGH);
    digitalWrite(motor1Pin, LOW);
    digitalWrite(motor2Pin, HIGH);
    digitalWrite(motor3Pin, LOW);
    digitalWrite(motor4Pin, HIGH);

    delay(750);
    Serial.println("Shoot");

    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    timer = pulseIn(echo, HIGH, 50000);
    cm = microsecondsToCentimeters(timer);
  }
}
