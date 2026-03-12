#include <Wire.h>
#include <MPU6050.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN 5
#define CSN_PIN 17
#define LED_PIN 2
#define MODE_BUTTON 0

RF24 radio(CE_PIN, CSN_PIN);
const byte address[] = "00001";
MPU6050 mpu(0x68, &Wire);

int16_t ax0 = 0, ay0 = 0;
const int gestureThreshold = 3000;
int speedMode = 1;  // 1 = slow, 2 = medium, 3 = fast
unsigned long lastButtonPress = 0;

void calibrate() {
  Serial.println("Calibrating...");
  digitalWrite(LED_PIN, HIGH);
  int16_t ax, ay, az;
  ax0 = 0; ay0 = 0;
  for (int i = 0; i < 100; i++) {
    mpu.getAcceleration(&ax, &ay, &az);
    ax0 += ax;
    ay0 += ay;
    delay(5);
  }
  ax0 /= 100;
  ay0 /= 100;
  digitalWrite(LED_PIN, LOW);
  Serial.print("Offsets: ax0 = ");
  Serial.print(ax0);
  Serial.print(", ay0 = ");
  Serial.println(ay0);
}

void setup() {
  Serial.begin(115200);
  Wire.begin(22, 21);
  mpu.initialize();

  pinMode(LED_PIN, OUTPUT);
  pinMode(MODE_BUTTON, INPUT_PULLUP);

  if (!radio.begin()) {
    Serial.println("NRF24L01 not detected!");
    while (1);
  }

  radio.setPALevel(RF24_PA_LOW);
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(address);
  radio.stopListening();

  calibrate();
  Serial.println("ESP32 ready with mode-based speed control");
}

void loop() {
  // Check for button press to change mode
  if (digitalRead(MODE_BUTTON) == LOW && millis() - lastButtonPress > 1000) {
    speedMode++;
    if (speedMode > 3) speedMode = 1;
    Serial.print("Mode changed to: ");
    Serial.println(speedMode);
    lastButtonPress = millis();
  }

  int16_t ax, ay, az;
  mpu.getAcceleration(&ax, &ay, &az);
  int16_t dx = ax - ax0;
  int16_t dy = ay - ay0;

  char direction = 'S';

  if (dy > gestureThreshold)       direction = 'F';
  else if (dy < -gestureThreshold) direction = 'B';
  else if (dx > gestureThreshold)  direction = 'L';
  else if (dx < -gestureThreshold) direction = 'R';

  char packet[2] = { direction, (char)(speedMode + '0') };

  if (radio.write(&packet, sizeof(packet))) {
    Serial.print("Sent: ");
    Serial.print(direction);
    Serial.print(" | Mode: ");
    Serial.println(speedMode);
  } else {
    Serial.println("Send failed");
  }

  delay(200);
}
