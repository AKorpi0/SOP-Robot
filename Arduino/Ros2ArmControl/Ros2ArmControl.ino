#include <Servo.h>
#include <Arduino.h>

const int NUM_SERVOS = 8;
const int SERVO_PINS[NUM_SERVOS] = {6, 7, 8, 9, 10, 11, 12, 13};

Servo servos[NUM_SERVOS];

void setup() {
  Serial.begin(115200);

  // Attach servos to pins
  for (int i = 0; i < NUM_SERVOS; ++i) {
    servos[i].attach(SERVO_PINS[i]);
  }
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');

    // Split the received command by commas
    int angles[NUM_SERVOS];
    int angleIndex = 0;
    int start = 0;
    int end = command.indexOf(',');

    while (end != -1) {
      angles[angleIndex++] = command.substring(start, end).toInt();
      start = end + 1;
      end = command.indexOf(',', start);
    }
    angles[angleIndex] = command.substring(start).toInt();

    // Set angles for each servo
    for (int i = 0; i < NUM_SERVOS; ++i) {
      servos[i].write(angles[i]);
    }

    // Send back the received angles
    Serial.print("Received angles: ");
    for (int i = 0; i < NUM_SERVOS; ++i) {
      Serial.print(angles[i]);
      if (i < NUM_SERVOS - 1) {
        Serial.print(",");
      }
    }
    Serial.println();
  }
}
