#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <CapacitiveSensor.h>

CapacitiveSensor CS = CapacitiveSensor(4, 5);

char auth[] = "b5e348e34fb44bdf82cf611a8b06567e";
char ssid[] = "LUFT-AQUILA";
char pass[] = "rokaFWIf512#";

bool RLY = false;

void setup() {
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  Blynk.run();
  if(CS.capacitiveSensorRaw(1) > 20000) {
    if(RLY) {
      digitalWrite(13, LOW);
      Blynk.virtualWrite(V0, LOW);
    }
    else {
      digitalWrite(13, HIGH);
      Blynk.virtualWrite(V0, HIGH);
    }
    RLY = !RLY;
    delay(500);
  }
}

BLYNK_WRITE(V0) {
  RLY = param.asInt();
  if(RLY) digitalWrite(13, HIGH);
  else    digitalWrite(13, LOW);
}

BLYNK_CONNECTED() { Blynk.syncAll(); }
