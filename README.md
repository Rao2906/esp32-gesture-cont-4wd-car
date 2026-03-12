
# Gesture Controlled Car 🚗

A wireless gesture-controlled robotic car built using ESP32, Arduino UNO, MPU6050, and NRF24L01.

## Hardware Used
- ESP32 (Transmitter)
- Arduino UNO (Receiver)
- MPU6050 Accelerometer + Gyroscope
- NRF24L01 RF Module (2 units)
- L298N Motor Driver
- DC Motors
- Battery Pack
- Chassis with wheels

---

# Working Principle

1. MPU6050 detects hand tilt.
2. ESP32 reads accelerometer data.
3. ESP32 sends command using NRF24L01.
4. Arduino UNO receives the signal.
5. Arduino controls L298N motor driver.
6. Motors move according to the gesture.

---

# Circuit Connections

## Transmitter (ESP32 + MPU6050 + NRF24L01)

### MPU6050 → ESP32

| MPU6050 | ESP32 |
|--------|------|
| VCC | 3.3V |
| GND | GND |
| SDA | GPIO21 |
| SCL | GPIO22 |

### NRF24L01 → ESP32

| NRF24L01 | ESP32 |
|---------|------|
| VCC | 3.3V |
| GND | GND |
| CE | GPIO4 |
| CSN | GPIO5 |
| SCK | GPIO18 |
| MOSI | GPIO23 |
| MISO | GPIO19 |

---

## Receiver (Arduino UNO + NRF24L01 + L298N)

### NRF24L01 → Arduino

| NRF24L01 | Arduino UNO |
|---------|-------------|
| VCC | 3.3V |
| GND | GND |
| CE | 9 |
| CSN | 10 |
| SCK | 13 |
| MOSI | 11 |
| MISO | 12 |

### L298N → Arduino

| L298N | Arduino |
|------|--------|
| IN1 | 3 |
| IN2 | 4 |
| IN3 | 5 |
| IN4 | 6 |

Motor outputs connect to the DC motors.

---

# Precautions While Building ⚠️

1. **NRF24L01 requires stable 3.3V**
   - Do NOT connect it to 5V.
   - Use a capacitor (10µF) across VCC and GND.

2. **Common Ground**
   - All modules must share the same GND.

3. **Motor Power Supply**
   - Motors should be powered from battery through L298N.
   - Do not power motors from Arduino directly.

4. **Loose Connections**
   - Ensure tight jumper connections.
   - Breadboard loose connections cause communication errors.

5. **Check SPI Pins Carefully**
   - Wrong SPI pins will stop NRF24 communication.

---

# Common Problems and Solutions

## Problem: Car not moving

Possible causes:
- Wrong L298N wiring
- Motors not powered
- Wrong Arduino pins

Solution:
- Recheck IN1, IN2, IN3, IN4 connections.

---

## Problem: NRF24L01 not communicating

Possible causes:
- Insufficient power
- Loose SPI wires

Solution:
- Add capacitor across VCC and GND.
- Recheck CE and CSN pins.

---

## Problem: Random movement

Possible causes:
- MPU6050 noise
- Unstable hand position

Solution:
- Adjust threshold values in code.

---

# Future Improvements

- PWM speed control
- PID steering control
- Camera module
- Mobile app control
- Longer range RF module

---

# Author

Embedded Systems Project by an Electronics & Communication Engineering student (Rao2906).
