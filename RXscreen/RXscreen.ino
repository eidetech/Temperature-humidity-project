
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "printf.h"
#include "Free_Fonts.h" // Include the header file attached to this sketch

/*************************************************************************/

unsigned long packetsRead = 0;
unsigned long lastUpdate = 0;
int packetsSec = 0;
unsigned long lastRecvTime = 0;
unsigned long drops = 0;

/*************************************************************************/

float temp1, temp2, temp3, temp1_old, temp2_old, temp3_old, test, test2, test3;
float humidity1, humidity2, humidity3;
byte id = 0;

/*************************************************************************/

RF24 radio(7, 8);
const uint64_t pipes[4] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0E2LL, 0xF0F0F0F0E3LL, 0xF0F0F0F0E4LL };

// The size of this struct should not exceed 32 bytes
struct sensorData1 {
  float temp1;
  float humidity1;
};

struct sensorData2 {
  float temp2;
  float humidity2;
};

struct sensorData3 {
  float temp3;
  float humidity3;
};

sensorData1 data1;
sensorData2 data2;
sensorData3 data3;

/*************************************************************************/

void setup(void) {

  Serial.begin(9600);
  printf_begin();
  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.openReadingPipe(1, pipes[1]);
  radio.openReadingPipe(2, pipes[2]);
  radio.openReadingPipe(3, pipes[3]);
  radio.startListening();
  radio.printDetails();
  delay(1000);
}

/*************************************************************************/

  unsigned long lastReceive_1 = 0;
  unsigned long lastReceive_2 = 0;
  unsigned long lastReceive_3 = 0;

/*************************************************************************/

void loop() {

  unsigned long time_now = millis();


  //delay(500);
   Serial.println("Time now:");
   Serial.println(time_now);
   Serial.println("");
   Serial.println("Lastreceive 1:");
   Serial.println(lastReceive_1);
   Serial.println("Lastreceive 2:");
   Serial.println(lastReceive_2);
   Serial.println("Lastreceive 3:");
   Serial.println(lastReceive_3);
   Serial.println("");
   test = time_now - lastReceive_1;
   Serial.println("Sum:");
   Serial.println(test);
   test2 = time_now - lastReceive_2;
   Serial.println("Sum2:");
   Serial.println(test2);
   test3 = time_now - lastReceive_3;
   Serial.println("Sum3:");
   Serial.println(test3);
   Serial.println("");


}
