/*
 * This ESP32 code is created by esp32io.com
 *
 * This ESP32 code is released in the public domain
 *
 * For more detail (instruction and wiring diagram), visit https://esp32io.com/tutorials/esp32-car
 */


//#define ENA_PIN 14          // The ESP32 pin GPIO14 connected to the ENA pin L298N
#define IN1_PIN 27          // The ESP32 pin GPIO27 connected to the IN1 pin L298N
#define IN2_PIN 26          // The ESP32 pin GPIO26 connected to the IN2 pin L298N
#define IN3_PIN 25          // The ESP32 pin GPIO25 connected to the IN3 pin L298N
#define IN4_PIN 33          // The ESP32 pin GPIO33 connected to the IN4 pin L298N
// #define ENB_PIN 32          // The ESP32 pin GPIO32 connected to the ENB pin L298N

void setup() {
  Serial.begin(9600);

  // pinMode(ENA_PIN, OUTPUT);
  pinMode(IN1_PIN, OUTPUT);
  pinMode(IN2_PIN, OUTPUT);
  pinMode(IN3_PIN, OUTPUT);
  pinMode(IN4_PIN, OUTPUT);
  // pinMode(ENB_PIN, OUTPUT);

  // digitalWrite(ENA_PIN, HIGH);  // set full speed
  // digitalWrite(ENB_PIN, HIGH);  // set full speed
}

void loop() {
  if (Serial.available()) {                         // if there is data comming
    String command = Serial.readStringUntil('\n');  // read string until newline character

    if (command == "W") {
      Serial.println("ADELANTE");
      CAR_moveForward();
    } else if (command == "A") {
      Serial.println("IZQUIERDA");
      CAR_turnLeft();
    } else if (command == "D") {
      Serial.println("DERECHA");
      CAR_turnRight();
    } else if (command == "S") {
      Serial.println("ATRAS");
      CAR_moveBackward();
    } else {
      Serial.println("DETENER");
      CAR_stop();
    }
  }
}

void CAR_moveBackward() {
  digitalWrite(IN1_PIN, HIGH);
  digitalWrite(IN2_PIN, LOW);
  digitalWrite(IN3_PIN, HIGH);
  digitalWrite(IN4_PIN, LOW);
}

void CAR_moveForward() {
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, HIGH);
  digitalWrite(IN3_PIN, LOW);
  digitalWrite(IN4_PIN, HIGH);
}

void CAR_turnLeft() {
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, HIGH);
  digitalWrite(IN3_PIN, LOW);
  digitalWrite(IN4_PIN, LOW);
}

void CAR_turnRight() {
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, LOW);
  digitalWrite(IN3_PIN, LOW);
  digitalWrite(IN4_PIN, HIGH);
}

void CAR_stop() {
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, LOW);
  digitalWrite(IN3_PIN, LOW);
  digitalWrite(IN4_PIN, LOW);
}