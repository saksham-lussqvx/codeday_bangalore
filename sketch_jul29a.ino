// Include application, user and local libraries
#include "SPI.h"
#include "TFT_22_ILI9225.h"
#ifdef ARDUINO_ARCH_STM32F1
#define TFT_RST PA1
#define TFT_RS  PA2
#define TFT_CS  PA0 // SS
#define TFT_SDI PA7 // MOSI
#define TFT_CLK PA5 // SCK
#define TFT_LED 0   // 0 if wired to +5V directly
#elif defined(ESP8266)
#define TFT_RST 4   // D2
#define TFT_RS  5   // D1
#define TFT_CLK 14  // D5 SCK
//#define TFT_SDO 12  // D6 MISO
#define TFT_SDI 13  // D7 MOSI
#define TFT_CS  15  // D8 SS
#define TFT_LED 2   // D4     set 0 if wired to +5V directly -> D3=0 is not possible !!
#elif defined(ESP32)
#define TFT_RST 26  // IO 26
#define TFT_RS  25  // IO 25
#define TFT_CLK 14  // HSPI-SCK
//#define TFT_SDO 12  // HSPI-MISO
#define TFT_SDI 13  // HSPI-MOSI
#define TFT_CS  15  // HSPI-SS0
#define TFT_LED 0   // 0 if wired to +5V directly
SPIClass hspi(HSPI);
#else
#define TFT_RST 8
#define TFT_RS  9
#define TFT_CS  10  // SS
#define TFT_SDI 11  // MOSI
#define TFT_CLK 13  // SCK
#define TFT_LED 3   // 0 if wired to +5V directly
#endif

#define TFT_BRIGHTNESS 200 // Initial brightness of TFT backlight (optional)

// Use hardware SPI (faster - on Uno: 13-SCK, 12-MISO, 11-MOSI)
TFT_22_ILI9225 tft = TFT_22_ILI9225(TFT_RST, TFT_RS, TFT_CS, TFT_LED, TFT_BRIGHTNESS);
// Use software SPI (slower)
//TFT_22_ILI9225 tft = TFT_22_ILI9225(TFT_RST, TFT_RS, TFT_CS, TFT_SDI, TFT_CLK, TFT_LED, TFT_BRIGHTNESS);

// Variables and constants
uint16_t x, y;
boolean flag = false;
int trigPin = 3;
int echoPin = 4;
long duration;
int distance;
int randNumber;
int randNumber_main;
// Setup
void setup() {

#if defined(ESP32)
  hspi.begin();
  tft.begin(hspi);
#else
  tft.begin();
#endif
  Serial.begin(9600);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
}

// Loop
void loop() {
    tft.clear();
  tft.drawText(10,80, "      ASTRAL",COLOR_WHITE);
  tft.drawText(10,100, "      PALM", COLOR_WHITE);
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  duration=pulseIn(echoPin,HIGH);
  distance=(duration*0.034/2);
  Serial.print("Distance : ");
  Serial.print(distance);
  Serial.println(" cm ");
  tft.drawRectangle(0, 0, tft.maxX() - 1, tft.maxY() - 1, COLOR_WHITE);
  
  randNumber_main = newrandom(1,3);
  randNumber = newrandom(1,6);
  if(distance < 10){
    if (randNumber_main == 1){
      Serial.println("You're Happy :)");
      if (randNumber == 1){
      Serial.println("Keep up the good mood! Cherish the moment.");
      }
      if (randNumber == 2){
      Serial.println("Wow what got your mood so high today.");
      }
      if (randNumber == 3){
      Serial.println("Are you thinking about me, cause you look so HAPPY!");
      }
      if (randNumber == 4){
      Serial.println("Man, what a wonderful way, to be alive, isn't it!");
      }
      if (randNumber == 5){
      Serial.println("Did you win a lottery with you, cause you look ecstatic!");
      }
    }

    if (randNumber_main == 2){
      Serial.println("You're Afraid :')");
      if (randNumber == 1){
      Serial.println("It's okay to be afraid, humans aren't god.");
      }
      if (randNumber == 2){
      Serial.println("Here's a virtual hug to help you calm down");
      }
      if (randNumber == 3){
      Serial.println("You are not alone, take a deep breath");
      }
      if (randNumber == 4){
      Serial.println("Fear proves you are a human, cherish it.");
      }
      if (randNumber == 5){
      Serial.println("Nothing will happen, stay strong and survive.");
      }
    }
  }
delay(2000);
}
unsigned long newrandom(unsigned long howsmall, unsigned long howbig)
{
  return howsmall + random() % (howbig-howsmall);
}
