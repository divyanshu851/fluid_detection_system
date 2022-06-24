#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(9, 10); // CE, CSN
const byte address[6] = "00001";

int data[6];

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}
void loop() {
  if (radio.available()) {
    radio.read(&data, sizeof(data));
   Serial.print(data[0]);
   Serial.print("x");
   Serial.print(data[1]);
   Serial.print("x");
   Serial.print(data[2]);
   Serial.print("x");
   Serial.print(data[3]);
   Serial.print("x");
   Serial.print(data[4]);
   Serial.print("x");
   Serial.println(data[5]);
 }
}
