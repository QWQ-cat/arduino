/*
 * 本範程式為Arduino結合DHT11和LCD範例程式，由傑森創工提供
 * 
 * 有關LCD的部份，大家可以參考另一篇教學：
 * https://blog.jmaker.com.tw/lcd1602/
 * 
 * 1，請先安裝Adafruit DHT Sensor Library函式庫，可由Arduino IDE裡的「程式管理員」進行安裝
 * 2，請先安裝Adafruit Unified Sensor Library函式庫，可由Arduino IDE裡的「程式管理員」進行安裝
 * 
 * 粉絲團：https://www.facebook.com/jasonshow
 * 傑森創工購物網：https://www.jmaker.com.tw/
 * 傑森創工部落格：https://blog.jmaker.com.tw/
 */
#include <LiquidCrystal_PCF8574.h>
#include "DHT.h"
#define DHTPIN 9 
#define DHTTYPE DHT11
//#define DHTTYPE DHT22   // DHT 22 如果用的是DHT22，就用這行
//#define DHTTYPE DHT21   // DHT 21
LiquidCrystal_PCF8574 lcd(0x3F);  // 設定i2c位址，一般情況就是0x27和0x3F兩種
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  Serial.begin(9600);
  Serial.println("DHTxx test!");
  dht.begin();  //初始化DHT
  
  lcd.begin(16, 2); // 初始化LCD
  
  lcd.setBacklight(255);
  lcd.clear();
  lcd.setCursor(0, 0);  //設定游標位置 (字,行)
  lcd.print("*~ first line.");
  lcd.setCursor(0, 1);
  lcd.print("~* second line.");
} // setup()

void loop()
{
  delay(1000);
  float h = dht.readHumidity();   //取得濕度
  float t = dht.readTemperature();  //取得溫度C
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" *C ");
  
  lcd.clear();
  lcd.setCursor(0, 0);  //設定游標位置 (字,行)
  lcd.print("RH  :");
  lcd.setCursor(7, 0);  
  lcd.print(h);
  lcd.setCursor(14, 0);
  lcd.print("%");

  lcd.setCursor(0, 1);  //設定游標位置 (字,行)
  lcd.print("Temp:");
  lcd.setCursor(7, 1);  
  lcd.print(t);
  lcd.setCursor(13, 1);
  lcd.print((char)223); //用特殊字元顯示符號的"度"
  lcd.setCursor(14, 1);
  lcd.print("C");
 
} // loop()
