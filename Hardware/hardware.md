# Hardware

## Overview

The Plant Emotion Translator is an ESP32-based embedded system that monitors environmental parameters affecting plant health. Based on sensor readings, the system evaluates the plant's condition and displays an intuitive emotional expression on a 128×64 OLED display.

---

## Components Used

| Component | Quantity | Description |
|-----------|---------:|-------------|
| ESP32 Development Board | 1 | Main Controller |
| MQ135 Gas Sensor | 1 | Air Quality Monitoring |
| Soil Moisture Sensor | 1 | Soil Moisture Measurement |
| LM35 Temperature Sensor | 1 | Analog Temperature Measurement |
| DS18B20 Temperature Sensor | 1 | Digital Temperature Measurement |
| LDR | 1 | Ambient Light Detection |
| SSD1306 OLED Display (128×64) | 1 | Emotion Display |
| Breadboard | 1 | Circuit Assembly |
| Jumper Wires | As Required | Electrical Connections |
| USB Cable | 1 | Programming & Power |

---

## Pin Configuration

| ESP32 Pin | Component |
|-----------|-----------|
| GPIO 34 | MQ135 |
| GPIO 35 | Soil Moisture Sensor |
| GPIO 32 | LM35 |
| GPIO 33 | LDR |
| GPIO 4 | DS18B20 |
| GPIO 21 | OLED SDA |
| GPIO 22 | OLED SCL |
| 3.3V | Sensor Power |
| GND | Common Ground |

---

## Sensor Functions

| Sensor | Function |
|---------|----------|
| MQ135 | Detects air quality |
| Soil Moisture Sensor | Measures soil moisture level |
| LM35 | Measures ambient temperature |
| DS18B20 | Measures digital temperature |
| LDR | Measures surrounding light intensity |
| SSD1306 OLED | Displays plant emotion and status |

---

## Plant States

| Plant State | Trigger |
|-------------|---------|
| Healthy | All sensor values within threshold |
| Thirsty | Soil Moisture < 30% |
| Overwatered | Soil Moisture > 80% |
| Low Light Stress | LDR value below threshold |
| Heat Stress | Temperature > 32°C |
| Poor Air Quality | MQ135 value > 700 |

---

## Power Supply

- USB Powered (5V)
- ESP32 onboard regulator supplies 3.3V to sensors

---

## Working Principle

1. ESP32 reads all sensor values.
2. Sensor readings are processed using predefined threshold values.
3. The current plant condition is determined.
4. A corresponding facial expression is drawn on the OLED display.
5. The process repeats every 3 seconds.
