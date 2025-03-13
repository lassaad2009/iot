

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

#define BLYNK_AUTH_TOKEN "smvN190KKU80ZT2fHcJR63FNF_PeUmt4" //

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "jsdjerba";//
char pass[] = "Hackerspace";//


void setup() {
  Serial.begin(115200);
   pinMode(2, OUTPUT);
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  delay(10);

}

BLYNK_WRITE(V0) {
digitalWrite(2, param.asInt());
    }

    

void loop() {
  Blynk.run();
}
