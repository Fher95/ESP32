#define PIN2 2
#define SALTO 2
#define RETRASO 10
#define MAX_BRIGHT 120

void setup() {
  Serial.begin(9600);
  pinMode(PIN2, OUTPUT);
}

void loop() {
  fadeUp();
  fadeDown();
}

void fadeUp() {
  for (int i = 0; i <= MAX_BRIGHT; i += SALTO) {
    analogWrite(PIN2, i);
    delay(RETRASO);
  }
}

void fadeDown() {
  for (int i = MAX_BRIGHT; i >= 0; i -= SALTO) {
    analogWrite(PIN2, i);
    delay(RETRASO);
  }
}