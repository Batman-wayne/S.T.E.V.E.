#include <bitswap.h>
#include <chipsets.h>
#include <color.h>
#include <colorpalettes.h>
#include <colorutils.h>
#include <controller.h>
#include <cpp_compat.h>
#include <dmx.h>
#include <FastLED.h>
#include <fastled_config.h>
#include <fastled_delay.h>
#include <fastled_progmem.h>
#include <fastpin.h>
#include <fastspi.h>
#include <fastspi_bitbang.h>
#include <fastspi_dma.h>
#include <fastspi_nop.h>
#include <fastspi_ref.h>
#include <fastspi_types.h>
#include <hsv2rgb.h>
#include <led_sysdefs.h>
#include <lib8tion.h>
#include <noise.h>
#include <pixelset.h>
#include <pixeltypes.h>
#include <platforms.h>
#include <power_mgt.h>

#define NUM_LEDS 30
#define DATA_PIN 5
#define trigPin2 11
#define echoPin2 10

CRGB leds[NUM_LEDS];

#include <SoftwareSerial.h>
SoftwareSerial BT(9, 8); //RX, TX
// Pins used for inputs and outputs********************************************************

int led = 13;
//Arrays for the 4 inputs**********************************************
String sensorValue[4];
float voltageValue[4] = {0, 0, 0, 0};
long duration, distance, Sensor2;

//Char used for reading in Serial characters
char inbyte = 0;
char values[4];
byte index = 0;
int flag = 0;
//*******************************************************************************************

void setup() {
  // initialise serial communications at 9600 bps:
  Serial.begin(9600);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  pinMode(trigPin2, OUTPUT);
pinMode(echoPin2, INPUT); 
  BT.begin(9600);
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
}

void loop() {
  while (BT.available() > 0) {
    inbyte = BT.read();
    if (inbyte == 0x23) {
      index = 0;
      flag = 1;
    }
    else {
      values[index] = inbyte;
      index++;
      flag = 0;
    }
    if (flag == 1){
      float battery_percent;
      battery_percent = (float)atof(values);
      battery_percent *= 100;
      int battery = (int) battery_percent;
      int count = (battery*30)/100;
      if (count<1)count=1; 
      if (count <= 30){
        for (int i = 0; i < count; i++){
          leds[i] = CRGB::Green;
                  FastLED.show();
        }

      }
      else {
        for (int i = 0; i < count; i++){
          leds[i] = CRGB::Green;
                  FastLED.show();
          }

        }
      for (int i =0; i <4; i++){
        Serial.print(values[i]);
        }
        Serial.println();
    }


  }
   digitalWrite(trigPin2, LOW); 
  delayMicroseconds(2); 
  digitalWrite(trigPin2, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW); 
  duration = pulseIn(echoPin2, HIGH); 
  distance = (duration/2)/29.1; 
  Sensor2 = distance;
  if (distance < 3){
    digitalWrite(3, HIGH);
    Serial.println("detected");
  }

  delay(1000);
  }




