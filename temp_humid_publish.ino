#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include "config.h"
#include <Adafruit_Sensor.h>

#define BME_SCK 24
#define BME_MISO 22
#define BME_MOSI 23
#define BME_CS 5
#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme(BME_CS);

unsigned long delayTime;
AdafruitIO_Feed *Temperature = io.feed("Temperature");
AdafruitIO_Feed *Humidity = io.feed("Humidity");
AdafruitIO_Feed *Pressure = io.feed("Pressure");

void setup() {
  unsigned status;
  Serial.begin(115200);
  status = bme.begin();
  Serial.print("Connecting to Adafruit IO");
  io.connect();
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println(io.statusText());

}

void loop() {
  io.run();
  sensors_event_t event;
  float celsius = bme.readTemperature();
  float humidity = bme.readHumidity();
  Serial.print("celsius: ");
  Serial.print(celsius);
  Serial.println("C");
  Serial.print("humidity: ");
  Serial.print(humidity);
  Serial.println("%");
 
  Temperature->save(celsius);
  Humidity->save(humidity);

  delay(120000);
}
