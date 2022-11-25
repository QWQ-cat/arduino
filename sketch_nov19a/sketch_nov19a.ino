#include <LiquidCrystal_PCF8574.h>
#include "DHT.h"
#define DHTPIN 9 
#define DHTTYPE DHT11
//#define DHTTYPE DHT22   // DHT 22 如果用的是DHT22，就用這行
//#define DHTTYPE DHT21   // DHT 21
LiquidCrystal_PCF8574 lcd(0x27);  // 設定i2c位址，一般情況就是0x27和0x3F兩種
DHT dht(DHTPIN, DHTTYPE);
float v =3;
float ssd = 0;
char text ="";
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
  delay(1000);
} // setup()

void loop()
{
  delay(1000);
  float h = dht.readHumidity();   //取得濕度
  float t = dht.readTemperature();  //取得溫度C
  ssd = (1.818*t+18.18)*(0.88+0.002*h)+(t-32)/(45-t)-(3.2*v)+18.2; //計算舒適度指數
  if(ssd>=86){
     text ="Very Hot";
  }else if(ssd<=85&ssd>=80){
     text ="Hot";
  }else if(ssd<=76&ssd>=76){
     text ="Little Hot";
  }else if(ssd<=75&ssd>=71){
     text ="Nice";
  }else if(ssd<=70&ssd>=59){
     text ="Nice Weather";
  }else if(ssd<=58&ssd>=51){
     text ="Little Cold";
  }else if(ssd<=50&ssd>=39){
     text ="Cold";
  }else if(ssd<=38&ssd>=26){
     text ="Very Cold";
  }else{
     text ="Super Cold";
  }
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C \t");
  Serial.print("Thermal comfort: ");
  Serial.println(ssd);

  lcd.clear();
  lcd.setCursor(0, 0);  //設定游標位置 (字,行)
  lcd.print("RH  :");  //Relative Humidity 相對濕度簡寫
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
  delay(3000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SSD :");
  lcd.setCursor(7, 0);
  lcd.print(ssd);
  lcd.setCursor(0, 1);
  lcd.print(text);
  delay(3000);
} // loop()