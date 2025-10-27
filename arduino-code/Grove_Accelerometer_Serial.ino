/*
  File: Grove_Accelerometer_Serial.ino
  
  More info on this sensor can be found on the Seeed Studio Wiki:
  https://wiki.seeedstudio.com/Grove-3-Axis-Digital-Accelerometer-LIS3DHTR/ 

  Description:
    - Connect sensor to I2C port.
    - Read data from Grove accelerometer.
    - Output readings to USB serial.
*/

#include <Wire.h>

// LIS3DHTR I2C address
#define LIS3DHTR_ADDR 0x19

// Register definitions
#define WHO_AM_I 0x0F
#define CTRL_REG1 0x20
#define CTRL_REG4 0x23
#define OUT_X_L 0x28

uint8_t buffer[6];

void setup() {
  // Initialise serial communication
  Serial.begin(9600);
  Serial.println("Grove Accelerometer");

  // Initialise I2C communication
  Wire.begin();

  // Initialise Accelerometer
  initAccelerometer();
}

void loop() {
  // 1. Read x, y, z data
  readMultiple(OUT_X_L, buffer, 6);

  int16_t x = (int16_t)(buffer[1] << 8 | buffer[0]);
  int16_t y = (int16_t)(buffer[3] << 8 | buffer[2]);
  int16_t z = (int16_t)(buffer[5] << 8 | buffer[4]);

  // 2. Adjust for sensitivity
  const float scale = 0.016;
  float xf = x * scale;
  float yf = y * scale;
  float zf = z * scale;

  // 3. Output to USB serial
  Serial.println("accelX " + String(xf));
  Serial.println("accelY " + String(yf));
  Serial.println("accelZ " + String(zf));
}

//========================================================
// Functions for reading sensor data
// Adapted from library found at:
// https://github.com/Seeed-Studio/Seeed_Arduino_LIS3DHTR

void initAccelerometer() {
  // Check device ID
  uint8_t id = readRegister(WHO_AM_I);
  Serial.print("LIS3DHTR WHO_AM_I = 0x");
  Serial.println(id, HEX);
  if (id != 0x33) {
    Serial.println("Device not found. Check wiring!");
    while (1)
      ;
  }

  // Enable all axes, normal mode, 100Hz output
  writeRegister(CTRL_REG1, 0b01000111);  // ODR=100Hz, X/Y/Z enabled
  delay(10);
  writeRegister(CTRL_REG4, 0b00000000);
  delay(10);
}

void writeRegister(uint8_t reg, uint8_t value) {
  Wire.beginTransmission(LIS3DHTR_ADDR);
  Wire.write(reg);
  Wire.write(value);
  Wire.endTransmission();
}

uint8_t readRegister(uint8_t reg) {
  Wire.beginTransmission(LIS3DHTR_ADDR);
  Wire.write(reg);
  Wire.endTransmission(false);
  Wire.requestFrom(LIS3DHTR_ADDR, (uint8_t)1);
  return Wire.read();
}

void readMultiple(uint8_t reg, uint8_t *buffer, uint8_t len) {
  Wire.beginTransmission(LIS3DHTR_ADDR);
  Wire.write(reg | 0x80);  // Enable auto-increment
  Wire.endTransmission(false);
  Wire.requestFrom(LIS3DHTR_ADDR, len);
  for (uint8_t i = 0; i < len; i++) {
    buffer[i] = Wire.read();
  }
}
