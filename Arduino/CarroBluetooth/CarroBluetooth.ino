#include "BluetoothSerial.h"

#define PIN_MOTOR_1A 27
#define PIN_MOTOR_1B 26

#define PIN_ENABLE 25

#define PIN_MOTOR_2A 14
#define PIN_MOTOR_2B 12

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluettoth is not enabled
#endif

BluetoothSerial SerialBT;
String completo;
String orientacion;

void setup() {
  pinMode(PIN_MOTOR_1A, OUTPUT);
  pinMode(PIN_MOTOR_1B, OUTPUT);
  pinMode(PIN_MOTOR_2A, OUTPUT);
  pinMode(PIN_MOTOR_2B, OUTPUT);
  pinMode(PIN_ENABLE, OUTPUT);
  digitalWrite(PIN_ENABLE, HIGH);
  Serial.begin(9600);
  SerialBT.begin("Fher Car");
  // put your setup code here, to run once:

}

void loop() {
  if (SerialBT.available()) {
    completo = "";
  }
  while (SerialBT.available()) {
    char dato = SerialBT.read();
    if (dato == '.') {
      if (completo.length() < 5) {
        orientacion = completo.substring(0, 1);
        completo = completo.substring(1, completo.length());
        if (orientacion == "e") {
          Serial.println("C: " + completo);
          adelante();
        }
        if (orientacion == "a") {
          Serial.println("C: " + completo);
          atras();
        }
        if (orientacion == "d") {
          Serial.println("C: " + completo);
          derecha();
        }
        if (orientacion == "i") {
          Serial.println("C: " + completo);
          izquierda();
        }
        if (completo.toInt() <= 0) {
          Serial.println("C: " + completo);
          detener();
        }
      }
      delay(50);
      break;
    } else {
      completo += dato;
    }
  }
}

void adelante() {
  Serial.println("Hacia adelante...");
  // Llanta uno hacia adelante
  digitalWrite(PIN_MOTOR_1A, HIGH);
  digitalWrite(PIN_MOTOR_1B, LOW);
  // Llanta dos hacia adelante
  digitalWrite(PIN_MOTOR_2A, HIGH);
  digitalWrite(PIN_MOTOR_2B, LOW);
}

void atras() {
  // Llanta uno hacia atrás
  Serial.println("Hacia atrás...");
  digitalWrite(PIN_MOTOR_1A, LOW);
  digitalWrite(PIN_MOTOR_1B, HIGH);
  // Llanta dos hacia atrás
  digitalWrite(PIN_MOTOR_2A, LOW);
  digitalWrite(PIN_MOTOR_2B, HIGH);
}

void izquierda() {
  Serial.println("A la izquierda...");
  // Llanta uno hacia atrás
  digitalWrite(PIN_MOTOR_1A, LOW);
  digitalWrite(PIN_MOTOR_1B, HIGH);
  // Llanta dos hacia adelante
  digitalWrite(PIN_MOTOR_2A, HIGH);
  digitalWrite(PIN_MOTOR_2B, LOW);
}

void derecha() {
  Serial.println("A la derecha...");
  // Llanta uno hacia adelante
  digitalWrite(PIN_MOTOR_1A, HIGH);
  digitalWrite(PIN_MOTOR_1B, LOW);
  // Llanta dos hacia atrás
  digitalWrite(PIN_MOTOR_2A, LOW);
  digitalWrite(PIN_MOTOR_2B, HIGH);
}
void detener() {
  Serial.println("Detenido.");
  // Todo en bajo
  digitalWrite(PIN_MOTOR_1A, LOW);
  digitalWrite(PIN_MOTOR_1B, LOW);
  digitalWrite(PIN_MOTOR_2A, LOW);
  digitalWrite(PIN_MOTOR_2B, LOW);
}
