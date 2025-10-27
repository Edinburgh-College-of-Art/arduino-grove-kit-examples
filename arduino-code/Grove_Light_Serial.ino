/*
  File: Grove_Light_Serial.ino
  
  More info on this sensor can be found on the Seeed Studio Wiki:
  https://wiki.seeedstudio.com/Grove-Light_Sensor/

  Description:
    - Connect sensor to port A0
    - Read data from Grove Light sensor.
    - Output readings to USB serial.
*/

#define LIGHT_PIN A0

void setup() {
  // Initialise Serial communication
  Serial.begin(9600); 
  Serial.println("Grove Light sensor");
}

void loop() {
  // 1. Read light sensor value
  int lightValue = analogRead(LIGHT_PIN);

  // 2. Output light value to USB serial
  Serial.println("light " + String(lightValue));
}