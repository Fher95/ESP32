#define TRIGGER 12
#define ECHO 13
#define PIN2 2
#define AIR_SPEED_CM 343.2
#define PRINTLN_FRECUENCE 1000  //ms: 4 times in a second

// Velocidad del sonido en el aire, 343,2 m/s. (34320 cm/s)

int LIGHT_STATE = LOW;
long lastTime = 0;
long serialTime = 0;

void setup() {
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(PIN2, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(TRIGGER, HIGH);
  delay(10);
  digitalWrite(TRIGGER, LOW);
  long duration = pulseIn(ECHO, HIGH);  // en microsegundos
  float distance = (AIR_SPEED_CM * duration) / 10000 / 2;
  long currentTime = millis();
  long lightFrecuence = map(distance, 1, 100, 10, 1000);
  lightFrecuence = constrain(lightFrecuence, 10, 1000);
  showConsoleInfo(duration, distance, currentTime, lightFrecuence);

  if ((currentTime - lastTime) >= lightFrecuence) {
    changeLightState();
    lastTime = currentTime;
  }
}

void changeLightState() {
  LIGHT_STATE = LIGHT_STATE == LOW ? HIGH : LOW;
  digitalWrite(PIN2, LIGHT_STATE);
}

void showConsoleInfo(long duration, float distance, long currentMillis, long lightFrecuence) {
  if (currentMillis - serialTime >= PRINTLN_FRECUENCE) {
    Serial.printf("Tiempo: %d microsegundos | Distancia: %0.1f cm | Frecuencia: %ld\n", duration, distance, lightFrecuence);
    serialTime = currentMillis;
  }
}
