/*
  File: Grove_Distance_Serial.ino
  
  More info on this sensor can be found on the Seeed Studio Wiki:
  https://wiki.seeedstudio.com/Grove-Ultrasonic_Ranger/

  Description:
    - Connect sensor to port D7
    - Read data from Grove ultrasonic distance sensor.
    - Output readings to USB serial.

    - Outputs distance in cm (approx.).
*/

#define DISTANCE_PIN 7

void setup() {
  // Initialise serial communication
  Serial.begin(9600);
  Serial.println("Grove Ultrasonic Distance sensor");
}

void loop() {
  // 1. Get ready to send sound pulse
  pinMode(DISTANCE_PIN, OUTPUT);    // Pin set to OUTPUT
  digitalWrite(DISTANCE_PIN, LOW);  // Pin turned off
  delayMicroseconds(2);

  // 2. Send a (very) short pulse of ultrasonic sound
  digitalWrite(DISTANCE_PIN, HIGH);  // On
  delayMicroseconds(5);              // Wait 5 microseconds
  digitalWrite(DISTANCE_PIN, LOW);   // Off

  // 3. Get time for sound to bounce back
  pinMode(DISTANCE_PIN, INPUT);            // Set pin to INPUT
  long duration = pulseIn(DISTANCE_PIN, HIGH);  // Get time in microseconds

  // 4. Calculate distance (in cm)
  long distanceInCentimeters = duration / 29 / 2;

  // 5. Output distance value to USB serial
  Serial.println("distance " + String(distanceInCentimeters));
}