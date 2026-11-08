#include <ESP32Servo.h>

#define SERVO_PIN 13  // ESP26 pin GPIO13 connected to servo motor

Servo servoMotor;

void setup() {
  Serial.begin(9600);
  servoMotor.attach(SERVO_PIN);  // attaches the servo on ESP32 pin
}

void loop() {
  if (Serial.available()) {                         // if there is data comming
    String command = Serial.readStringUntil('\n');  // read string until newline character

    if (command == "0") {
      posInicial();
      Serial.println("GIRA A 0 GRADOS");
    } else if (command == "90") {
      posCentro();
      Serial.println("GIRA A 90 GRADOS");
    } else if (command == "180") {
      posFinal();
      Serial.println("GIRA A 180 GRADOS");
    } else {
      moverAGrados(command.toInt());
      Serial.println("GIRA A " + command +  " GRADOS");
    }
  }
}

void posInicial() {
  servoMotor.write(0);
  delay(15);
}

void posCentro() {
  servoMotor.write(90);
  delay(15);
}

void posFinal() {
  servoMotor.write(180);
  delay(15);
}

void moverAGrados(int grados) {
  servoMotor.write(grados);
  delay(15);
}

void de0A180() {
  int espera = 30;
  int paso = 2;
  // rotates from 0 degrees to 180 degrees
  for (int pos = 0; pos <= 180; pos += paso) {
    // in steps of 1 degree
    servoMotor.write(pos);
    delay(espera);  // waits 15ms to reach the position
  }

  // rotates from 180 degrees to 0 degrees
  for (int pos = 180; pos >= 0; pos -= paso) {
    servoMotor.write(pos);
    delay(espera);  // waits 15ms to reach the position
  }
  Serial.println("AQUI TERMINA UN LOOP");
}