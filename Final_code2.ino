#include <Wire.h>
#include <Adafruit_BMP280.h>
#include <BH1750.h> // Updated library
#include <DHT11.h>

// Vibration sensor
const int vibrationSensorPin = 2; // Change to D7
int sensorValue = 0;
unsigned long startTime = 0;
unsigned long elapsedTime = 0;
const unsigned long interval = 2000; // Interval in milliseconds (2 seconds)
int vibrationCount = 0;
const int threshold = 500;

// BMP280
Adafruit_BMP280 bmp;
float temperature;
float pressure;
float altitude;

// Light sensor (GY-302) - BH1750
BH1750 lightSensor;

// DHT11
// DHT11 DHT;

void setup() {
  Serial.begin(9600);
  
  // BMP280 setup
  if (!bmp.begin()) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    while (1);
  }
  
  // Light sensor setup
  //lightSensor.begin();
  //lightSensor.configure(BH1750_CONTINUOUS_HIGH_RES_MODE); // Configure sensor mode

  // Record the start time
  startTime = millis();
}

void loop() {
  // Read vibration sensor
  sensorValue = digitalRead(vibrationSensorPin);
  if(sensorValue == HIGH) {
    vibrationCount++;
  }
  
  // Read BMP280 sensor
  temperature = bmp.readTemperature();
  pressure = bmp.readPressure() / 100.0;
  altitude = bmp.readAltitude(1013.25); // Adjusted to your local pressure
  
  // Read light sensor
  float lightLevel = lightSensor.readLightLevel();
  
  // Read DHT11 sensor
  //int chk = DHT.read11(2); // DHT11 connected to D2
  //float humidity = DHT.humidity;
  
  // Check if the interval has elapsed
  elapsedTime = millis() - startTime;
  if (elapsedTime >= interval) {
    // Print sensor readings
    Serial.println("Vibration count: " + String(vibrationCount));
    Serial.println("Temperature: " + String(temperature) + " °C");
    Serial.println("Pressure: " + String(pressure) + " hPa");
    Serial.println("Altitude: " + String(altitude) + " meters");
    Serial.println("Light level: " + String(lightLevel) + " lux");
 //   Serial.println("Humidity: " + String(humidity) + " %");
    Serial.println();
    
    // Reset variables and start time
    vibrationCount = 0;
    startTime = millis();
  }
  
  delay(100); // Delay for stability
}
