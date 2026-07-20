#include <SPI.h>
#include <RF24.h>

RF24 radio(9, 10);
const byte address[6] = "00001";
const int BUTTON_PIN = 4;
int lastButtonState = HIGH;

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  if (!radio.begin()) {
    Serial.println("NRF24 initialization failed!");
    while (1) {}
  }
  
  radio.openWritingPipe(address);
  radio.stopListening();
  radio.setPALevel(RF24_PA_MIN);
  radio.setDataRate(RF24_250KBPS);
  radio.setChannel(76);
  
  Serial.println("TX Initialized successfully!");
}

void loop() {
  int buttonState = digitalRead(BUTTON_PIN);
  
  if (buttonState == LOW && lastButtonState == HIGH) {
    const char message[] = "BUTTON_PRESSED";
    
    if (radio.write(&message, sizeof(message))) {
      Serial.println("Message sent: BUTTON_PRESSED");
    } else {
      Serial.println("Failed to send message");
    }
    delay(50);
  }
  
  lastButtonState = buttonState;
  delay(10);
}