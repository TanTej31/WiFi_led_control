#include <Arduino.h>
#include<WiFi.h>
unsigned long int timeInterval = 2000;
//int n;
int flag = LOW;
int ledPin = 2;
const char* ssid = "TanX";
const char* password = "boys$hostel";
void WifiInit()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid,password);
  Serial.print("Connecting to WiFi");
  while(WiFi.status()!= WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.print("IP ADDR: ");
  Serial.println(WiFi.localIP());
  digitalWrite(ledPin,HIGH);
  delay(1000);
  digitalWrite(ledPin,LOW);


}
void setup() 
{
  Serial.begin(115200);
  pinMode(ledPin,OUTPUT);
  Serial.println("Getting Started....");
  WifiInit();
  Serial.println("Setting Up..");
}

void loop() 
{
  int i;
  /*Serial.println("Starting Scan:..");
  n = WiFi.scanNetworks();*/
  unsigned long int prevtime = 0;
  unsigned long int currentTime =millis();
  if(WiFi.status() == WL_CONNECTED)
  {
    digitalWrite(ledPin,HIGH);
    delay(100);
    digitalWrite(ledPin,LOW);
    delay(100);
  }
  else if((WiFi.status() != WL_CONNECTED) && (currentTime - prevtime > timeInterval))
  {
    flag = HIGH;
    digitalWrite(ledPin,flag);
    Serial.println("Restarting in ");
    for(i = 1;i<4;i++)
    {
      Serial.print(i);
      Serial.print(" ");
      delay(1000);
    }
    ESP.restart();
  }
  flag = LOW;
  /*if(n == 0)
  {
    Serial.println("No Nearby Network");
  }
  else
  {
  Serial.print("No. ");
  Serial.print("SSID  ");
  Serial.print("RSSI ");
  Serial.println(" ");
  for(i = 0;i<n;i++)
  {
    Serial.print(i+1);
    Serial.print("  ");
    Serial.print(WiFi.SSID(i));
    Serial.print("  ");
    Serial.print(WiFi.RSSI(i));
    Serial.println(" ");
    delay(100);
  }
  }*/
}
