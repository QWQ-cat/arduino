#include <LiquidCrystal_PCF8574.h>
#include "DHT.h"
#define DHTPIN 9 
#define DHTTYPE DHT11
//#define DHTTYPE DHT22   // DHT 22 如果用的是DHT22，就用這行
//#define DHTTYPE DHT21   // DHT 21
LiquidCrystal_PCF8574 lcd(0x27);  // 設定i2c位址，一般情況就是0x27和0x3F兩種
DHT dht(DHTPIN, DHTTYPE);
float v =3.5;
float ssd = 0;
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
  
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C \t");
  Serial.print("Thermal comfort: ");
  Serial.print(ssd);
  Serial.print("\t");
  if(ssd>85){
    Serial.println("Very Hot");
  }else if(ssd<=85&ssd>80){
    Serial.println("Hot");
  }else if(ssd<=80&ssd>76){
    Serial.println("Little Hot");
  }else if(ssd<=76&ssd>71){
    Serial.println("Nice");
  }else if(ssd<=71&ssd>59){
    Serial.println("Nice Weather");
  }else if(ssd<=59&ssd>51){
    Serial.println("Little Cold");
  }else if(ssd<=51&ssd>39){
    Serial.println("Cold");
  }else if(ssd<=39&ssd>=26){
    Serial.println("Very Cold");
  }else if(ssd>26){
    Serial.println("Super Cold");
  }
  
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
  if(ssd>85){
    lcd.print("Very Hot");
  }else if(ssd<=85&ssd>80){
    lcd.print("Hot");
  }else if(ssd<=80&ssd>76){
    lcd.print("Little Hot");
  }else if(ssd<=76&ssd>71){
    lcd.print("Nice");
  }else if(ssd<=71&ssd>59){
    lcd.print("Nice Weather");
  }else if(ssd<=59&ssd>51){
    lcd.print("Little Cold");
  }else if(ssd<=51&ssd>39){
    lcd.print("Cold");
  }else if(ssd<=39&ssd>=26){
    lcd.print("Very Cold");
  }else if(ssd>26){
    lcd.print("Super Cold");
  }
  delay(3000);
} // loop()