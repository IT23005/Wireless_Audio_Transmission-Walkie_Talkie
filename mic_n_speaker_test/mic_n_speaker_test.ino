#define MIC_PIN A0
#define PWM_OUT 6

void setup() {
  pinMode(PWM_OUT, OUTPUT);
}

void loop() {
  int sum = 0;
  for (int i = 0; i < 32; i++) {
    sum += analogRead(MIC_PIN);
  }
  int sample = sum / 32;
  uint8_t out = sample >> 2;
  analogWrite(PWM_OUT, out);
}