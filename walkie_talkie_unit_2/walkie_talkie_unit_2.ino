#include <SPI.h>
#include <RF24.h>
#include <RF24Audio.h>

// =========================================================================
// HARDWARE CONFIGURATION
// =========================================================================

// Initialize the radio on CE=7, CSN=8
RF24 radio(7, 8); 

// Initialize audio library using the radio object, identifier set to 0
RF24Audio rfAudio(radio, 0); 

// Push to Talk (PTT) Button Pin
const int pttPin = 3; 

// Track whether the walkie-talkie is currently transmitting or listening
// (Needed because the official library lacks an internal status check)
bool isTransmitting = false; 

void setup() {
  // Start serial communication for debugging
  Serial.begin(115200);
  delay(1000); // Short delay to let power stabilize
  Serial.println("\n=== Walkie-Talkie Booting Up ===");

  // Set the button pin as an input with internal pull-up resistor
  // The pin reads HIGH when open, and LOW when pressed to ground
  pinMode(pttPin, INPUT_PULLUP);

  // Initialize the nRF24L01+ Radio
  radio.begin();
  
  // Verify SPI connections by checking if the Arduino can see the radio
  if (radio.isChipConnected()) {
    Serial.println("-> SUCCESS: Radio hardware detected!");
  } else {
    Serial.println("-> WARNING: Radio NOT found! Check your SPI pins (11, 12, 13, CE=7, CSN=8).");
  }
  
  // Power level setup for PA/LNA module:
  // Now that you have the 9V power supply, you can use RF24_PA_HIGH!
  // If you experience any dropouts, you can lower this to RF24_PA_LOW or RF24_PA_MIN.
  radio.setPALevel(RF24_PA_HIGH); 
  
  // Initialize the audio library
  rfAudio.begin();
  
  // Set volume level (Range: 0 to 7)
  // Tuned to 3 to prevent acoustic feedback/screeching loops in close quarters
  rfAudio.setVolume(3); 
  
  // Set unit to default receive/listening mode
  rfAudio.receive(); 
  Serial.println("System Ready. Listening for transmissions...");
}

void loop() {
  // Read the state of the PTT button
  // LOW = Pressed (grounded), HIGH = Released (pulled up to 5V)
  bool buttonPressed = (digitalRead(pttPin) == LOW);

  if (buttonPressed) {
    // If the button is pressed, and we aren't transmitting yet...
    if (!isTransmitting) { 
      Serial.println("-> Transmitting Audio...");
      rfAudio.transmit();    // Turn on mic transmission
      isTransmitting = true; // Update state
    }
  } else {
    // If the button is released, and we are currently transmitting...
    if (isTransmitting) { 
      Serial.println("<- Transmission ended. Returning to Receive mode.");
      rfAudio.receive();      // Return to listening mode
      isTransmitting = false; // Update state
    }
  }
  
  // Note: Avoid placing any delay() inside this loop, as it will disrupt
  // the continuous real-time audio sampling and stream transmission.
}