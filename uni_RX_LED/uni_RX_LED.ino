#include <SPI.h>
#include <RF24.h>

// Create RF24 object (CE pin = 9, CSN pin = 10)
RF24 radio(9, 10);

// Define the address for communication (MUST be same as TX)
const byte address[6] = "00001";

// LED pin
const int LED_PIN = 5;

void setup() {
  Serial.begin(9600);
  
  // Initialize LED pin as output
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW); // LED off initially
  
  // Initialize RF24
  if (!radio.begin()) {
    Serial.println("RX initialization failed!");
    while (1) {} // Halt if NRF24 fails
  }
  
  // Set module as receiver
  radio.openReadingPipe(1, address);
  radio.startListening();
  
  // Configure RF24 settings (MUST MATCH TX)
  radio.setPALevel(RF24_PA_MIN);  // Same as TX
  radio.setDataRate(RF24_250KBPS); // Same as TX
  radio.setChannel(76);             // Same as TX
  
  Serial.println("RX Initialized successfully!");
  Serial.println("Waiting for messages...");
}

void loop() {
  // Check if data is available
  if (radio.available()) {
    char message[32] = "";
    
    // Read the message
    radio.read(&message, sizeof(message));
    
    Serial.print("Message received: ");
    Serial.println(message);
    
    // Check if button pressed message received
    if (strcmp(message, "BUTTON_PRESSED") == 0) {
      Serial.println("Button detected! Turning LED ON");
      
      // Turn LED on
      digitalWrite(LED_PIN, HIGH);
      
      // Keep LED on for 2 seconds
      delay(2000);
      
      // Turn LED off
      digitalWrite(LED_PIN, LOW);
      Serial.println("LED OFF");
    }
  }
  
  delay(10);
}