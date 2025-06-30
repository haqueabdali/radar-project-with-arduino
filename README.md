# IoT Radar System - Object Detection & Monitoring

[![PlatformIO CI](https://github.com/haqueabdali/radar-project-with-arduino/actions/workflows/pio.yml/badge.svg)](https://github.com/haqueabdali/radar-project-with-arduino/actions)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

![System Diagram]

An IoT-enabled radar system that detects objects, visualizes spatial data in real-time, and sends alerts. Built with ESP32, MQTT, and Grafana.

## Features

- 🌀 180° object detection with ultrasonic sensor
- 📶 Real-time data streaming via MQTT
- 📊 Grafana dashboard for visualization
- 🔔 Distance-based alerts
- 📶 WiFi signal strength monitoring
- 🔄 OTA update capability

## Hardware Requirements

- ESP32 Development Board
- HC-SR04 Ultrasonic Sensor
- 28BYJ-48 Stepper Motor + ULN2003 Driver
- 5V 2A Power Supply
- Jumper Wires

## Software Requirements

- PlatformIO (for firmware)
- Node-RED (for data processing)
- Docker (for database & visualization)
- MQTT Client (for testing)

## Getting Started

### 1. Hardware Setup
See [hardware setup guide](docs/hardware-setup.md)

### 2. Firmware Installation
1. Install [PlatformIO](https://platformio.org/)
2. Clone this repository
3. Update WiFi credentials in `firmware/src/main.cpp`
4. Flash to ESP32:
```bash
pio run --target upload
```

### 3. Data Pipeline Setup
1. Install [Docker](https://www.docker.com/)
2. Start services:
```bash
cd cloud
docker-compose up -d
```
3. Access services:
   - Grafana: http://localhost:3000 (admin/radar123)
   - InfluxDB: http://localhost:8086 (admin/pass123)

### 4. Node-RED Configuration
1. Install [Node-RED](https://nodered.org/):
```bash
npm install -g node-red
```
2. Import [cloud/node-red-flow.json](cloud/node-red-flow.json)
3. Start Node-RED:
```bash
node-red
```
## Dashboard Visualization
Access Grafana at `http://localhost:3000` and import the dashboard from [cloud/grafana-dashboard.json](cloud/grafana-dashboard.json)

![Dashboard Preview](docs/dashboard-preview.png)

## Project Structure
```
├── firmware/
│   ├── src/
│   │   └── main.cpp
│   └── platformio.ini
├── cloud/
│   ├── node-red-flows.json
│   └── docker-compose.yml
│   └── grafana-dashboard.json
├── docs/
│   ├── hardware-setup.md
│   └── architecture.png
└── README.md
```

## Contributing
1. Fork the repository
2. Create a new branch (`git checkout -b feature/your-feature`)
3. Commit your changes (`git commit -am 'Add feature'`)
4. Push to branch (`git push origin feature/your-feature`)
5. Create a Pull Request

## License
This project is licensed under the MIT License - see [LICENSE](LICENSE) for details.

## Acknowledgements
- Public MQTT Broker: [HiveMQ](https://www.hivemq.com/public-mqtt-broker/)
- Arduino Libraries: AccelStepper, PubSubClient
- Visualization: Grafana, InfluxDB