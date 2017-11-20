<<<<<<< current
#include <dht.h>
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"
#include <avr/power.h>
#include "LowPower.h"

dht DHT;

#define DHT22_PIN 2

RF24 radio(9, 10);
const uint64_t pipes[4] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0E2LL, 0xF0F0F0F0E3LL, 0xF0F0F0F0E4LL };

// The size of this struct should not exceed 32 bytes
struct sensorData1 {
  float temp1;
  float humidity1;
};

sensorData1 data1;

struct
{
    uint32_t total;
    uint32_t ok;
    uint32_t crc_error;
    uint32_t time_out;
    uint32_t connect;
    uint32_t ack_l;
    uint32_t ack_h;
    uint32_t unknown;
} stat = { 0,0,0,0,0,0,0,0};

void setup()
{
    Serial.begin(9600);
    printf_begin();
    radio.begin();
    radio.setAutoAck(false);
    radio.setDataRate(RF24_250KBPS);
    radio.openWritingPipe(pipes[1]);
    radio.startListening();
    radio.printDetails();
    Serial.println("Type,\tstatus,\tHumidity (%),\tTemperature (C)\tTime (us)");

     // Disable analog to digital conversion (ADC) to drop power consumption
     ADCSRA = 0;
     power_adc_disable(); // ADC converter
     power_timer1_disable();// Timer 1
     power_timer2_disable();// Timer 2
     power_twi_disable(); // TWI (I2C)
}

void loop()
{
    uint32_t start = micros();
    int chk = DHT.read22(DHT22_PIN);
    uint32_t stop = micros();

    stat.total++;
    switch (chk)
    {
    case DHTLIB_OK:
        stat.ok++;
        Serial.print("OK,\t");
        break;
    case DHTLIB_ERROR_CHECKSUM:
        stat.crc_error++;
        Serial.print("Checksum error,\t");
        break;
    case DHTLIB_ERROR_TIMEOUT:
        stat.time_out++;
        Serial.print("Time out error,\t");
        break;
    case DHTLIB_ERROR_CONNECT:
        stat.connect++;
        Serial.print("Connect error,\t");
        break;
    case DHTLIB_ERROR_ACK_L:
        stat.ack_l++;
        Serial.print("Ack Low error,\t");
        break;
    case DHTLIB_ERROR_ACK_H:
        stat.ack_h++;
        Serial.print("Ack High error,\t");
        break;
    default:
        stat.unknown++;
        Serial.print("Unknown error,\t");
        break;
    }
    // Display data to serial monitor.
    Serial.print(DHT.humidity, 1);
    Serial.print(",\t");
    Serial.print(DHT.temperature, 1);
    Serial.print(",\t");
    Serial.print(stop - start);
    Serial.println();

    data1.temp1 = DHT.temperature;
    data1.humidity1 = DHT.humidity;

    if (radio.write(&data1, sizeof(sensorData1))) {

   delay(10);
   ADCSRA = 0;  // disable ADC
   radio.powerDown();
  // power_all_disable ();   // turn off all modules
   for(int i=0;i<53;i++) //(53 * 8) / 60 = 7.06 minutes
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
    }
}
=======
#include <dht.h>
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"
#include <avr/power.h>
#include "LowPower.h"

dht DHT;

#define DHT22_PIN 2

RF24 radio(9, 10);
const uint64_t pipes[4] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0E2LL, 0xF0F0F0F0E3LL, 0xF0F0F0F0E4LL };

// The sizeof this struct should not exceed 32 bytes
struct sensorData1 {
  float temp1;
  float humidity1;
};

sensorData1 data1;

struct
{
    uint32_t total;
    uint32_t ok;
    uint32_t crc_error;
    uint32_t time_out;
    uint32_t connect;
    uint32_t ack_l;
    uint32_t ack_h;
    uint32_t unknown;
} stat = { 0,0,0,0,0,0,0,0};

void setup()
{
    Serial.begin(9600);
    printf_begin();
    radio.begin();
    radio.setAutoAck(false);
    radio.setDataRate(RF24_250KBPS);
   //radio.setRetries(15, 15);
    radio.openWritingPipe(pipes[1]);
    radio.startListening();
    radio.printDetails();
    Serial.println("Type,\tstatus,\tHumidity (%),\tTemperature (C)\tTime (us)");

    // disable analog to digital conversion (ADC) to drop power consumption
     ADCSRA = 0;
     power_adc_disable(); // ADC converter
     power_timer1_disable();// Timer 1
     power_timer2_disable();// Timer 2
     power_twi_disable(); // TWI (I2C)
}

void loop()
{
    uint32_t start = micros();
    int chk = DHT.read22(DHT22_PIN);
    uint32_t stop = micros();

    stat.total++;
    switch (chk)
    {
    case DHTLIB_OK:
        stat.ok++;
        Serial.print("OK,\t");
        break;
    case DHTLIB_ERROR_CHECKSUM:
        stat.crc_error++;
        Serial.print("Checksum error,\t");
        break;
    case DHTLIB_ERROR_TIMEOUT:
        stat.time_out++;
        Serial.print("Time out error,\t");
        break;
    case DHTLIB_ERROR_CONNECT:
        stat.connect++;
        Serial.print("Connect error,\t");
        break;
    case DHTLIB_ERROR_ACK_L:
        stat.ack_l++;
        Serial.print("Ack Low error,\t");
        break;
    case DHTLIB_ERROR_ACK_H:
        stat.ack_h++;
        Serial.print("Ack High error,\t");
        break;
    default:
        stat.unknown++;
        Serial.print("Unknown error,\t");
        break;
    }
    // DISPLAY DATA
    Serial.print(DHT.humidity, 1);
    Serial.print(",\t");
    Serial.print(DHT.temperature, 1);
    Serial.print(",\t");
    Serial.print(stop - start);
    Serial.println();

    data1.temp1 = DHT.temperature;
    data1.humidity1 = DHT.humidity;

    if (radio.write(&data1, sizeof(sensorData1))) {

      delay(10);
   /*CLKPR = 0x80; // lager rare tall når den våkner opp igjen for å sende neste runde med data?
   CLKPR = 0x04;*/
   ADCSRA = 0;  // disable ADC
   radio.powerDown();
  // power_all_disable ();   // turn off all modules
   for(int i=0;i<53;i++) //37 = 5min
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
    }


}
>>>>>>> before discard
