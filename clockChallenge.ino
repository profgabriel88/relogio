#include <Wire.h>
#include <RTC.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include "DHT.h"

#define DHTPIN 8
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2


#define BIGODE_HEIGHT 16
#define BIGODE_WIDTH  16

static const unsigned char PROGMEM bigode[] =
{ B00000000, B00000000,
  B11111111, B11111111,
  B10000001, B10000001,
  B01000010, B01000010,
  B01111110, B01111110,
  B00000000, B00000000,
  B00000000, B00000000,
  B00000000, B00000000,
  B00011111, B11111000,
  B00111110, B01111100,
  B01111100, B00111110,
  B11110000, B00001111,
  B11100000, B00000111,
  B11000000, B00000011,
  B10000000, B00000001,
  B00000000, B00000000 };

static DS1307 RTC;

void setup()
{
  Serial.begin(9600);
  RTC.begin();

  Serial.println();
  Serial.println("*** RTC 1307 ***");
  Serial.print("Is Clock Running : ");
  if (RTC.isRunning())
    Serial.println("Yes");
  else
    Serial.println("No. Time may be Inaccurate");
  Serial.print("Hour Mode : ");
  if (RTC.getHourMode() == CLOCK_H24)
    Serial.println("24 Hours");
  else
    Serial.println("12 Hours");
  Serial.print("Is Out Pin Enabled : ");
  if (RTC.isOutPinEnabled())
    Serial.println("Yes");
  else
    Serial.println("No");

  Serial.print("Is SQWE Enabled : ");
  if (RTC.isSqweEnabled())
    Serial.println("Yes");
  else
    Serial.println("No");

  display.begin();
  display.setContrast(40);
  display.clearDisplay();
  display.drawBitmap(0, 32, bigode, BIGODE_HEIGHT, BIGODE_WIDTH, BLACK);
  display.display();

  dht.begin();
}

void loop()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  display.setTextSize(1);
  display.setTextColor(BLACK);

  display.setCursor(0,0);

  switch (RTC.getWeek())
  {
    case 2:
      display.println("Dom");
      break;
    case 3:
      display.println("Seg");
      break;
    case 4:
      display.println("Ter");
      break;
    case 5:
      display.println("Qua");
      break;
    case 6:
      display.println("Qui");
      break;
    case 7:
      display.println("Sex");
      break;
    case 1:
      display.println("Sab");
      break;
  }
  
  display.setCursor(33,0);
  display.println(RTC.getDay());
  display.setCursor(48,0);
  display.println(RTC.getMonth());
  display.setCursor(58,0);
  display.println(RTC.getYear());

  display.setTextSize(2);
  display.setTextColor(BLACK);
  display.setCursor(11,13);
  display.println(RTC.getHours());

  display.setCursor(32,13);
  display.println(":");

  if (RTC.getMinutes() < 10)
  {
    display.setCursor(40,13);
    display.println("0");
    display.setCursor(51,13);
    display.println(RTC.getMinutes());
  }

  else
  {  
    display.setCursor(40,13);
    display.println(RTC.getMinutes());
  }

  if (RTC.getSeconds() < 10)
  {
    display.setTextSize(1);
    display.setCursor(64,20);
    display.println("0");
    display.setCursor(70,20);
    display.println(RTC.getSeconds());
  }
  else
  {
    display.setTextSize(1);
    display.setCursor(64,20);
    display.println(RTC.getSeconds());
  }
  
  
  
  display.drawBitmap(0, 32, bigode, 16, 16, BLACK);

  display.setCursor(22,32);
  display.println("Temp");
  display.setCursor(48,32);
  display.println(t,1);
  
  // essa linha foi emprestada de https://simple-circuit.com/arduino-bmp280-nokia-5110-lcd/
  display.drawRect(72, 32, 3, 3, BLACK); // desenha o símbolo °
  
  display.setCursor(76,32);
  display.println("C");

  display.setCursor(22,41);
  display.println("Umid");
  display.setCursor(48,41);
  display.println(h,1);
  display.setCursor(73,41);
  display.println("%");  
  
  display.display();
  delay(900);
  display.clearDisplay();

}
