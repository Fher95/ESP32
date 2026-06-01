#include <ESP32Servo.h>

#define IN1_PIN 27
#define IN2_PIN 26
#define IN3_PIN 25
#define IN4_PIN 33

#define SERVO_PIN 13

#define TRIG_PIN 12
#define ECHO_PIN 14

Servo servoMotor;

String direccion = "FRENTE";
float duration_us, distance_cm;
int delayGiro = 500;

void setup() {
  Serial.begin(9600);
  pinMode(IN1_PIN, OUTPUT);
  pinMode(IN2_PIN, OUTPUT);
  pinMode(IN3_PIN, OUTPUT);
  pinMode(IN4_PIN, OUTPUT);
  servoMotor.attach(SERVO_PIN);
  // configure the trigger pin to output mode
  pinMode(TRIG_PIN, OUTPUT);
  // configure the echo pin to input mode
  pinMode(ECHO_PIN, INPUT);
  // Inicialmente mira al frente
  moverServoGrados(90);
}

void loop() {
  if (puedeSeguir()) {
    Serial.println("ANDA HACIA ADELANTE");
    CAR_moverAdelante();
    moverServoGrados(90);
    direccion = "FRENTE";
  } else {
    CAR_detener();
    alternarDireccion();
  }
}

void alternarDireccion() {
  Serial.println("DIRECCION ACTUAL: " + direccion);
  if (direccion == "FRENTE") {
    // Se mueve a la izquierda
    moverServoGrados(135);
    delay(1000);
    direccion = "IZQUIERDA";
    if (puedeSeguir()) {
      CAR_girarIzquierda();
      delay(delayGiro);
      CAR_detener();
      // Servo vuelve al frente
      moverServoGrados(90);
      return;
    }
  }
  if (direccion == "IZQUIERDA") {
    // Se mueve a la derecha
    moverServoGrados(45);
    delay(1000);
    direccion = "DERECHA";
    if (puedeSeguir()) {
      CAR_girarDerecha();
      delay(delayGiro);
      CAR_detener();
      moverServoGrados(90);
      return;
    }
  }
  if (direccion == "DERECHA") {
    // VUELVE A MIRAR AL FRENTE PARA RETROCEDER
    direccion = "FRENTE";
    if (!puedeSeguir()) {
      CAR_moverAtras();
      delay(1000);
      CAR_detener();
      moverServoGrados(90);
      Serial.println("CAMBIA DIRECCION: " + direccion);
    }
  }
}

bool puedeSeguir() {
  float distActual = medirDistancia();
  if (distActual >= 45) {
    Serial.println("PUEDE SEGUIR");
    return true;
  }
  Serial.println("SE DETIENE");
  return false;
}

void moverServoGrados(int grados) {
  servoMotor.write(grados);
  delay(15);
}

float medirDistancia() {
  // generate 10-microsecond pulse to TRIG pin
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // measure duration of pulse from ECHO pin
  duration_us = pulseIn(ECHO_PIN, HIGH);

  // calculate the distance
  distance_cm = 0.017 * duration_us;

  // print the value to Serial Monitor
  Serial.print("distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

  return distance_cm;
}

void CAR_moverAtras() {
  digitalWrite(IN1_PIN, HIGH);
  digitalWrite(IN2_PIN, LOW);
  digitalWrite(IN3_PIN, HIGH);
  digitalWrite(IN4_PIN, LOW);
}

void CAR_moverAdelante() {
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, HIGH);
  digitalWrite(IN3_PIN, LOW);
  digitalWrite(IN4_PIN, HIGH);
}

void CAR_girarIzquierda() {
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, LOW);
  digitalWrite(IN3_PIN, LOW);
  digitalWrite(IN4_PIN, HIGH);
}

void CAR_girarDerecha() {
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, HIGH);
  digitalWrite(IN3_PIN, LOW);
  digitalWrite(IN4_PIN, LOW);
}

void CAR_detener() {
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, LOW);
  digitalWrite(IN3_PIN, LOW);
  digitalWrite(IN4_PIN, LOW);
}