#include <Wire.h>
#include <LiquidCrystal_I2C.h> 
#include <DHT.h>

#define DHTPIN D6 // Used D6 instead of D5
#define DHTTYPE DHT11  

const int MQ3 = A0; 

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

int threshold; //Declared globally instead of in loop()

void setup() {

  Serial.begin(9600);
  
  lcd.init(); 
  lcd.backlight();

  lcd.print("Hello there");

  dht.begin();

  int mq3Baseline = analogRead(MQ3);
  
  threshold = mq3Baseline/2; //Calculate once
  
}

void loop() {

  int mq3Value = analogRead(MQ3); 

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
     lcd.clear();
     Serial.println("Failed to read from DHT sensor!");
     lcd.print("error");
     return; //Added semicolon
  }

  if(mq3Value < threshold) {
    //Food spoiled code
    lcd.setCursor(0,0);
    lcd.print("the food spolied");

  } else {

    //Code to print fresh food
    lcd.setCursor(0,0);
    lcd.print("food was fresh");
  }

  // Added delays after LCD prints
  lcd.setCursor(0, 1);
  lcd.print("temperature:");  
  lcd.print(t);
  delay(2000);
  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print("humidity:");
  lcd.print(h); 
  delay(2000);
  
}