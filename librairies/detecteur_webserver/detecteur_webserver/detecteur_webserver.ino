#include <ArduinoJson.h>

#include <moTSerial.h>
#include <moTStorage.h>
#include <moTRTC.h>
#include <moTMPU6050.h>
#include <detecteur.h>

MoTSerial s = MoTSerial();
Detecteur d = Detecteur();
MoTMPU6050 accgyr = MoTMPU6050();

void setup() {

  s.begin(115200);
  s.setVerboseLevel(DEBUG);
  accgyr.init();
  d.init();
}


void loop() {
  d.run();
  delay(1000);
  yield();
}
