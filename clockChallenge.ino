#include <Wire.h>
#include <RTC.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include "DHT.h"

#define DHTPIN 8 // pino em que o sensor será ligado - pin for the sensor
#define DHTTYPE DHT11 // modelo do sensor - type of sensor

DHT dht(DHTPIN, DHTTYPE);

// pinos para o display - display pins
// pin 7 - Serial clock out (SCLK)
// pin 6 - Serial data out (DIN)
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)
Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3); 

// tamanho do logo - size of the logo
#define BIGODE_HEIGHT 16
#define BIGODE_WIDTH  16

// logo
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
  RTC.begin(); // inicia o relógio - starts the clock
  
  display.begin(); // inicia o display - starts the diplay
  display.setContrast(40); // ajusta o contraste - set the contrast
  display.clearDisplay();

  dht.begin(); // inicia o sensor - starts the sensor
}

void loop()
{
  float h = dht.readHumidity(); // umidade - humidity
  float t = dht.readTemperature(); // temperatura - temperature
  
  display.setTextSize(1); // tamanho do texto
  display.setTextColor(BLACK);

  display.setCursor(0,0); // posiciona o cursor no inicio da tela

  // determina o dia da semana - gets the day of the week
  switch (RTC.getWeek())
  {
    case 2:
      display.println("Dom"); // sunday
      break;
    case 3:
      display.println("Seg"); // monday
      break;
    case 4:
      display.println("Ter"); // tuesday
      break;
    case 5:
      display.println("Qua"); // wednsday
      break;
    case 6:
      display.println("Qui"); // thursday
      break;
    case 7:
      display.println("Sex"); // fryday
      break;
    case 1:
      display.println("Sab"); // saturday
      break;
  }
  
  display.setCursor(33,0);
  display.println(RTC.getDay()); // mostra no display o dia - show the day on the display
  display.setCursor(48,0);
  display.println(RTC.getMonth()); // mês - month
  display.setCursor(58,0);
  display.println(RTC.getYear()); // ano - year

  display.setTextSize(2); // muda o tamanho do texto - change text size
  display.setTextColor(BLACK);
  display.setCursor(11,13);
  display.println(RTC.getHours()); // mostra as horas - show the hours

  display.setCursor(32,13);
  display.println(":"); // mostra o símbolo : - displays the symbol :

  // aqui se os minutos forem menor que 10 precisamos colocar o 0 antes
  // if minutes is less than 10 we need to display the 0 first
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
  
  
  // aqui se os segundos forem menor que 10 precisamos colocar o 0 antes
  // if seconds is less than 10 we need to display the 0 first
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
  
  
  // essa linha desenha a logo - this line draws the logo
  display.drawBitmap(0, 32, bigode, BIGODE_HEIGHT, BIGODE_WIDTH, BLACK);
  
  // as linhas a seguir mostram a temperatura em °C
  // the following lines display the temperature in Celsius 
  display.setCursor(22,32);
  display.println("Temp");
  display.setCursor(48,32);
  display.println(t, 1); // mostra a temperatura e ajusta para uma casa decimal - display temperature with one decimal place
  
  // essa linha foi emprestada de https://simple-circuit.com/arduino-bmp280-nokia-5110-lcd/
  // this line is borrowed from the site above
  display.drawRect(72, 32, 3, 3, BLACK); // desenha o símbolo ° - draws the ° symbol
  
  display.setCursor(76,32);
  display.println("C");

  // as linhas a seguir mostram a umidade relativa
  // the following lines shows the humidity
  display.setCursor(22,41);
  display.println("Umid");
  display.setCursor(48,41);
  display.println(h, 1); // mostra a umidade e ajusta para uma casa decimal - display humidity with one decimal place
  display.setCursor(73,41);
  display.println("%");  
  
  // atualiza o display - update the display
  display.display();
  // espera 900 milissegundos antes de repetir - delays 900 miliseconds
  delay(900);
  
  // limpa o display - clear the display
  display.clearDisplay();

}
