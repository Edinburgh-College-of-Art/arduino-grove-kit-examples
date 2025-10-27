/*
  File: Grove_DHT_Serial.ino
  
  More info on this sensor can be found on the Seeed Studio Wiki:
  https://wiki.seeedstudio.com/Grove-TemperatureAndHumidity_Sensor/

  Description:
    - Connect sensor to port D2.
    - Read data from Grove temperature and humidity sensor.
    - Output readings to USB serial.

    - Outputs temperature in °C and humidity in % (approx.).
*/

#define DHT_PIN 2

float humidity;
float temperature;

uint8_t dhtData[5];

void setup() {
  // Initialise serial communication
  Serial.begin(9600);
  Serial.println("Grove Temperature and Humidity sensor");
}

void loop() {
  // 1. Check if sensor read is successful
  bool readStatus = readDHT11();

  // 2. If successful, output values to USB serial
  if (readStatus) {
    Serial.println("humidity " + String(humidity));
    Serial.println("temperature " + String(temperature));
  }

  // 3. Wait at least 2 seconds between reads
  delay(2500);
}

//================================================================
// Functions for reading DHT11
// Code adapted from Grove DHT Library, found at:
// https://github.com/Seeed-Studio/Grove_Temperature_And_Humidity_Sensor

bool readDHT11() {
  uint8_t lastState = HIGH;
  uint8_t counter = 0;
  uint8_t j = 0, i;

  // Clear previous data
  for (i = 0; i < 5; i++) dhtData[i] = 0;

  // Send start signal
  pinMode(DHT_PIN, OUTPUT);
  digitalWrite(DHT_PIN, LOW);
  delay(20);
  digitalWrite(DHT_PIN, HIGH);
  delayMicroseconds(30);
  pinMode(DHT_PIN, INPUT_PULLUP);

  // Wait for DHT response
  unsigned long t = micros();
  while (digitalRead(DHT_PIN) == HIGH) {
    if (micros() - t > 90) return false;  // timeout
  }

  t = micros();
  while (digitalRead(DHT_PIN) == LOW)
    if (micros() - t > 90) return false;

  t = micros();
  while (digitalRead(DHT_PIN) == HIGH)
    if (micros() - t > 90) return false;

  // Read 40 bits (5 bytes)
  for (i = 0; i < 40; i++) {
    // Wait for low signal
    t = micros();
    while (digitalRead(DHT_PIN) == LOW) {
      if (micros() - t > 90) return false;
    }

    // Measure high signal length
    unsigned long start = micros();
    while (digitalRead(DHT_PIN) == HIGH) {
      if (micros() - start > 90) break;
    }
    unsigned long pulseLength = micros() - start;

    // Determine bit value (threshold around 50 µs)
    dhtData[i / 8] <<= 1;
    if (pulseLength > 50) dhtData[i / 8] |= 1;
  }

  // Check checksum
  if (dhtData[4] != ((dhtData[0] + dhtData[1] + dhtData[2] + dhtData[3]) & 0xFF))
    return false;

  // Convert data
  humidity = dhtData[0] + dhtData[1] * 0.1;
  temperature = dhtData[2] + dhtData[3] * 0.1;

  // Reset data line (important for next read)
  pinMode(DHT_PIN, OUTPUT);
  digitalWrite(DHT_PIN, HIGH);
  delay(10);
  pinMode(DHT_PIN, INPUT_PULLUP);

  return true;
}
