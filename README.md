# relogio
Relogio Digital Com Arduino

Usa um módulo RTC DS1307, um sensor de umidade/temperatura DHT11 e um display Nokia 5110;

É necessário instalar as bibliotecas:

RTC.h by Manjunath CV

DHT.h (DHT sensor library) by Adafruit

Adafruit_PCD8544.h (Adafruit PCD8544 Nokia 5110 LCD library) by Adafruit

Para instalar as bibliotecas, na IDE do Arduino, selecione 'Ferramentas' e 'Gerenciador de Biblioteca'
pesquise pelo nome e clique em instalar. As bibliotecas terão dependencias, instale-as.

O trecho a seguir define a logo que é mostrada no canto inferior esquerdo. '1' representa um pixel e '0'
representa um espaço em branco;

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
  
display.drawBitmap(0, 32, bigode, BIGODE_HEIGHT, BIGODE_WIDTH, BLACK);
essa linha mostra a logo na tela, se não quiser exibir, basta comentá-la.
