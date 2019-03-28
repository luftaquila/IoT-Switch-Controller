#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <CapacitiveSensor.h>

CapacitiveSensor CS = CapacitiveSensor(4, 5);

char auth[] = "b5e348e34fb44bdf82cf611a8b06567e";
char ssid[] = "Luft Aquila";
char pass[] = "ljhobjokr";

boolean RLY;

void setup()
{
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  RLY = false;

  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  Blynk.run();
  
  long TCH = CS.capacitiveSensorRaw(30);
  if(TCH > 10000)
  {
    if(RLY == true)
    {
      digitalWrite(13, LOW);
      Blynk.virtualWrite(V0, 0);
      RLY = false;
      delay(200);
    }
    else if(RLY == false)
    {
      digitalWrite(13, HIGH);
      Blynk.virtualWrite(V0, 1);
      RLY = true;
      delay(200);
    }
  }
}

BLYNK_WRITE(V0)
{
  int rcv = param.asInt();
  if(rcv == 1)
  {
    digitalWrite(13, HIGH);
    RLY = true;
  }
  else if(rcv == 0)
  {
    digitalWrite(13, LOW);
    RLY = false;
  }
}

BLYNK_CONNECTED()
{
  Blynk.syncVirtual(V0);
}

BLYNK_APP_CONNECTED()
{
  if(RLY == true)
    Blynk.virtualWrite(V0, 1);
  else if(RLY == false)
    Blynk.virtualWrite(V0, 0);
}
