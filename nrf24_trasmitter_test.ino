#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <NewPing.h>
#include <Wire.h>
#include <Adafruit_BMP280.h>


#define trigger_pin1 3
#define echo_pin1 2
#define trigger_pin2 5
#define echo_pin2 4
#define max_distance 200
#define sensor1 A0
#define sensor2 A1

NewPing sonar1(trigger_pin1, echo_pin1, max_distance);
NewPing sonar2(trigger_pin2, echo_pin2, max_distance);
Adafruit_BMP280 bmp;

RF24 radio(9, 10); // CE, CSN
const byte address[6] = "00001";
int data[6];

void setup() {
  radio.begin();
  Serial.begin(9600);
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  bmp.begin();
 bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
}
void loop() {
  delay(50);
  data[0] = sonar1.ping_cm();
  data[1] = sonar2.ping_cm();
  data[2] = analogRead(sensor1);
  data[3] = analogRead(sensor2);
  data[4] = bmp.readTemperature();
  data[5] = bmp.readPressure();

   Serial.print("Distance 1: ");
   Serial.print(data[0]);
   Serial.print(" | Distance 2: ");
   Serial.print(data[1]);
   Serial.print(" | Water Level 1: ");
   Serial.print(data[2]);
   Serial.print(" | Water Level 2: ");
   Serial.println(data[3]);
   Serial.print(" | Temperature: ");
   Serial.print(data[4]);
   Serial.print(" | Pressure: ");
   Serial.println(data[5]);
  
  radio.write(&data, sizeof(data));
  delay(500);
}
