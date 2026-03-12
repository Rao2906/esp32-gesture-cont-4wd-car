
#include <Wire.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "MPU6050.h"

RF24 radio(4, 5);
const byte address[6] = "00001";

MPU6050 mpu;
int16_t ax, ay, az;

void setup() {
  Serial.begin(115200);
  Wire.begin();

  mpu.initialize();
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_LOW);
  radio.stopListening();
}

void loop() {
  mpu.getAcceleration(&ax, &ay, &az);

  char command = 'S';

  if (ax > 8000) command = 'F';
  else if (ax < -8000) command = 'B';
  else if (ay > 8000) command = 'L';
  else if (ay < -8000) command = 'R';
  else command = 'S';

  radio.write(&command, sizeof(command));
  delay(100);
}
