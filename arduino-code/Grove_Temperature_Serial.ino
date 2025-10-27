/*
  File: Grove_Temperature_Serial.ino

  More info on this sensor can be found on the Seeed Studio Wiki:
  https://wiki.seeedstudio.com/Grove-Temperature_Sensor_V1.2/

  Description:
    - Connect sensor to port A0
    - Read data from Grove temperature sensor.
    - Convert raw data to temperature using Steinhart–Hart thermistor equation.
    - Output readings to USB serial.

    - Outputs calculated temperature in °C
*/

#include <math.h>

#define TEMP_PIN A0

const int B = 4275000;  // B value of the thermistor
const int R0 = 100000;  // R0 = 100k

void setup() {
  // Initialise serial communication
  Serial.begin(9600);
  Serial.println("Grove Temperature sensor");
}

void loop() {
  // 1. Get raw data from temperature sensor
  int a = analogRead(TEMP_PIN);

  // 2. Calculate actual resistance of the thermistor (in ohms)
  float R = 1023.0 / a - 1.0;
  R = R0 * R;

  // 3. Convert resistance to temperature (in °C)
  // This uses uses Steinhart–Hart thermistor equation to calculate temperature from resistance
  float temperature = 1.0 / (log(R / R0) / B + 1 / 298.15) - 273.15;

  // 4. Output temperature to USB serial
  Serial.println("temperature " + String(temperature));
}