#include <SPI.h>
#include <RF24.h>

RF24 radio(9, 10);
const byte address[6] = "00001";

const int BUTTON_PIN = 4;
const int LED_PIN = 5;
int lastButtonState = HIGH;

void setup() {
  Serial.begin(9600);
  
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  
  if (!radio.begin()) {
    Serial.println("Unit 1: NRF24 initialization failed!");
    while (1) {}
  }
  
  // Setup as BOTH transmitter and receiver
  radio.openWritingPipe(address);
  radio.openReadingPipe(1, address);
  
  radio.setPALevel(RF24_PA_MIN);
  radio.setDataRate(RF24_250KBPS);
  radio.setChannel(76);
  
  // Start in RX mode (listening)
  radio.startListening();
  
  Serial.println("Unit 1: Initialized - Ready for bidirectional communication");
}

void loop() {
  // RX phase: Listen for messages
  radio.startListening();
  delay(100);
  
  if (radio.available()) {
    char message[32] = "";
    radio.read(&message, sizeof(message));
    
    Serial.print("Unit 1 received: ");
    Serial.println(message);
    
    if (strcmp(message, "BUTTON2_PRESSED") == 0) {
      Serial.println("LED ON (received from Unit 2)");
      digitalWrite(LED_PIN, HIGH);
      delay(500);
      digitalWrite(LED_PIN, LOW);
      Serial.println("LED OFF");
    }
  }
  
  // TX phase: Send button press
  int buttonState = digitalRead(BUTTON_PIN);
  
  if (buttonState == LOW && lastButtonState == HIGH) {
    radio.stopListening();  // Switch to TX mode
    delay(10);
    
    const char message[] = "BUTTON1_PRESSED";
    
    if (radio.write(&message, sizeof(message))) {
      Serial.println("Unit 1 sent: BUTTON1_PRESSED");
    } else {
      Serial.println("Unit 1: Failed to send");
    }
    
    delay(10);
  }
  
  lastButtonState = buttonState;
  delay(10);
}