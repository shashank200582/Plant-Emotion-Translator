<div align="center">

# Plant Emotion Translator

### An Embedded System for Interpreting Plant Health Using Environmental Sensors

![Status](https://img.shields.io/badge/Status-Completed-success)
![Platform](https://img.shields.io/badge/Controller-ESP32-blue)
![Language](https://img.shields.io/badge/Language-C++-00599C)
![Display](https://img.shields.io/badge/Display-OLED-green)
![License](https://img.shields.io/badge/License-MIT-yellow)

</div>

---

# Overview

Plant Emotion Translator is an embedded system designed to monitor environmental conditions affecting plant health and translate sensor data into intuitive plant "emotions."

Instead of displaying raw sensor values alone, the system evaluates soil moisture, air quality, ambient light, and temperature to determine the plant's condition and presents a graphical expression on an OLED display, making plant monitoring more interactive and user-friendly.

---

# Features

* Real-Time Soil Moisture Monitoring
* Air Quality Monitoring using MQ135
* Ambient Light Monitoring
* Temperature Monitoring using LM35
* DS18B20 Digital Temperature Monitoring
* OLED-Based Plant Emotion Display
* Rule-Based Plant Health Interpretation

---

# Plant States

| Condition          | Displayed Emotion |
| ------------------ | ----------------- |
| Healthy            | Healthy           |
| Low Soil Moisture  | Thirsty           |
| High Soil Moisture | Overwatered       |
| Low Light          | Low Light Stress  |
| High Temperature   | Heat Stress       |
| Poor Air Quality   | Poor Air Quality  |

---

# Hardware Components

| Component            | Description                 |
| -------------------- | --------------------------- |
| ESP32                | Main Controller             |
| MQ135                | Air Quality Sensor          |
| Soil Moisture Sensor | Soil Moisture Measurement   |
| LM35                 | Analog Temperature Sensor   |
| DS18B20              | Digital Temperature Sensor  |
| LDR                  | Ambient Light Sensor        |
| SSD1306 OLED Display | Plant Emotion Visualization |

---

# Software Stack

| Category                | Technology        |
| ----------------------- | ----------------- |
| Programming Language    | C++               |
| Development Environment | Arduino IDE       |
| Controller              | ESP32             |
| Graphics Library        | U8g2              |
| Temperature Library     | DallasTemperature |
| OneWire Communication   | OneWire Library   |

---

# Working Principle

1. Environmental sensors continuously monitor the plant's surroundings.
2. Sensor readings are acquired by the ESP32.
3. Threshold-based logic evaluates the plant's condition.
4. The corresponding plant emotion is selected.
5. An expressive face representing the detected condition is displayed on the OLED.

---

# Repository Structure

```text
Plant-Emotion-Translator
│
├── Firmware
├── Hardware
├── Images
├── Videos
├── README.md
└── LICENSE
```

---

# Current Plant Conditions Supported

| Parameter          |   Status  |
| ------------------ | :-------: |
| Soil Moisture      | Supported |
| Air Quality        | Supported |
| Temperature        | Supported |
| Ambient Light      | Supported |
| OLED Visualization | Supported |

---

# Future Improvements

* Mobile Application Integration
* IoT-Based Remote Monitoring
* Automatic Irrigation Control
* Cloud Data Logging
* Machine Learning-Based Plant Health Prediction

---

# Gallery

Project images, hardware setup, OLED outputs, and demonstration videos are available in the Images and Videos directories.

---

# Author

**Shashank H**

Electronics and Telecommunication Engineering

Siddaganga Institute of Technology

---

# License

This project is licensed under the MIT License.

