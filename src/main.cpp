#include <Arduino.h>

// Define the relay pins
const int relayPins[] = {5, 6, 7, 8};

// Define the firmware version
const char* firmwareVersion = "0.0.1";

void setup() {
  // Initialize the serial communication
  Serial.begin(115200);

  // Initialize the relay pins as outputs
  for (int i = 0; i < 4; i++) {
    pinMode(relayPins[i], OUTPUT);
    digitalWrite(relayPins[i], LOW);
  }
}

void loop() {
  // Check if there is incoming serial data
  if (Serial.available() > 0) {
    // Read the incoming serial data
    String command = Serial.readStringUntil('\n');

    // Parse the command
    if (command.startsWith("relay")) {
      // Extract the relay number and command type
      int relayNumber = command.substring(6, 7).toInt();
      String commandType = command.substring(8);

      // Check if the relay number is valid
      if (relayNumber >= 1 && relayNumber <= 4) {
        // Check the command type
        if (commandType.equals("on")) {
          // Turn the relay on
          digitalWrite(relayPins[relayNumber - 1], HIGH);
          Serial.println("ok");
        } else if (commandType.equals("off")) {
          // Turn the relay off
          digitalWrite(relayPins[relayNumber - 1], LOW);
          Serial.println("ok");
        } else {
          Serial.println("invalid command");
        }
      } else {
        Serial.println("invalid command");
      }
    } else if (command.equals("version")) {
      // Respond with the firmware version
      Serial.println(firmwareVersion);
    } else {
      Serial.println("invalid command");
    }
  }
}
