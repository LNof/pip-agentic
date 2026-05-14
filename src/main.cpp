#include <Arduino.h>

// Define relay pins
const int relayPins[] = {5, 6, 7, 8};

// Define firmware version
const String firmwareVersion = "0.0.1";

void setup() {
  // Initialize serial communication
  Serial.begin(115200);

  // Initialize relay pins as outputs
  for (int i = 0; i < 4; i++) {
    pinMode(relayPins[i], OUTPUT);
    digitalWrite(relayPins[i], LOW);
  }
}

void loop() {
  // Check for incoming serial commands
  if (Serial.available() > 0) {
    // Read incoming command
    String command = Serial.readStringUntil('\n');
    command.trim();
    // Parse command
    if (command.startsWith("relay")) {
      // Extract relay number and action
      int spaceIndex1 = command.indexOf(' ');
      int spaceIndex2 = command.indexOf(' ', spaceIndex1 + 1);
      String relayNumberStr = command.substring(spaceIndex1 + 1, spaceIndex2);
      int relayNumber = relayNumberStr.toInt();
      String action = command.substring(spaceIndex2 + 1);
      // Validate relay number
      if (relayNumber >= 1 && relayNumber <= 4) {
        // Perform action
        if (action == "on") {
          digitalWrite(relayPins[relayNumber - 1], HIGH);
          Serial.println("ok");
        } else if (action == "off") {
          digitalWrite(relayPins[relayNumber - 1], LOW);
          Serial.println("ok");
        } else {
          Serial.println("invalid command");
        }
      } else {
        Serial.println("invalid command");
      }
    } else if (command == "version") {
      // Respond with firmware version
      Serial.println(firmwareVersion);
    } else {
      Serial.println("invalid command");
    }
  }
}
