// Define motor control pins
// Define relay control pins
const int relayLeft = 10;   // Relay for the left motor
const int relayRight = 9;   // Relay for the right motor

// Define IR sensor pins
const int sensorLeft = 2;   // Left IR sensor
const int sensorMiddle = 3; // Middle IR sensor
const int sensorRight = 4;  // Right IR sensor

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
}

void loop() {
  // Read sensor values (LOW = black line detected)
  int leftSensor = digitalRead(sensorLeft);
  int middleSensor = digitalRead(sensorMiddle);
  int rightSensor = digitalRead(sensorRight);

  if (middleSensor == LOW) {
    // Move forward when the middle sensor detects the line
    moveMotors(HIGH, HIGH);
  } else if (leftSensor == LOW) {
    // Turn left by running the right motor only
    moveMotors(LOW, HIGH);
  } else if (rightSensor == LOW) {
    // Turn right by running the left motor only
    moveMotors(HIGH, LOW);
  } else {
    // Stop if no sensor detects the line
    moveMotors(LOW, LOW);
  }
}

// Function to control motor states using relays
void moveMotors(int stateLeft, int stateRight) {
  digitalWrite(relayLeft, stateLeft);   // Control left motor relay
  digitalWrite(relayRight, stateRight); // Control right motor relay
}
