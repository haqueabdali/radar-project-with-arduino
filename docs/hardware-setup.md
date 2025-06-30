# IoT Radar - Hardware Setup Guide

## Components Required
1. ESP32 Development Board
2. HC-SR04 Ultrasonic Sensor
3. 28BYJ-48 Stepper Motor + ULN2003 Driver Board
4. Jumper Wires
5. 5V Power Supply (2A+ recommended)

## Wiring Diagram
ESP32	Component
5V	ULN2003 VCC
text
        | HC-SR04 VCC

GND | ULN2003 GND
| HC-SR04 GND
GPIO 12 (IN1) | ULN2003 IN1
GPIO 14 (IN2) | ULN2003 IN2
GPIO 13 (IN3) | ULN2003 IN3
GPIO 15 (IN4) | ULN2003 IN4
GPIO 5 (TRIG) | HC-SR04 Trig
GPIO 18 (ECHO)| HC-SR04 Echo


## Assembly Instructions

1. Mount the ultrasonic sensor on the stepper motor shaft using a 3D-printed bracket
2. Connect the ULN2003 driver to the ESP32 as specified above
3. Connect HC-SR04 to ESP32 and power lines
4. Provide stable 5V power to both motor driver and ESP32
5. Secure all components in an enclosure

## Calibration

1. Upload the firmware
2. Monitor serial output at 115200 baud
3. Adjust in code:
   - `STEPS_PER_REV`: Actual steps for full rotation
   - Motor speed/acceleration values
   - Measurement frequency

## Troubleshooting

| Issue                 | Solution                      |
|-----------------------|-------------------------------|
| Motor not rotating    | Check power supply connections|
| Inaccurate distance   | Ensure stable 5V to HC-SR04   |
| WiFi disconnects      | Add capacitor to power lines  |
| Jerky motor movement  | Reduce maxSpeed in code       |