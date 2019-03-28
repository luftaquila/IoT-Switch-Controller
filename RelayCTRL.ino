#include <CapacitiveSensor.h>
#include <SoftwareSerial.h>

CapacitiveSensor cs_4_7 = CapacitiveSensor(4, 7);

int tx = 2;
int rx = 3;
int relay = 10;
boolean RLY;

SoftwareSerial BT(tx, rx);
String cmd = "";

void setup()
{
  BT.begin(9600);
  pinMode(relay, OUTPUT);
  digitalWrite(relay, HIGH);
  RLY = false;
}

void loop()
{
  while(BT.available())
  {
    char RCV = (char)BT.read();
    cmd += RCV;
    delay(5);
  }
  if(!cmd.equals(""))
  {
    if(cmd == "sw")
    {
      if(RLY == true)
      {
        digitalWrite(relay, HIGH);
        RLY = false;
      }
      else if(RLY == false)
      {
        digitalWrite(relay, LOW);
        RLY = true;
      }
    }
    cmd="";
  }

  long TCH = cs_4_7.capacitiveSensorRaw(30);
  if(TCH > 1000)
  {
    if(RLY == true)
      {
        digitalWrite(relay, HIGH);
        RLY = false;
        delay(200);
      }
      else if(RLY == false)
      {
        digitalWrite(relay, LOW);
        RLY = true;
        delay(200);
      }
  }
  delay(50);
}
