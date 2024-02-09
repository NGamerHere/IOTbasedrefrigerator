#define BLYNK_PRINT Serial 

#define BLYNK_TEMPLATE_ID "TMPL3c0rEMyu0"
#define BLYNK_TEMPLATE_NAME "tester"
#define BLYNK_AUTH_TOKEN "UaZj0zPTJrreEcW5i3mfpd_pXPmaGpYf"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

char auth[] = "UaZj0zPTJrreEcW5i3mfpd_pXPmaGpYf"; // Your Blynk Auth Token
char ssid[] = "IQOO neo 6"; // Wifi SSID
char pass[] = "datta3232"; // Wifi Password

#define DHTPIN D4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

void sendSensor(){
  float h = dht.readHumidity();
  float t = dht.readTemperature(); 
 
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Serial.print("Temp "); 
Serial.println(t);
  Blynk.virtualWrite(V5, h); // Virtual Pin V5 for Humidity
  Blynk.virtualWrite(V6, t); // Virtual Pin V6 for Temperature  
}

void setup(){
  
  Serial.begin(9600);
  
  Blynk.begin(auth, ssid, pass);

  dht.begin();

  timer.setInterval(1000L, sendSensor); // Send sensor data every 1 second
 
}

void loop(){
 
  Blynk.run(); 
  timer.run();
}