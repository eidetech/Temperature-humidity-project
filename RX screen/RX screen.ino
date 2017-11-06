#include <TFT_HX8357.h> // Hardware-specific library
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "printf.h"
#include "Free_Fonts.h" // Include the header file attached to this sketch

/*************************************************************************/

TFT_HX8357 tft = TFT_HX8357();       // Invoke custom library
unsigned long drawTime = 0;

/*************************************************************************/

unsigned long packetsRead = 0;
unsigned long lastUpdate = 0;
int packetsSec = 0;
unsigned long lastRecvTime = 0;
unsigned long drops = 0;

/*************************************************************************/

float temp1, temp2, temp3, temp1_old, temp2_old, temp3_old, test, test2, test3;
float humidity1, humidity2, humidity3;

/*************************************************************************/

RF24 radio(7, 8);
const uint64_t pipes[4] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0E2LL, 0xF0F0F0F0E3LL, 0xF0F0F0F0E4LL };

// The sizeof this struct should not exceed 32 bytes
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

//PRINTE user interface 1 gang.
void printUI() {
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_DARKGREY, TFT_BLACK);
  tft.setFreeFont(FSS12);
  
  /*OVERSKRIFT*/
  tft.drawString("Temperatur & fuktighetssensor", 80, 20, GFXFF);
  tft.drawLine(1, 50, 600, 50, TFT_ORANGE);
  
  /*HEADERS*/
  tft.setFreeFont(FSS12);
  tft.drawString("Sensor", 20, 60, GFXFF);
  tft.drawLine(1, 85, 600, 85, TFT_ORANGE);
  tft.drawString("Temperatur", 160, 60, GFXFF);
  tft.drawString("Luftfuktighet  ", 330, 60, GFXFF);
  
  tft.drawString("Sensor 1", 20, 100, GFXFF);
  tft.drawString("Sensor 2", 20, 143, GFXFF);
  tft.drawString("Sensor 3", 20, 185, GFXFF);
  }

/*************************************************************************/
  
void setup(void) {
  tft.begin();
  tft.setRotation(1);
  printUI();
  
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
  
  /*SENSORER*/
  tft.setFreeFont(FSS12);
  
  byte id = 0;

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

   
  /* SENSOR 1 - check if still receiving data */
  if (time_now - lastReceive_1 > 900000 ) { //Verdien her er det som bestemmer om skjermen ikke lenger viser siste verdi den fikk.
  tft.fillRect(220,100,120,40,TFT_BLACK);
  tft.drawString("---", 220, 100, GFXFF);
  tft.fillRect(380,100,120,40,TFT_BLACK);
  tft.drawString("---", 380, 100, GFXFF);
  Serial.println("Sensor 1 off");
  }

  /* SENSOR 2 - check if still receiving data */
  if (time_now - lastReceive_2 > 900000 ) { 
  tft.fillRect(220,143,120,40,TFT_BLACK);
  tft.drawString("---", 220, 143, GFXFF);
  tft.fillRect(380,143,120,40,TFT_BLACK);
  tft.drawString("---", 380, 143, GFXFF);
  Serial.println("Sensor 2 off");
  }

  /* SENSOR 3 - check if still receiving data */
  if (time_now - lastReceive_3 > 900000 ) {
  tft.fillRect(220,185,120,40,TFT_BLACK);
  tft.drawString("---", 220, 185, GFXFF);
  tft.fillRect(380,185,120,40,TFT_BLACK);
  tft.drawString("---", 380, 185, GFXFF);
  Serial.println("Sensor 3 off");
  }
  
  /* CHECK IF RADIOS ARE AVAILABLE */
  if (radio.available(&id)) {


  /*SENSOR 1 - display data and update last receive variable*/
  if (id == 1) {
    //delay(50);
    radio.read(&data1, sizeof(sensorData1));
    lastReceive_1 = time_now;
    int sensorHum_1 = data1.humidity1;
    int sensorTemp_1 = data1.temp1;
      //if (temp1 != temp1_old) {
      tft.fillRect(220,100,120,40,TFT_BLACK);
      tft.drawFloat(sensorTemp_1, 1, 220, 100, GFXFF);
      tft.drawString("C", 270, 100, GFXFF);
      tft.fillRect(380,100,120,40,TFT_BLACK);
      tft.drawFloat(sensorHum_1, 1, 380, 100, GFXFF);
      tft.drawString("%", 430, 100, GFXFF);
      Serial.println("Sensor 1:");
      Serial.println(data1.temp1);
      //temp1_old = temp1;
   // }
  }

/*SENSOR 2 - display data and update last receive variable*/
  if (id == 2) {
    //delay(50);
    radio.read(&data2, sizeof(sensorData2));
    lastReceive_2 = time_now;
    int sensorHum_2 = data2.humidity2;
    int sensorTemp_2 = data2.temp2;
      //if (temp2 != temp2_old) {
      tft.fillRect(220,143,120,40,TFT_BLACK);
      tft.drawFloat(sensorTemp_2, 1, 220, 143, GFXFF);
      tft.drawString("C", 270, 143, GFXFF);
      tft.fillRect(380,143,120,40,TFT_BLACK);
      tft.drawFloat(sensorHum_2, 1, 380, 143, GFXFF);
      tft.drawString("%", 430, 143, GFXFF);
      Serial.println("Sensor 2:");
      Serial.println(data2.temp2);
      //temp2_old = temp2;
   // }
  }

/*SENSOR 3 - display data and update last receive variable*/
  if (id == 3) {
    //delay(50);
    radio.read(&data3, sizeof(sensorData3));
    lastReceive_3 = time_now;
    int sensorHum_3 = data3.humidity3;
    int sensorTemp_3 = data3.temp3;
      //if (temp3 != temp3_old) {
      tft.fillRect(220,185,120,40,TFT_BLACK);
      tft.drawFloat(sensorTemp_3, 1, 220, 185, GFXFF);
      tft.drawString("C", 270, 185, GFXFF);
      tft.fillRect(380,185,120,40,TFT_BLACK);
      tft.drawFloat(sensorHum_3, 1, 380, 185, GFXFF);
      tft.drawString("%", 430, 185, GFXFF);
      Serial.println("Sensor 3:");
      Serial.println(data3.temp3);
      //temp2_old = temp2;
   // }
  }
/*
  /*SENSOR 3 - display data and update last receive variable
  if (id == 3) {
    //delay(50);
    radio.read(&temp3, sizeof(temp3));
    lastReceive_3 = time_now;
      //if (temp3 != temp3_old) {
      tft.fillRect(220,185,120,40,TFT_BLACK);
      tft.drawFloat(temp3, 1, 220, 185, GFXFF);
      tft.drawString("256%", 410, 185, GFXFF);
      Serial.println("Sensor 3:");
      Serial.println(temp3);
     // temp3_old = temp3;
   // }
  }

    SENSOR 3
  if (id != 3 &&  time_now - lastReceive_3 > 1100 ) {
  tft.fillRect(220,185,120,40,TFT_BLACK);
  tft.drawString("---", 220, 185, GFXFF);
  Serial.println("Sensor 3 off");
  state_3 = true;
  }else{
  lastReceive_3 = millis();
 
  if (id == 3) {
    //delay(50);
    radio.read(&temp3, sizeof(temp3));
    if (temp3 != temp3_old || state_3 == true) {
      tft.fillRect(220,185,120,40,TFT_BLACK);
      tft.drawFloat(temp3, 1, 220, 185, GFXFF);
      tft.drawString("256%", 410, 185, GFXFF);
    
    Serial.println("Sensor 3:");
    Serial.println(temp3);
    temp3_old = temp3;
    state_3 = false;
    }
  }
  }
*/
  
}else{
 // Serial.println("No radios available.");
}
delay(250);
}

#ifndef LOAD_GLCD
//ERROR_Please_enable_LOAD_GLCD_in_User_Setup
#endif

#ifndef LOAD_FONT2
//ERROR_Please_enable_LOAD_FONT2_in_User_Setup!
#endif

#ifndef LOAD_FONT4
//ERROR_Please_enable_LOAD_FONT4_in_User_Setup!
#endif

#ifndef LOAD_FONT6
//ERROR_Please_enable_LOAD_FONT6_in_User_Setup!
#endif

#ifndef LOAD_FONT7
//ERROR_Please_enable_LOAD_FONT7_in_User_Setup!
#endif

#ifndef LOAD_FONT8
//ERROR_Please_enable_LOAD_FONT8_in_User_Setup!
#endif

#ifndef LOAD_GFXFF
ERROR_Please_enable_LOAD_GFXFF_in_User_Setup!
#endif
