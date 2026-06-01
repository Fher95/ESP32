/*
 * This ESP32 code is created by esp32io.com
 *
 * This ESP32 code is released in the public domain
 *
 * For more detail (instruction and wiring diagram), visit https://esp32io.com/tutorials/esp32-serial-monitor
 */

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT); // set the digital pin as output:
}

void loop() {
  if (Serial.available()) { // if there is data comming
    String command = Serial.readStringUntil('\n'); // read string until newline character

    if (command == "ON") {
      digitalWrite(LED_BUILTIN, HIGH); // turn on LED
      Serial.println("Turn LED ON");
    } else if (command == "OFF") {
      digitalWrite(LED_BUILTIN, LOW);  // turn off LED
      Serial.println("Turn LED OFF");
    }
  }
}
