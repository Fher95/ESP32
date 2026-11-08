
#define PIN2 2
#define MIN_SPEED 50
#define MAX_SPEED 1000
int pipSpeed = 50;
int step = -100;


void setup() {
  Serial.begin(9600);
  pinMode(PIN2, OUTPUT);
  
}

void loop() {
  doublePip();
  delay(500);
  manageSpeed();
}

void doublePip() {
  digitalWrite(PIN2, HIGH);
  delay(pipSpeed);
  digitalWrite(PIN2, LOW);
  delay(pipSpeed);
  digitalWrite(PIN2, HIGH);
  delay(pipSpeed);
  digitalWrite(PIN2, LOW);
}

void manageSpeed() {
  if (pipSpeed >= MAX_SPEED || pipSpeed <= MIN_SPEED) {
    step = step * -1;
  }
  pipSpeed += step;
  Serial.println(String("VELOCIDAD: ") + pipSpeed);
}