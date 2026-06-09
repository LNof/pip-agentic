#include <Arduino.h>

// Define the relay pins
const int relayPins[] = {5, 6, 7, 8};

// Define the firmware version
const char* firmwareVersion = "v1.0.0";

// Function to get the relay number from the command
int getRelayNumber(String command) {
  int relayNumber = -1;
  if (command.indexOf("relay 1") != -1) relayNumber = 0;
  if (command.indexOf("relay 2") != -1) relayNumber = 1;
  if (command.indexOf("relay 3") != -1) relayNumber = 2;
  if (command.indexOf("relay 4") != -1) relayNumber = 3;
  return relayNumber;
}

// Function to process the command
void processCommand(String command) {
  if (command.startsWith("relay")) {
    int relayNumber = getRelayNumber(command);
    if (relayNumber >= 0 && relayNumber <= 3) {
      if (command.indexOf("on") != -1) {
        digitalWrite(relayPins[relayNumber], HIGH);
        Serial.println("Relay " + String(relayNumber + 1) + " turned on");
      } else if (command.indexOf("off") != -1) {
        digitalWrite(relayPins[relayNumber], LOW);
        Serial.println("Relay " + String(relayNumber + 1) + " turned off");
      }
    } else if (command.indexOf("all") != -1) {
      if (command.indexOf("on") != -1) {
        for (int i = 0; i < 4; i++) {
          digitalWrite(relayPins[i], HIGH);
        }
        Serial.println("All relays turned on");
      } else if (command.indexOf("off") != -1) {
        for (int i = 0; i < 4; i++) {
          digitalWrite(relayPins[i], LOW);
        }
        Serial.println("All relays turned off");
      }
    }
  } else if (command == "firmware") {
    Serial.println(firmwareVersion);
  } else {
    Serial.println("Invalid command");
  }
}

void setup() {
  Serial.begin(57600);
  // Initialize the relay pins as outputs
  for (int i = 0; i < 4; i++) {
    pinMode(relayPins[i], OUTPUT);
  }
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    processCommand(command);
  }
}