#include <string.h>
#include <EEPROM.h>
#include <WiFi.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_AHTX0.h>
#include <RTClib.h>
#include "esp_task_wdt.h"
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>


//================================================================================//
//================================================================================//
//================================================================================//
//===============THIS SECTION WILL BE USED FOR GLOBAL VARIABLES===================//
//================================================================================//
//================================================================================//
//================================================================================//

TaskHandle_t Task1;

#define BOTtoken "7914324580:AAGKdX346i5EBbhUfjESXx37x3sKtRb4VVU"

#define idChat "1094949906"

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

LiquidCrystal_I2C lcd(0x27,16,2);

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3c ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define BMP_SCK  (13)
#define BMP_MISO (12)
#define BMP_MOSI (11)
#define BMP_CS   (10)
Adafruit_BMP280 bmp;

Adafruit_AHTX0 aht;

const char* ssid     = "BatuKhan";
const char* password = "momoygemoy";

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 7 * 3600;;
const int   daylightOffset_sec = 0;

struct tm timeinfo;

byte satu[] PROGMEM = {
  B11111,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
};

byte dua[] PROGMEM = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
};

byte tiga[] PROGMEM = {
  B11100,
  B00010,
  B00010,
  B00001,
  B00001,
  B00010,
  B00010,
  B11100,
};

byte empat[] PROGMEM = {
  B00111,
  B01000,
  B01000,
  B10000,
  B10000,
  B01000,
  B01000,
  B00111,
};

byte lima[] PROGMEM = {
  B11100,
  B00100,
  B00100,
  B00100,
  B01000,
  B01000,
  B10000,
  B10000,
};

byte enam[] PROGMEM = {
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
};

byte tujuh[] PROGMEM = {
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B01000,
  B01000,
  B00111,
};

byte delapan[] PROGMEM = {
  B00011,
  B00100,
  B00100,
  B01000,
  B01000,
  B10000,
  B10000,
  B11111,
};

const unsigned char dick [] PROGMEM = {
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x03, 0xff, 0xff, 0xf0, 0x00, 0x1f, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xfe, 0xff, 0xc0, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xfe, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x7f, 0xfe, 0x0f, 0xff, 
	0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0xff, 0xe3, 0xff, 
	0xff, 0xff, 0xff, 0x87, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0xff, 0xf8, 0xff, 
	0xff, 0xff, 0xfe, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbf, 0xff, 0xfe, 0x7f, 
	0xff, 0xff, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbf, 0xff, 0xff, 0x7f, 
	0xff, 0xff, 0xe3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbf, 0xff, 0xff, 0x7f, 
	0xff, 0xff, 0x8f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbf, 0xff, 0xff, 0x7f, 
	0xff, 0xff, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbf, 0xff, 0xff, 0x7f, 
	0xff, 0xff, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbf, 0xf0, 0x00, 0x7f, 
	0xff, 0xfe, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbf, 0xff, 0xff, 0x7f, 
	0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbf, 0xff, 0xff, 0x7f, 
	0xff, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbf, 0xff, 0xfe, 0x7f, 
	0xff, 0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbf, 0xff, 0xfe, 0xff, 
	0xff, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbf, 0xff, 0xfe, 0xff, 
	0xff, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbf, 0xff, 0xfd, 0xff, 
	0xff, 0xf7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0xff, 0xf9, 0xff, 
	0xff, 0xe7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x7f, 0xff, 0x7f, 0xff, 0xe3, 0xff, 
	0xff, 0xef, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1f, 0x00, 0x01, 0x7f, 0xfe, 0x0f, 0xff, 
	0xff, 0xe3, 0xff, 0xff, 0xff, 0xf3, 0xff, 0xff, 0xfe, 0x7f, 0xff, 0xfe, 0x00, 0x01, 0xff, 0xff, 
	0xff, 0xfb, 0xff, 0xff, 0xff, 0xf3, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xfb, 0xff, 0xff, 0xff, 0xf1, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xfb, 0xff, 0xff, 0xff, 0xf5, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xfb, 0xff, 0xff, 0xff, 0xf5, 0xff, 0xff, 0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xfb, 0xff, 0xff, 0xff, 0xf5, 0xff, 0xff, 0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xfb, 0xff, 0xff, 0xff, 0xf5, 0xff, 0xff, 0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xfb, 0xff, 0xff, 0xff, 0xf4, 0xff, 0xff, 0xf9, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xfb, 0xff, 0xff, 0xff, 0xe6, 0xff, 0xff, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xfb, 0xff, 0xff, 0xff, 0xee, 0xff, 0xff, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xfb, 0xff, 0xff, 0xff, 0xee, 0xff, 0xff, 0xf3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xfd, 0xff, 0xff, 0xff, 0xde, 0xff, 0xff, 0xf7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xfd, 0xff, 0xff, 0xff, 0x9e, 0x7f, 0xff, 0xf7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xfd, 0xff, 0xff, 0xff, 0x3f, 0x3f, 0xff, 0xe7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xfc, 0xff, 0xff, 0xfe, 0x7f, 0x9f, 0xff, 0xef, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xfe, 0x7f, 0xff, 0xfc, 0xff, 0xcf, 0xff, 0xef, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0x3f, 0xff, 0xfd, 0xff, 0xe3, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0x8f, 0xff, 0xf9, 0xff, 0xf8, 0xff, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xe0, 0xff, 0xf3, 0xff, 0xfe, 0x0f, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xfe, 0x0f, 0xc7, 0xff, 0xff, 0xe0, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xe0, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

const unsigned char arrow [] PROGMEM = {
	0x00, 0xff, 0xff, 0x00, 0x00, 0x80, 0x01, 0x00, 0x00, 0x80, 0x01, 0x00, 0x00, 0x80, 0x01, 0x00, 
	0x00, 0x80, 0x01, 0x00, 0xff, 0x80, 0x01, 0xff, 0x60, 0x00, 0x00, 0x06, 0x1c, 0x00, 0x00, 0x38, 
	0x03, 0x80, 0x01, 0xc0, 0x00, 0x70, 0x0e, 0x00, 0x00, 0x0e, 0x70, 0x00, 0x00, 0x01, 0x80, 0x00
};


const char daysOfWeek[7][12] = {
  "Minggu",
  "Senin",
  "Selasa",
  "Rabu",
  "Kamis",
  "Jum'at",
  "Sabtu"
};

int8_t alarm_hour,alarm_minute;

bool online_mode = false;

// RTC_DS1307 rtc;

RTC_DS3231 rtc;



//================================================================================//
//================================================================================//
//================================================================================//
//===============THIS SECTION WILL BE USED FOR GLOBAL VARIABLES===================//
//================================================================================//
//================================================================================//
//================================================================================//

void setup()
{
  esp_task_wdt_deinit();
  client.setInsecure();

  while(!EEPROM.begin(64))
  {
    delay(1000);
  }  

  alarm_hour=EEPROM.read(0);
  alarm_minute=EEPROM.read(1);

  Serial.begin(115200);

  pinMode(16,OUTPUT);
  pinMode(17,INPUT_PULLUP);

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  display.display();

  //INITIALISE BMP280
  while(!bmp.begin())
  {
    delay(100);
  }
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */

  //INITIALISE AHT20
  while(!aht.begin())
  {
    delay(100);
  }
  
  while(!rtc.begin())
  {
    delay(500);
  }

  WiFi.begin(ssid, password);
  uint8_t connect_wifi_attempt=0;

  while (WiFi.status() != WL_CONNECTED && connect_wifi_attempt<15) {
    const String String_wifi="CONNECTING WIFI";
    uint8_t xPos,yPos;
    int16_t x,y;
    uint16_t textWidth, textHeight; 
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.getTextBounds(String_wifi, 0, 0, &x, &y, &textWidth, &textHeight);
    xPos=(SCREEN_WIDTH-textWidth)/2;
    yPos=(SCREEN_HEIGHT-textHeight)/2;
    display.setCursor(xPos, yPos);
    display.print(String_wifi);
    display.getTextBounds(".", 0, 0, &x, &y, &textWidth, &textHeight);
    display.setCursor(xPos+(textWidth*connect_wifi_attempt),yPos+textHeight);
    display.print(".");
    display.display();
    connect_wifi_attempt+=1;
    delay(1000);
  }
  
 
  
  if(connect_wifi_attempt<=10)
  {
    online_mode=true;
    display.clearDisplay();
    const String String_wifi="WIFI CONNECTED";
    uint8_t xPos,yPos;
    int16_t x,y;
    uint16_t textWidth, textHeight; 
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.getTextBounds(String_wifi, 0, 0, &x, &y, &textWidth, &textHeight);
    xPos=(SCREEN_WIDTH-textWidth)/2;
    yPos=(SCREEN_HEIGHT-textHeight)/2;
    display.setCursor(xPos, yPos);
    display.print(String_wifi);
    display.display();

    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    if(!getLocalTime(&timeinfo))
    {
      Serial.println("Failed to obtain time");
      return;
    }

    rtc.adjust(DateTime(timeinfo.tm_year+1900, timeinfo.tm_mon+1, timeinfo.tm_mday, timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec ));
  }
  else
  {
    display.clearDisplay();
    const String String_wifi="WIFI NOT FOUND";
    uint8_t xPos,yPos;
    int16_t x,y;
    uint16_t textWidth, textHeight; 
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.getTextBounds(String_wifi, 0, 0, &x, &y, &textWidth, &textHeight);
    xPos=(SCREEN_WIDTH-textWidth)/2.5;
    yPos=(SCREEN_HEIGHT-textHeight)/2;
    display.setCursor(xPos, yPos);
    display.print(String_wifi);
    display.getTextBounds("Proceed Using RTC", 0, 0, &x, &y, &textWidth, &textHeight);
    xPos=(SCREEN_WIDTH-textWidth)/2;
    yPos=(yPos+textHeight+3);
    display.setCursor(xPos, yPos);
    display.print("Proceed Using RTC");
    display.display();
  }  
  delay(3000);


  display.clearDisplay();
  // display.setCursor(0,0);
  // display.setTextSize(1);
  // display.setTextColor(SSD1306_WHITE);
  // display.println("hello world");
  display.display();

  // delay(3000);

  lcd.init();
  lcd.createChar(0,satu);
  lcd.createChar(1,dua);
  lcd.createChar(2,tiga);
  lcd.createChar(3,empat);
  lcd.createChar(4,lima);
  lcd.createChar(5,enam);
  lcd.createChar(6,tujuh);
  lcd.createChar(7,delapan);
  lcd.home();        
  lcd.backlight();

  xTaskCreatePinnedToCore
  (
    Task1code,   /* Task function. */
    "Task1",     /* name of task. */
    10000,       /* Stack size of task */
    NULL,        /* parameter of the task */
    1,           /* priority of the task */
    &Task1,      /* Task handle to keep track of created task */
    0            /* pin task to core 0 */ 
  );               

  
}


void print_number_to_lcd_16x2_i2c(int number, int column)
{      
  switch(number)
  {
    case 0:
      lcd.setCursor(column,0);
      lcd.print(" ");
      lcd.print(" ");
      lcd.setCursor(column,1);
      lcd.write(3);
      lcd.write(2);
      break;
    case 1:
      lcd.setCursor(column,0);
      lcd.print(" ");
      lcd.write(5);
      lcd.setCursor(column,1);
      lcd.print(" ");
      lcd.write(5);
      break;
    case 2:
      lcd.setCursor(column,0);
      lcd.write(0);
      lcd.write(2);
      lcd.setCursor(column,1);
      lcd.write(3);
      lcd.write(1);
      break;
    case 3:
      lcd.setCursor(column,0);
      lcd.write(0);
      lcd.write(2);
      lcd.setCursor(column,1);
      lcd.write(1);
      lcd.write(2);
      break;
    case 4:
      lcd.setCursor(column,0);
      lcd.write(7);
      lcd.write(1);
      lcd.setCursor(column,1);
      lcd.print(" ");
      lcd.write(5);
      break;
    case 5:
      lcd.setCursor(column,0);
      lcd.write(7);
      lcd.write(0);
      lcd.setCursor(column,1);
      lcd.write(1);
      lcd.write(2);
      break;
    case 6:
      lcd.setCursor(column,0);
      lcd.write(7);
      lcd.write(0);
      lcd.setCursor(column,1);
      lcd.write(6);
      lcd.write(2);
      break;
    case 7:
      lcd.setCursor(column,0);
      lcd.write(0);
      lcd.write(4);
      lcd.setCursor(column,1);
      lcd.print(" ");
      lcd.write(5);        
      break;
    case 8:
      lcd.setCursor(column,0);
      lcd.write(3);
      lcd.write(2);
      lcd.setCursor(column,1);
      lcd.write(3);
      lcd.write(2);
      break;
    case 9:
      lcd.setCursor(column,0);
      lcd.write(3);
      lcd.write(2);
      lcd.setCursor(column,1);
      lcd.write(1);
      lcd.write(4);
      break;
    
  }
}

void get_online_Time_dates(uint8_t *hour, uint8_t *minutes, uint8_t *seconds, uint16_t *year, uint8_t *month, uint8_t *dates, String *day)
{
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  // Serial.println(timeinfo.tm_hour);
  // Serial.println(timeinfo.tm_min);
  // Serial.println(timeinfo.tm_sec);

  *hour = timeinfo.tm_hour;
  *minutes = timeinfo.tm_min;
  *seconds = timeinfo.tm_sec;
  *year = timeinfo.tm_year+1900;
  *month = timeinfo.tm_mon+1;
  *dates = timeinfo.tm_mday;
  *day = daysOfWeek[timeinfo.tm_wday];
  
}

void get_offline_Time_dates(uint8_t *hour, uint8_t *minutes, uint8_t *seconds, uint16_t *year, uint8_t *month, uint8_t *dates, String *day)
{
  DateTime now=rtc.now();
  *hour = now.hour();
  *minutes = now.minute();
  *seconds = now.second();
  *year = now.year();
  *month = now.month();
  *dates = now.day();
  *day = daysOfWeek[now.dayOfTheWeek()];
}


void print_clock(uint8_t hour, uint8_t minutes, uint8_t seconds)
{
  uint8_t a,b,c,d,e,f;
  lcd.setCursor(0, 0);
  // lcd.print(String(hour)+":"+String(minutes)+":"+String(seconds));

  a=hour/10;
  b=hour%10;
  print_number_to_lcd_16x2_i2c(a,0);
  print_number_to_lcd_16x2_i2c(b,2);
  lcd.setCursor(4,0);
  lcd.print(":");
  lcd.setCursor(4,1);
  lcd.print(":");
  c=minutes/10;
  d=minutes%10;
  print_number_to_lcd_16x2_i2c(c,5);
  print_number_to_lcd_16x2_i2c(d,7);
  e=seconds/10;
  f=seconds%10;
}

uint8_t suhu11=0,kelembapan=0;

void show_temp_and_humid()
{
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);

  float aht20, bmp20, averageTemp;
  
  aht20=temp.temperature;
  bmp20=bmp.readTemperature();
  averageTemp=(aht20+bmp20)/2;
  suhu11=averageTemp;
  kelembapan=humidity.relative_humidity;

  lcd.setCursor(10,0);
  lcd.print(String(averageTemp)+"C");
  lcd.setCursor(10,1);
  lcd.print(String(humidity.relative_humidity)+"%");
}

void print_date_times_to_oled_i2c(uint16_t year, uint8_t month, uint8_t dates, String day)
{
  uint8_t xPos,yPos;
  int16_t x,y;
  uint16_t textWidth, textHeight;
  String combine_all_dates = (String(dates)+"-"+String(month)+"-"+String(year));

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(2);
  display.getTextBounds(day, 0, 0, &x, &y, &textWidth, &textHeight);
  xPos = (SCREEN_WIDTH-textWidth)/2;
  yPos = (SCREEN_HEIGHT-textHeight-5)/2.5;
  display.setCursor(xPos, yPos);
  display.print(day);
  display.getTextBounds(combine_all_dates, 0, 0, &x, &y, &textWidth, &textHeight);
  xPos = (SCREEN_WIDTH-textWidth)/2;
  yPos = (yPos+textHeight+3);
  display.setCursor(xPos, yPos);
  display.print(combine_all_dates);
  display.display();

  
}

void Buzzer_beep(){
  for(int x=0; x<4; x++){
    digitalWrite(16,HIGH);
    delay(50);
    digitalWrite(16,LOW);
    delay(50);
  }
}

//====GLOBAL VARIABLE====//

bool easter_egg = false;
String global_chat_id;

//====GLOBAL VARIABLE====//

void handleNewMessages(int numNewMessages) {
  for (int i = 0; i < numNewMessages; i++) {
    String chatId = String(bot.messages[i].chat_id);
    String text = bot.messages[i].text;

    Serial.println("Received command: " + text);

    // Handle specific commands
    if (text == "/start") 
    {
      String welcomeMsg = "SELAMAT DATANG DI BOT PENDETEKSI SUHU!\n";
      welcomeMsg += "Gunakan /suhu untuk mendapatkan temperatur suhu ruangan anda";
      bot.sendMessage(chatId, welcomeMsg, "");
    } 
    else if (text == "/suhu") 
    {
      digitalWrite(16,HIGH);
      delay(50);
      digitalWrite(16,LOW);
      delay(50);
      String statusMsg = "suhu: "+String(suhu11)+"\n"+"kelembapan: "+String(kelembapan);
      bot.sendMessage(chatId, statusMsg, "");
    } 
    else if(text == "/easteregg")
    {
      global_chat_id = chatId;
      easter_egg = true;
    }
    else {
      bot.sendMessage(chatId, "maap ges aku gak tau perintah yang kamu kirim nich cobain /suhu deh", "");
    }
  }
}



// #define DS3231_I2C_ADDR 0x68
// #define DS3231_TEMPERATURE_ADDR 0x11

// float getTemperature() {
//   Wire.beginTransmission(DS3231_I2C_ADDR);
//   Wire.write(DS3231_TEMPERATURE_ADDR);
//   Wire.endTransmission();
  
//   Wire.requestFrom(DS3231_I2C_ADDR, 2);
//   byte msb = Wire.read();
//   byte lsb = Wire.read() >> 6;
  
//   float temperature = msb + (lsb * 0.25);
//   return temperature;
// }

//================================================================================//
//============THE SECTION BELOW WILL BE USED FOR GLOBAL VARIABLES=================//
//================================================================================//

uint32_t last_value1=0,last_value2=0,last_value3=0,last_value4=0; //for millis interval timer

bool Menu_Opened = false;

bool is_the_alarm_ringging = false;

bool is_it_the_next_day_reset = true;

uint32_t timer1=0,timer2=0;

String rick_roll[]={
  "Never Gonna Give You UP",
  "Never Gonna Let You Down",
  "Never Gonna Run Around",
  "And Dessert You"
};

uint8_t iteration_easter_egg = 0;




//================================================================================//
//============THE SECTION ABOVE WILL BE USED FOR GLOBAL VARIABLES=================//
//================================================================================//

void loop()// main loop for core 0
{
  uint8_t hour,minutes,seconds,dates,month;
  uint16_t year;
  String day;


  if (millis() - timer2 > 1000) 
  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    while (numNewMessages) 
    {
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    timer2 = millis();

    if(easter_egg && iteration_easter_egg < 4)
    {
      // bot.sendMessage(chatId, statusMsg, "");
      bot.sendMessage(global_chat_id,rick_roll[iteration_easter_egg], "");
      iteration_easter_egg ++;
    }
    else if(iteration_easter_egg >= 4)
    {
      easter_egg = false;
      iteration_easter_egg = 0;
    }
  }



  if(online_mode)
  {
    get_online_Time_dates(&hour,&minutes,&seconds,&year,&month,&dates,&day);
  }
  else
  {
    get_offline_Time_dates(&hour,&minutes,&seconds,&year,&month,&dates,&day);
  }

  if(hour == 0 && minutes == 0) is_it_the_next_day_reset=true;

  if(alarm_hour == hour && alarm_minute == minutes && is_it_the_next_day_reset) is_the_alarm_ringging=true;
  //
  // else is_the_alarm_ringging = false;

    
  if(millis()-last_value1>=3000)
  {
    last_value1=millis();
    show_temp_and_humid();
    // float tempC = getTemperature();
    // Serial.print("Temperature: ");
    // Serial.print(tempC);
    // Serial.println(" °C");
  }

  if(millis()-last_value2>=6000)
  {
    last_value2=millis();
    print_clock(hour,minutes,seconds);    
  }
  
  if(millis()-last_value3>=6000 && !Menu_Opened)
  {
    last_value3=millis();
    if(online_mode)
    {
      last_value2=millis();
      get_online_Time_dates(&hour,&minutes,&seconds,&year,&month,&dates,&day);
      print_clock(hour,minutes,seconds);
    }
    else
    {
      get_offline_Time_dates(&hour,&minutes,&seconds,&year,&month,&dates,&day);
      print_clock(hour,minutes,seconds);
    }
    print_date_times_to_oled_i2c(year,month,dates,day);
    Serial.println(String(dates)+"-"+String(month)+"-"+String(year));
  }


  // if(millis()-last_value3>=600 && hour==7 && minutes==30 && seconds<=60)
  // {
  //   Buzzer_beep();    
  // }
  // esp_task_wdt_reset();
}


void Print_menu()
{
  uint8_t menu_index = 1 , open_menu = 0 ;
  String text[] = {
    "Menu",
    "Ganti Alarm",
    "Ganti Waktu RTC",
    "Exit",
    "Easter Egg"
  };


  // uint8_t alarm_hour=EEPROM.read(0),alarm_minute=EEPROM.read(1);
  // alarm_hour=EEPROM.read(0);
  // alarm_minute=EEPROM.read(1);
  uint8_t Rtc_hour=0, Rtc_minute=0;

  int16_t x,y;
  int16_t x1, y1;
  uint16_t textWidth, textHeight;

  bool iteration_done=false;
  uint32_t last_time_button_pressed=0;
  bool reset=false;

  uint8_t change_step=0;
  int8_t hour1=0, hour2=0;
  int8_t minute1=0, minute2=0;
  String alarm_clock;
  float arrowmultiply=0.2;
  
  while(Menu_Opened)
  {
    uint16_t duration=0;
    uint8_t xPos=0,yPos=0;
    uint8_t button_command=0;
    

    if(!digitalRead(17) && iteration_done)
    {      
      last_time_button_pressed=millis();
      while(!digitalRead(17))
      {
        duration=millis()-last_time_button_pressed;
        Serial.println(duration);
        if(duration>1000)
        {
          if(open_menu==0)
          {
            open_menu=menu_index;
                    
          }
          else 
          {
            button_command=3;
          }
          iteration_done=false;
          
          Serial.println("select button pressed");
          display.clearDisplay();
          display.display();
          break;
        }
      }
      if(duration<=150 && iteration_done)
      {
        if(open_menu==0)
        {
          menu_index+=1;
        }
        else
        {
          button_command=1;
        }        
        iteration_done=false;       
      }
      else if(duration>150 && iteration_done)
      {
        if(open_menu==0)
        {
          menu_index-=1;
        }
        else
        {
          button_command=2;
        }      
        iteration_done=false;
      }
      while(!digitalRead(17))
      {
        yield();
      }
    }

    if(menu_index<1)
    {
      menu_index=4;
    }
    else if (menu_index>4) {
      menu_index=1;
    }

    Serial.println("menu index: ");
    Serial.println(menu_index);
    Serial.println("open menu: ");
    Serial.println(open_menu);
    Serial.println("reset: ");
    Serial.println(reset);

    // delay(100);
    yield();
    if(digitalRead(17) && !iteration_done || reset>0)
    {
      if(reset=1)
      {
        reset=false;
      }
         
      switch (open_menu) 
      {
        case 0:
          
          x=0;
          y=0;
          
          display.clearDisplay();
          display.setTextColor(SSD1306_WHITE);
          display.setTextSize(1);
          display.getTextBounds(text[x],0,0,&x1,&y1,&textWidth,&textHeight);
          xPos=(SCREEN_WIDTH-textWidth)/2;
          display.setCursor(xPos,y);
          display.print("MENU");
          yPos=(yPos+textHeight);
          display.drawLine(0,yPos,128,yPos,SSD1306_WHITE);
          // display.display();

          //=======================================satu==================================
          x+=1;
          y+=12;
          display.getTextBounds(text[x], 0, 0, &x1, &y1, &textWidth, &textHeight);
          xPos = (SCREEN_WIDTH - textWidth) / 2;
          if(x==menu_index)
          {
            display.fillRect(14, y-1, 100, textHeight+1, SSD1306_WHITE);
            display.setTextColor(SSD1306_BLACK);
          }
          else
          {
            display.fillRect(14, y-1, 100, textHeight+1, SSD1306_BLACK);
            display.setTextColor(WHITE);
          }
          display.setCursor(xPos,y);
          display.print(text[x]);
          // display.display();

          //=======================================dua==================================
          x+=1;
          y+=12;
          display.getTextBounds(text[x], 0, 0, &x1, &y1, &textWidth, &textHeight);
          xPos = (SCREEN_WIDTH - textWidth) / 2;
          if(x==menu_index)
          {
            display.fillRect(14, y-1, 100, textHeight+1, SSD1306_WHITE);
            display.setTextColor(SSD1306_BLACK);
          }
          else
          {
            display.fillRect(14, y-1, 100, textHeight+1, SSD1306_BLACK);
            display.setTextColor(WHITE);
          }
          display.setCursor(xPos,y);
          display.print(text[x]);
          // display.display();

          //=======================================tiga==================================
          x+=1;
          y+=12;
          display.getTextBounds(text[x], 0, 0, &x1, &y1, &textWidth, &textHeight);
          xPos = (SCREEN_WIDTH - textWidth) / 2;
          if(x==menu_index)
          {
            display.fillRect(14, y-1, 100, textHeight+1, SSD1306_WHITE);
            display.setTextColor(SSD1306_BLACK);
          }
          else
          {
            display.fillRect(14, y-1, 100, textHeight+1, SSD1306_BLACK);
            display.setTextColor(WHITE);
          }
          display.setCursor(xPos,y);
          display.print(text[x]);
          // display.display();

          //=======================================empat==================================
          x+=1;
          y+=12;
          display.getTextBounds(text[x], 0, 0, &x1, &y1, &textWidth, &textHeight);
          xPos = (SCREEN_WIDTH - textWidth) / 2;
          if(x==menu_index)
          {
            display.fillRect(14, y-1, 100, textHeight+1, SSD1306_WHITE);
            display.setTextColor(SSD1306_BLACK);
          }
          else
          {
            display.fillRect(14, y-1, 100, textHeight+1, SSD1306_BLACK);
            display.setTextColor(WHITE);
          }
          display.setCursor(xPos,y);
          display.print(text[x]);
          display.display();

        break;
        case 1:

        
          if(alarm_hour>24) alarm_hour=0;
          else if(alarm_hour<0) alarm_hour=24;

          if(alarm_minute>59) alarm_minute=0;
          else if(alarm_minute<0) alarm_minute=59;
          display.clearDisplay();
          hour1=alarm_hour/10;
          hour2=alarm_hour%10;
          minute1=alarm_minute/10;
          minute2=alarm_minute%10;
          alarm_clock=String(hour1)+String(hour2)+":"+String(minute1)+String(minute2);
          display.setTextSize(3);
          display.setTextColor(SSD1306_WHITE);
          display.getTextBounds(alarm_clock, 0, 0, &x1, &y1, &textWidth, &textHeight);
          xPos=(SCREEN_WIDTH-textWidth)/2;
          yPos=(SCREEN_HEIGHT-textHeight)/2;
          display.setCursor(xPos , yPos);
          display.print(alarm_clock);
          display.drawBitmap((xPos+textWidth-18)*arrowmultiply,yPos-textHeight/2,arrow,32,12,SSD1306_WHITE);
          display.display();
          if(button_command==1 && change_step == 0)
          {
            alarm_hour+=1;
          }
          else if(button_command==2 && change_step == 0)
          {
            alarm_hour-=1;
          }
          else if(button_command==1 && change_step == 1)
          {
            alarm_minute+=1;
          }
          else if(button_command==2 && change_step == 1)
          {
            alarm_minute-=1;
          }
          else if(button_command==3)
          {
            arrowmultiply=0.8;
            change_step+=1;
            
          }
          if(change_step>1)
          {
            arrowmultiply=0.2;
            open_menu=0; 
            change_step=0;
            if(EEPROM.read(0)!=alarm_hour)
            {
              EEPROM.write(0, alarm_hour);
              EEPROM.commit();
            } 

            if(EEPROM.read(1)!=alarm_minute) 
            {
              EEPROM.write(1, alarm_minute);
              EEPROM.commit();
            }   
            is_it_the_next_day_reset=true;
                    
          }
          reset=true;



        break;
        case 2:

          if(Rtc_hour>24) Rtc_hour=24;
          else if(Rtc_hour<0) Rtc_hour=0;

          if(Rtc_minute>59) Rtc_minute=59;
          else if(Rtc_minute<0) Rtc_minute=0;
          display.clearDisplay();
          hour1=Rtc_hour/10, hour2=Rtc_hour%10;
          minute1=Rtc_minute/10, minute2=Rtc_minute%10;
          alarm_clock=String(hour1)+String(hour2)+":"+String(minute1)+String(minute2);
          display.setTextSize(3);
          display.setTextColor(SSD1306_WHITE);
          display.getTextBounds(alarm_clock, 0, 0, &x1, &y1, &textWidth, &textHeight);
          xPos=(SCREEN_WIDTH-textWidth)/2;
          yPos=(SCREEN_HEIGHT-textHeight)/2;
          display.setCursor(xPos , yPos);
          display.print(alarm_clock);
          display.drawBitmap((xPos+textWidth-18)*arrowmultiply,yPos-textHeight/2,arrow,32,12,SSD1306_WHITE);
          display.display();
          if(button_command==1 && change_step == 0)
          {
            alarm_hour+=1;
          }
          else if(button_command==2 && change_step == 0)
          {
            alarm_hour-=1;
          }
          else if(button_command==1 && change_step == 1)
          {
            alarm_minute+=1;
          }
          else if(button_command==2 && change_step == 1)
          {
            alarm_minute-=1;
          }
          else if(button_command==3)
          {
            arrowmultiply=0.8;
            change_step+=1;
            
          }
          if(change_step>1)
          {
            arrowmultiply=0.2;
            open_menu=0; 
            change_step=0;
            // rtc.adjust(DateTime(timeinfo.tm_year+1900, timeinfo.tm_mon+1, timeinfo.tm_mday, Rtc_hour, Rtc_minute, 0 ));
                    
          }
          reset=true;

        break;

        case 3:
          display.clearDisplay();
          display.setTextColor(SSD1306_WHITE);
          display.setTextSize(2);
          display.getTextBounds("EXITING", 0, 0, &x1, &y1, &textWidth, &textHeight);
          display.setCursor((SCREEN_WIDTH-textWidth)/2, (SCREEN_HEIGHT-textHeight)/2);
          display.display();
          delay(2000);
          Menu_Opened=false;      
          display.clearDisplay();
          display.display();         
          

        break;
        
        case 4:
          display.clearDisplay();      
          display.drawBitmap(0,0,dick,SCREEN_WIDTH,SCREEN_HEIGHT,SSD1306_WHITE);
          display.display();
          delay(2000);
          display.clearDisplay();
          display.display();
          open_menu=0;
          reset=true;
          // reset_menu(4, 0);
          
          
        break;

      }
      // if(reset!=0 && reset<3)
      // {
      //   reset+=1;
      // }

      iteration_done=true;
    }
    // if(reset>2 && reset!=0)
    // {
    //   reset=0;
    // }
    
    yield();

  }
  
}

void print_alarm_snooze_time(uint32_t time_right_now, uint32_t first_time_reference, uint8_t snooze_time_in_minute )
{
  uint8_t xpos,ypos;
  int16_t x1, y1;
  uint16_t textWidth, textHeight;

  uint16_t total_seconds_left = ((6000*snooze_time_in_minute)-(time_right_now-first_time_reference))/1000;

  uint8_t minutes_left = total_seconds_left/60;
  uint8_t seconds_left =total_seconds_left%60;
  

  String combine_string_snooze_timer = String(minutes_left/10)+String(minutes_left%10)+":"+String(seconds_left/10)+String(seconds_left%10);
  
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(3);
  display.getTextBounds(combine_string_snooze_timer,0,0,&x1,&y1,&textWidth,&textHeight);
  xpos=(SCREEN_WIDTH-textWidth)/2;
  ypos=(SCREEN_HEIGHT-textHeight)/2;
  display.setCursor(xpos, ypos);
  display.print(combine_string_snooze_timer);
  display.display();
}


//================================================================================//
//============THE SECTION BELOW WILL BE USED FOR GLOBAL VARIABLES=================//
//================================================================================//



uint32_t on_core1_last_value0=0,on_core1_last_value1=0;
uint32_t last_time_pressed=0;


//================================================================================//
//============THE SECTION ABOVE WILL BE USED FOR GLOBAL VARIABLES=================//
//================================================================================//


void Task1code( void * pvParameters )//core 1
{
  uint32_t on_core1_last_value2;
  uint8_t snooze_time = 2;
    
  for(;;)//main loop for core 1
  {
    //========================//
    on_core1_last_value0=millis();
    //========================//

    while(is_the_alarm_ringging)
    {
      uint32_t now_time_reference=millis();
      if(now_time_reference-on_core1_last_value2>1000)
      {
        print_alarm_snooze_time(now_time_reference, on_core1_last_value0, snooze_time);
        on_core1_last_value2=now_time_reference;
        if(now_time_reference - on_core1_last_value0 >= 1000*60*snooze_time)
        {        
          is_it_the_next_day_reset=false;         
          is_the_alarm_ringging=false;
          break;        
        }
      }
      
    
      
      if(!digitalRead(17))
      {
        is_it_the_next_day_reset=false;         
        is_the_alarm_ringging=false;

        while(!digitalRead(17)){}
        delay(100);
        break;
      } 

      if(millis()-on_core1_last_value1 >= 800) 
      {
        on_core1_last_value1=millis();
        Buzzer_beep();
      }
    }
    
    

    if(!digitalRead(17) && !Menu_Opened)
    { 
      Serial.println("buka menu ditekan");
      delay(100);     
      if(digitalRead(17))
      {
        Serial.println("buka menu dilepas");
        Menu_Opened=true;
        display.clearDisplay();
        display.display();
        Print_menu();
        delay(100);
      }      
    }
  }
}
