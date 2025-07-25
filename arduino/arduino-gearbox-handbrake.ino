#include <Joystick.h>

// Pin assignments for buttons and magnet sensor
const int buttonPins[8] = {2, 3, 4, 5, 6, 7, 8, 9};
const int magnetSensorPin = A2;

void setup() {
  // Initialize Joystick library
  Joystick.begin();
  

  // Setup buttons with pull-up resistors
  for (int i = 0; i < 8; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }

  // Setup magnet sensor pin (analog read)
  pinMode(magnetSensorPin, INPUT);
}

void loop() {
  // Read button states and update Joystick buttons
  for (int i = 0; i < 8; i++) {
    // Button state is LOW when pressed (because of pull-up)
    bool buttonPressed = (digitalRead(buttonPins[i]) == LOW);
    Joystick.setButton(i, buttonPressed);
  }
  
  // Read magnet sensor and map its value to Joystick X-axis
  int magnetValue = analogRead(magnetSensorPin);
  //Serial.print("Magnet sensor reading: ");
  //Serial.println(magnetValue);
  // Map the reading from 850 to 520 (for 0% to 100% mapping)
  int mappedValue = map(magnetValue, 650, 520, 0, 125);
  
  // Ensure the value stays within 0 to 255
  mappedValue = constrain(mappedValue, -125, 125);
  
  // Set the X axis of the Joystick
  Joystick.setYAxis(mappedValue);
  // Serial.println(magnetValue);

  delay(20);  // Small delay to debounce and smooth readings
}
