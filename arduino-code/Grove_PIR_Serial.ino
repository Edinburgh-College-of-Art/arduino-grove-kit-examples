/*
  File: Grove_PIR_Serial.ino

  More info on this sensor can be found on the Seeed Studio Wiki:
  https://wiki.seeedstudio.com/Grove-Adjustable_PIR_Motion_Sensor/

  Description:
    - Connect sensor to port D2
    - Read data from Grove PIR sensor.
    - Output readings to USB serial.

    - Output will be 1 if motion detected and 0 if no motion detected.
*/

#define PIR_PIN 2

void setup() {
  // Initialise serial communication
  Serial.begin(9600);
  Serial.println("Grove PIR sensor");

  // Initialise PIR pin as an INPUT device
  pinMode(PIR_PIN, INPUT);
}

void loop() {
  // 1. Read PIR value (1=motion, 0=no motion)
  int pirValue = digitalRead(PIR_PIN);
  
  // 2. Output value to USB serial
  Serial.println("motion " + String(pirValue));
}
