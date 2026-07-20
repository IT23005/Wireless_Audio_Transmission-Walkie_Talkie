const int MIC_PIN = A0;

void setup() {
  Serial.begin(9600);
  Serial.println("Microphone initialized - Reading audio samples...");
}

void loop() {
  // Read analog value from microphone
  int micValue = analogRead(MIC_PIN);
  
  // Send to Serial (laptop)
  Serial.println(micValue);
  
  // Delay for sampling (adjust if needed)
  delay(10); // ~100 samples per second
}