/*
  File: Grove_AirQuality_Serial.ino
  
  More info on this sensor can be found on the Seeed Studio Wiki:
  https://wiki.seeedstudio.com/Grove-Air_Quality_Sensor_v1.3/

  Description:
    - Connect sensor to port A0.
    - Read data from Grove air quality sensor.
    - Output readings to USB serial.

  Output:
    0-50    = Fresh Air
    50-150  = Low Polution
    150-400 = High Polution
    400+    = Very High Polution

    Values obtains from sensor library, found at:
    https://github.com/Seeed-Studio/Grove_Air_quality_Sensor 
*/

#define AIRQ_PIN A0  // Analog input pin for the air quality sensor

int sensorValue = 0;    // Current reading
int baselineValue = 0;  // Baseline reading (calibrated clean air)

void setup() {
  // Initialise serial communication
  Serial.begin(9600);
  Serial.println("Grove Air Quality sensor");

  // Calibration
  Serial.println("Calibrating. Please wait 20 seconds...");
  pinMode(AIRQ_PIN, INPUT);

  long total = 0;
  for (int i = 0; i < 100; i++) {
    total += analogRead(AIRQ_PIN);
    delay(200);
  }
  baselineValue = total / 100;

  // Ready to go
  Serial.print("Calibration complete. Baseline = ");
  Serial.println(baselineValue);
  Serial.println("Begin air quality monitoring...");
}

void loop() {
  // 1. Read raw sensor value
  int sensorValue = analogRead(AIRQ_PIN);

  // 2. Use calibration value calculated in setup() function
  // to check if air quality has changed
  int difference = sensorValue - baselineValue;

  // 3. Output value to USB serial
  Serial.println("air_quality/" + String(difference));

  // 4. Wait at least 2 seconds between reads
  delay(2000);
}
