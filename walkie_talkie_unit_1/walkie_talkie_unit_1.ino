#include <SPI.h>
#include <RF24.h>
#include <RF24Audio.h>

// Initialize the radio on CE=7, CSN=8
RF24 radio(7, 8); 

// Initialize audio using radio, set to radio number 0
RF24Audio rfAudio(radio, 0); 

// Push to Talk Button Pin
const int pttPin = 3; 
bool isTransmitting = false; // Tracks whether the walkie-talkie is talking or listening

void setup() {
  Serial.begin(115200);
  Serial.println("Walkie-Talkie Booting Up...");

  // Set the button pin as an input with internal pull-up resistor
  pinMode(pttPin, INPUT_PULLUP);

  // Initialize the radio
  radio.begin();
  // Check if the radio hardware is responding
  if (radio.isChipConnected()) {
    Serial.println("-> SUCCESS: Radio hardware detected!");
  } else {
    Serial.println("-> WARNING: Radio NOT found! Check your SPI pins (11, 12, 13).");
  }
  
  // Set power to HIGH or MAX since you have the PA/LNA module
  // If audio is stuttering, drop this to RF24_PA_LOW during testing
  radio.setPALevel(RF24_PA_MIN); 
  
  // Initialize the audio library
  rfAudio.begin();
  
  // Default volume is 4. Range is 0 to 7.
  rfAudio.setVolume(5); 
  
  // Start in listening mode
  rfAudio.receive(); 
  Serial.println("System Ready. Listening...");
}

void loop() {
  // Read the PTT button: LOW means it IS pressed, HIGH means it is NOT pressed
  if (digitalRead(pttPin) == LOW) {
    
    // If pressed and not transmitting yet, start talking
    if (!isTransmitting) { 
      Serial.println("-> Transmitting...");
      rfAudio.transmit();    
      isTransmitting = true; 
    }
    
  } else { // Button is released (pin goes HIGH)
    
    // If we were talking, stop and go back to listening
    if (isTransmitting) { 
      Serial.println("<- Listening...");
      rfAudio.receive();      
      isTransmitting = false; 
    }
    
  }
}