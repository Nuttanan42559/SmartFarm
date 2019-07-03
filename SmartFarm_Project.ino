#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <BH1750FVI.h>
#include <SimpleBlynk.h>
//#include <NTPClient.h>
//#include <WiFiUdp.h>

#define BLYNK_PRINT Serial
#define DHTPIN D1
#define DHTTYPE DHT22
//#define Moisture D2
#define ledlight D2
#define pential D4
#define pentialfan D5
#define fan D6
#define N D0
#define P D7
#define K D8

char auth[] = "161a1f66aca443c3856b48747d625d32";
char ssid[] = "SHA256";
char pass[] = "123456789";


//const long utcOffsetInSeconds = 25200;

DHT dht(DHTPIN, DHTTYPE);
BH1750FVI LightSensor(BH1750FVI::k_DevModeContLowRes);
//WiFiUDP ntpUDP;
//NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds); 

BLYNK_WRITE(V1) {
  switch (param.asInt())
  {
    case 1: 
      NPK(1);
      break;
    case 2: 
      NPK(2);
      break;
    case 3: 
      NPK(3);
      break;
    default:
      Serial.println("Unknown item selected");
  }
}

void setup()
{
  Serial.begin(9600);    
  Blynk.begin(auth, ssid, pass, "blynk.honey.co.th", 8080);
  dht.begin();
  LightSensor.begin();  
}

void loop()
{ 
    Blynk.run();
    tempcontrol();
    light();
}

void NPK(int func) {  
  if(func == 1){
    Serial.print("Function 1");
    digitalWrite(N, HIGH);
    delay(8000);
    digitalWrite(P, HIGH);
    delay(5000);
    digitalWrite(K, HIGH);
    delay(5000);
  }
  else if(func == 2){
    Serial.print("Function 2");
    digitalWrite(N, HIGH);
    delay(5000);
    digitalWrite(P, HIGH);
    delay(5000);
    digitalWrite(K, HIGH);
    delay(5000);
  }
  else if(func == 3){
    Serial.print("Function 3");
    digitalWrite(N, HIGH);
    delay(5000);
    digitalWrite(P, HIGH);
    delay(7000);
    digitalWrite(K, HIGH);
    delay(7000);
  }
    
}
void light() {
    uint16_t lux = LightSensor.GetLightIntensity();
    if(lux < 10){
       digitalWrite(ledlight, HIGH);
    }
    else{
      digitalWrite(ledlight, LOW);
    }
}

int tempcontrol() {
    int humidity = dht.readHumidity();            
    int temp = dht.readTemperature();
    Blynk.virtualWrite(V2, humidity);               
    Blynk.virtualWrite(V3, temp);
    if(temp > 30){
      digitalWrite(pential, HIGH);
      digitalWrite(pentialfan, HIGH);
      digitalWrite(fan, HIGH);
    }
    else if(temp < 30){
      digitalWrite(pential, LOW);
      digitalWrite(pentialfan, LOW);
      digitalWrite(fan, LOW);
    }
  
}

