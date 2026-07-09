#include <OneWire.h>
#include <DallasTemperature.h>
#include <U8g2lib.h>
#include <Wire.h>

// ---------------- Pin Definitions ----------------
#define MQ135_PIN 34          // Air quality
#define MOISTURE_PIN 35       // Soil moisture
#define LM35_PIN 32           // Temperature sensor
#define LDR_PIN 33            // Light sensor
#define DS18B20_PIN 4         // Temperature sensor

// ---------------- OLED ----------------
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

// ---------------- Objects ----------------
OneWire oneWire(DS18B20_PIN);
DallasTemperature tempSensor(&oneWire);

// ---------------- Variables (made global so all funcs can use them) ----------------
int mq135Value = 0;
int moistureValue = 0;
int lm35Value = 0;
int ldrValue = 0;
unsigned long lastUpdate = 0;
const int interval = 3000; // 3 seconds
int statusIndex = 0;

// Values derived from ADC (made global)
int moisturePercent = 0;
float lm35Temperature = 0.0;

// ---------------------- PLANT STATUS EMOJIS ----------------------

void drawHealthy() {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_6x12_tr);
  u8g2.drawStr(30,10,"Healthy");
  u8g2.drawDisc(50,30,3);
  u8g2.drawDisc(78,30,3);
  u8g2.drawArc(65,42,10,130,260);
  u8g2.sendBuffer();
}

void drawThirsty() {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_6x12_tr);
  u8g2.drawStr(30,10,"Thirsty");
  u8g2.drawDisc(50,30,3);
  u8g2.drawDisc(78,30,3);
  u8g2.drawArc(65,52,10,260,130);
  u8g2.sendBuffer();
}

void drawOverwatered() {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_6x12_tr);
  u8g2.drawStr(15,10,"Overwatered");
  u8g2.drawCircle(50,30,3);
  u8g2.drawCircle(78,30,3);
  u8g2.drawLine(55,45,75,45);
  u8g2.drawLine(45,33,45,45);
  u8g2.drawLine(78,33,78,45);
  u8g2.sendBuffer();
}

void drawLowLightStress() {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_6x12_tr);
  u8g2.drawStr(10,10,"LowLightStress");
  u8g2.drawDisc(50,30,3);
  u8g2.drawDisc(78,30,3);
  u8g2.drawLine(55,45,75,45);
  // Sun symbol
  u8g2.drawCircle(65,50,6);
  u8g2.drawLine(65,43,65,37);
  u8g2.drawLine(65,57,65,63);
  u8g2.drawLine(59,50,53,50);
  u8g2.drawLine(71,50,77,50);
  u8g2.sendBuffer();
}

void drawHeatStress() {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_6x12_tr);
  u8g2.drawStr(25,10,"HeatStress");
  u8g2.drawLine(45,23,55,27);
  u8g2.drawLine(85,23,75,27);
  u8g2.drawDisc(52,32,3);
  u8g2.drawDisc(78,32,3);
  u8g2.drawLine(55,50,75,50);
  u8g2.drawLine(65,42,65,55);
  u8g2.sendBuffer();
}

void drawPoorAirQuality() {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_6x12_tr);
  u8g2.drawStr(5,10,"PoorAirQuality");
  u8g2.drawCircle(50,30,3);
  u8g2.drawCircle(78,30,3);
  u8g2.drawArc(65,52,10,260,130);
  u8g2.drawBox(55,35,20,8);
  u8g2.sendBuffer();
}

// ---------------------- STATUS DECISION ----------------------
void updatePlantStatus() {
  // thresholds (adjustable)
  bool thirsty = (moisturePercent < 30);      // <30% -> thirsty
  bool overwatered = (moisturePercent > 80);  // >80% -> overwatered
  bool lowLight = (ldrValue < 500);           // low light sensor reading
  bool heatStress = (lm35Temperature > 32.0); // degrees Celsius
  bool poorAir = (mq135Value > 700);          // MQ135 threshold (raw ADC)

  if (thirsty) {
    Serial.println("STATUS: Thirsty");
    drawThirsty();
  }
  else if (overwatered) {
    Serial.println("STATUS: Overwatered");
    drawOverwatered();
  }
  else if (lowLight) {
    Serial.println("STATUS: LowLightStress");
    drawLowLightStress();
  }
  else if (heatStress) {
    Serial.println("STATUS: HeatStress");
    drawHeatStress();
  }
  else if (poorAir) {
    Serial.println("STATUS: PoorAirQuality");
    drawPoorAirQuality();
  }
  else {
    Serial.println("STATUS: Healthy");
    drawHealthy();
  }
}

// ---------------------- SETUP ----------------------
void setup() {
  Serial.begin(115200);
  Serial.println("\nInitializing Sensors...");
  tempSensor.begin();
  delay(2000);

  u8g2.begin();
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_6x12_tr);
  u8g2.drawStr(0, 10, "ESP32 Multi-Sensor");
  u8g2.drawStr(0, 25, "System Starting...");
  u8g2.sendBuffer();
  delay(2000);
  Serial.println("ESP32 Multi-Sensor System Started");
}

// ---------------------- MAIN LOOP ----------------------
void loop() {
  mq135Value = analogRead(MQ135_PIN);
  moistureValue = analogRead(MOISTURE_PIN);

  lm35Value = analogRead(LM35_PIN);
  float voltage = (lm35Value / 4095.0) * 3.3;
  lm35Temperature = (voltage * 100.0) + 11.0; // global updated

  ldrValue = analogRead(LDR_PIN);

  tempSensor.requestTemperatures();
  float dsTemperature = tempSensor.getTempCByIndex(0);

  // update global moisturePercent (adjust ADC mapping to your sensor)
  moisturePercent = map(moistureValue, 4095, 1500, 0, 100);
  moisturePercent = constrain(moisturePercent, 0, 100);

  Serial.println("\n----- SENSOR DATA -----");
  Serial.printf("MQ135 Value: %d\n", mq135Value);
  Serial.printf("Soil Moisture (%%): %d\n", moisturePercent);
  Serial.printf("LM35 Temp: %.2f °C\n", lm35Temperature);
  Serial.printf("LDR Value: %d\n", ldrValue);
  Serial.printf("DS18B20 Temp: %s\n",
                (dsTemperature == DEVICE_DISCONNECTED_C ? "ERROR" : String(dsTemperature).c_str()));

  if (millis() - lastUpdate >= interval) {
    lastUpdate = millis();
    updatePlantStatus();
  }

  delay(3000);
}
