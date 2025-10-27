/*
  File: Grove_Sound_Serial.ino
  
  More info on this sensor can be found on the Seeed Studio Wiki:
  https://wiki.seeedstudio.com/Grove-Sound_Sensor/

  Description:
    - Connect sensor to port A0
    - Read data from Grove sound sensor.
    - Output readings to USB serial.
*/

#define SOUND_PIN A0

void setup() {
  // Initialise serial communication
  Serial.begin(9600);
  Serial.println("Grove Sound sensor");
}

void loop() {
  // 1. Average 50 sound sensor readings
  long summedSoundValues = 0;

  // a) Add 50 readings together
  for (int i = 0; i < 50; i++)
    summedSoundValues += analogRead(SOUND_PIN);  // Add 50 readings together

  // b) Divide by total number of readings to get average
  int average = summedSoundValues / 50;  

  // 2. Output average reading to USB serial
  Serial.println("sound " + String(average));
  delay(10);
}
