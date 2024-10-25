/*
* Name: clock and temp project
* Author: Wiktor Nordström
* Date: 2024-10-25
* Description: This project uses a ds3231 to measure time and displays the time to an 1306 oled display,
* Further, it measures temprature with a analog temprature module and displays a mapped value to a 9g-servo-motor 
* Additionally it maps the temprature value to a light to show if its too hot or cold in a room.
*/

// Include Libraries
#include <RTClib.h>
#include <Wire.h>
#include "U8glib.h"
#include <WS2812FX.h>
// Init constants
const int tmpPin = A1;
#define LED_COUNT 30
#define LED_PIN 5
// Init global variables
int Vo;
float R1 = 10000;  // value of R1 on board
float logR2, R2, T;
float c1 = 0.001129148, c2 = 0.000234125, c3 = 0.0000000876741;  //steinhart-hart coeficients for thermistor
// construct objects
RTC_DS3231 rtc;
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);
WS2812FX ws2812fx = WS2812FX(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // init communication
  Wire.begin();
  // Init Hardware
  pinMode(tmpPin, INPUT);
  rtc.begin();
  ws2812fx.init();
   ws2812fx.start();
  // Settings
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  u8g.setFont(u8g_font_unifont);
  ws2812fx.setBrightness(120);  // Set the LED’s overall brightness. 0=strip off, 255=strip at full intensity
  ws2812fx.setSpeed(1000);       // Set the animation speed. 10=very fast, 5000=very slow
  ws2812fx.setMode(3);
}

void loop() {

  oledWrite(10, 20, getTime());
  ledWrite();
  ws2812fx.service();
}


/*
*This function reads time from an ds3231 module and package the time as a String
*Parameters: Void
*Returns: time in hh:mm:ss as String
*/
String getTime() {
  DateTime now = rtc.now();

  return (String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second()));

  delay(1000);
}

/*
* This function reads an analog pin connected to an analog temprature sensor and calculates the corresponding temp
*Parameters: Void
*Returns: temprature as float
*/
float getTemp() {
  Vo = analogRead(tmpPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2));
  T = T - 273.15;

  return (T);
}

/*
* This function takes a string and draws it to an oled display
*Parameters: - text: String to write to display
*Returns: void
*/
void oledWrite(int x, int y, String text) {
  u8g.firstPage();
  do {

    u8g.drawStr(x, y, text.c_str());

  } while (u8g.nextPage());
}
/*
*this function takes the temprature value and maps it to a colour spectrum on the ring light
*Parameters: - none
*Returns: void
*/
void ledWrite() {

  while (getTemp() >= 20) {
    ws2812fx.setColor(map(getTemp(), 20.0, 30.0, 30, 255), 15, 20);
    ws2812fx.service();
  }
   while (getTemp() > 20) {
    ws2812fx.setColor(20 ,15, map(getTemp(), 0, 20.0, 255, 30));
    ws2812fx.service();
  }
}
