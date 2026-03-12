#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define IN1 4
#define IN2 5
#define IN3 9
#define IN4 10
#define ENA 6  // PWM
#define ENB 3  // PWM

RF24 radio(7, 8);  // CE, CSN
const byte address[] = "00001";
char packet[2];

void setup() {
  Serial.begin(9600);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  radio.begin();
  radio.setPALevel(RF24_PA_LOW);
  radio.setDataRate(RF24_250KBPS);
  radio.openReadingPipe(0, address);
  radio.startListening();

  Serial.println("📱 Receiver ready with PWM control");
}

void loop() {
  if (radio.available()) {
    radio.read(&packet, sizeof(packet));
    char command = packet[0];
    int speedMode = packet[1] - '0';

    // 🔧 Fix: use minimum safe PWM value for Mode 1
    int pwm = 0;
    if (speedMode == 1) pwm = 100;
    else if (speedMode == 2) pwm = 170;
    else if (speedMode == 3) pwm = 255;

    Serial.print("📥 Received: ");
    Serial.print(command);
    Serial.print(" | Mode: ");
    Serial.print(speedMode);
    Serial.print(" | PWM: ");
    Serial.println(pwm);

    switch (command) {
      case 'F': forward(pwm); break;
      case 'B': backward(pwm); break;
      case 'L': left(pwm); break;
      case 'R': right(pwm); break;
      default: stop(); break;
    }
  }
}

void forward(int pwm) {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  analogWrite(ENA, pwm); analogWrite(ENB, pwm);
}

void backward(int pwm) {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
  analogWrite(ENA, pwm); analogWrite(ENB, pwm);
}

void left(int pwm) {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  analogWrite(ENA, pwm); analogWrite(ENB, pwm);
}

void right(int pwm) {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
  analogWrite(ENA, pwm); analogWrite(ENB, pwm);
}

void stop() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
  analogWrite(ENA, 0); analogWrite(ENB, 0);
}
