
# Gesture Controlled Car 🚗

Gesture Controlled Robotic Car built using ESP32, Arduino UNO, MPU6050 and NRF24L01 wireless communication.

This project demonstrates embedded systems integration, sensor interfacing, wireless communication, motor control, and battery management.

---

# 🧰 Hardware Used

- ESP32 (Transmitter)
- Arduino UNO (Receiver)
- MPU6050 Accelerometer & Gyroscope
- NRF24L01 RF Modules (2)
- L298N Motor Driver
- DC Motors
- Robotic Car Chassis
- 18650 Lithium‑ion Cells
- TP4056 Battery Charging Module

---

# ⚙️ Working Principle

1. MPU6050 detects the tilt of the hand.
2. ESP32 reads the sensor data and converts it into commands.
3. Commands are transmitted wirelessly using NRF24L01 RF modules.
4. Arduino UNO receives the commands.
5. Arduino drives the motors using the L298N motor driver.
6. The car moves forward, backward, left, or right depending on the hand gesture.

---

# 🔌 Circuit Connections

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

| NRF24L01 | Arduino |
|---------|--------|
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

# 🔋 Power Management

This system uses rechargeable 18650 Li‑ion batteries to power the robotic car.

## Components

- 18650 Lithium‑ion Cells
- TP4056 Li‑ion Charging Module

## TP4056 Connections

| TP4056 Pin | Connection |
|-----------|-----------|
| B+ | Battery Positive |
| B- | Battery Negative |
| OUT+ | System Power Output |
| OUT- | System Ground |

The TP4056 module provides:
- Over‑charge protection
- Over‑discharge protection
- Safe Li‑ion charging
- USB charging capability

---

# ⚠️ Precautions While Building

1. NRF24L01 requires stable 3.3V power
   - Never connect it to 5V
   - Add a 10µF capacitor across VCC and GND

2. Common Ground
   - Ensure ESP32, Arduino, motor driver, and RF module share the same ground

3. Motor Power
   - Motors should be powered from battery through L298N
   - Do not power motors directly from Arduino

4. Secure Connections
   - Loose jumper wires can cause communication errors

5. Battery Safety
   - Do not short circuit 18650 cells
   - Ensure correct polarity when connecting batteries

---

# 🛠 Common Problems and Solutions

## Car Not Moving

Possible causes:
- Wrong L298N wiring
- Motors not powered
- Wrong pin configuration

Solution:
- Verify IN1, IN2, IN3, IN4 connections

---

## NRF24L01 Not Communicating

Possible causes:
- Insufficient power supply
- Incorrect SPI wiring

Solution:
- Add capacitor across VCC and GND
- Recheck CE and CSN connections

---

## Random Movements

Possible causes:
- Sensor noise
- Hand instability

Solution:
- Adjust threshold values in the code

---

# 🚀 Future Improvements

- PWM speed control
- PID based steering
- Camera module for FPV
- Mobile app control
- Longer range RF module

---

# 👨‍💻 Author

Embedded Systems Project by an Electronics & Communication Engineering student.
