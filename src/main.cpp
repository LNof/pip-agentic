#include <Arduino.h>

// Define the relay pins
const int relayPins[] = {5, 6, 7, 8};

// Define the firmware version
const char* firmwareVersion = "v1.0.0";

void setup() {
  // Initialize the serial communication at 57600 baud
  Serial.begin(57600);

  // Initialize the relay pins as outputs
  for (int i = 0; i < 4; i++) {
    pinMode(relayPins[i], OUTPUT);
  }
}

void loop() {
  // Check if there is incoming serial data
  if (Serial.available() > 0) {
    // Read the incoming command
    String command = Serial.readStringUntil('\n');

    // Parse the command
    if (command.startsWith("relay")) {
      // Extract the relay number and state
      int relayNumber = command.substring(6, 7).toInt();
      String state = command.substring(8);

      // Check if the relay number is valid
      if (relayNumber >= 1 && relayNumber <= 4) {
        // Check if the state is "on" or "off"
        if (state == "on") {
          // Turn on the relay
          digitalWrite(relayPins[relayNumber - 1], HIGH);
          Serial.println("Relay " + String(relayNumber) + " turned on");
        } else if (state == "off") {
          // Turn off the relay
          digitalWrite(relayPins[relayNumber - 1], LOW);
          Serial.println("Relay " + String(relayNumber) + " turned off");
        } else {
          Serial.println("Invalid command");
        }
      } else {
        Serial.println("Invalid command");
      }
    } else if (command == "firmware") {
      // Return the firmware version
      Serial.println(firmwareVersion);
    } else {
      Serial.println("Invalid command");
    }
  }
}