/*
* Name: Line-Following Car
* Author: Wiktor Nordström
* Date: 2025-02-07
* Description: This project uses IR sensors to detect and follow a line on the ground. 
  The sensors send LOW or HIGH signals to the relay, which controls the motors.
*/

// Define relay control pins
const int relayLeft = 10;   // Relay for the left motor
const int relayRight = 9;   // Relay for the right motor

// Define IR sensor pins
const int sensorLeft = 4;   // Left IR sensor
const int sensorMiddle = 3; // Middle IR sensor
const int sensorRight = 2;  // Right IR sensor

void setup() {
  // Set relay pins as outputs
  pinMode(relayLeft, OUTPUT);
  pinMode(relayRight, OUTPUT);

  // Set IR sensor pins as inputs
  pinMode(sensorLeft, INPUT);
  pinMode(sensorMiddle, INPUT);
  pinMode(sensorRight, INPUT);

  // Start with motors OFF
  digitalWrite(relayLeft, LOW);
  digitalWrite(relayRight, LOW);

   // Initial delay to ignore first sensor readings
  delay(2000);
}

int readSensor(int pin) {
  int value = 0;
  for (int i = 0; i < 5; i++) {  // Take 5 readings and average
    value += digitalRead(pin);
    delay(2);  // Small delay to stabilize readings
  }
  return (value >= 3) ? HIGH : LOW; // Majority rule filtering
}

void loop() {
  // Read sensor values with filtering
  int leftSensor = readSensor(sensorLeft);
  int middleSensor = readSensor(sensorMiddle);
  int rightSensor = readSensor(sensorRight);

  if (middleSensor == LOW) {
    // Move forward when the middle sensor detects the line
    moveMotors(HIGH, HIGH);
  } else if (leftSensor == LOW && rightSensor == LOW) {
    // Stop if both side sensors detect the line
    moveMotors(LOW, LOW);
  } else if (leftSensor == LOW && middleSensor == HIGH && rightSensor == HIGH) {
    // Turn left by running the right motor only
    moveMotors(LOW, HIGH);
  } else if (rightSensor == LOW && middleSensor == HIGH && leftSensor == HIGH) {
    // Turn right by running the left motor only
    moveMotors(HIGH, LOW);
  } else if (rightSensor == LOW && leftSensor == LOW && middleSensor == HIGH){
    // Stop if both side sensors detects the line
    moveMotors(LOW, LOW);
  } else {
    // Stop if no sensor detects the line
    moveMotors(LOW, LOW);
  }
  
  delay(50);  // Small delay to prevent rapid motor switching
}

// Function to control motor states using relays
void moveMotors(int stateLeft, int stateRight) {
  digitalWrite(relayLeft, stateLeft);   // Control left motor relay
  digitalWrite(relayRight, stateRight); // Control right motor relay
}
