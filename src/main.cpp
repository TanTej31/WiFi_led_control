#include <Arduino.h>
#include<WiFi.h>
#include<WiFiMulti.h>
unsigned long int timeInterval = 2000;
int i,n,m,k;
int flag = LOW;
int ledPin = 2;
const char* ssid1 = "TanX";
const char* password1 = "boys$hostel";
const char* ssid2 = "Intellithink_Office";
const char* password2 = "eCalifornia!22";
void WifiInit()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid1,password1);
  Serial.print("Connecting to WiFi");
  while(WiFi.status()!= WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.print("IP ADDR: ");
  Serial.println(WiFi.localIP());
  Serial.println("Connected");
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
  /*Serial.println("Starting Scan:..");
  n = WiFi.scanNetworks();*/
  unsigned long int prevtime = 0;
  unsigned long int currentTime =millis();
  Serial.print("Connection RSSI: ");
  Serial.println(WiFi.RSSI());
  Serial.print("Connection SSID: ");
  Serial.println(WiFi.SSID());
  if(WiFi.RSSI()<-70  || (WiFi.status() != WL_CONNECTED))
  {
  n = WiFi.scanNetworks();
  for(i = 0;i<n;i++)
  {
    if(WiFi.SSID(i) == "Intellithink_Office")
    {
      m = i;
    }
    else if(WiFi.SSID(i) == "TanX")
    {
      k = i;
    }
  }
  Serial.println(n);
  Serial.println(m);
  Serial.println(WiFi.SSID(m));
  Serial.println(WiFi.SSID(k));
  if(WiFi.RSSI(n) < -70)
  {
    WiFi.disconnect();
    WiFi.begin(ssid2,password2);
    digitalWrite(ledPin,HIGH);
    delay(500);
    digitalWrite(ledPin,LOW);
    Serial.print("Connected to : ");
    Serial.println(WiFi.localIP());
    Serial.println(WiFi.SSID());
  }
  else if(WiFi.RSSI(m)<-70)
  {
    WiFi.disconnect();
    WiFi.begin(ssid1,password1);
    digitalWrite(ledPin,HIGH);
    delay(500);
    digitalWrite(ledPin,LOW);
    Serial.print("Connected to : ");
    Serial.println(WiFi.localIP());
    Serial.println(WiFi.SSID());
  }
  }
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
