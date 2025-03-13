 /*************************************************************
MADE BY LASSAAD AKROUT
JSDJERBA 2023
/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

/* Fill-in your Template ID (only if using Blynk.Cloud) */
#define BLYNK_TEMPLATE_ID   "TMPLZzz3zcD-"


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "smvN190KKU80ZT2fHcJR63FNF_PeUmt4";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "CPFPH";
char pass[] = "20222023";


void setup()
{
  // Debug console
  Serial.begin(115200);
  pinMode(2, OUTPUT);
  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

}


BLYNK_WRITE(V0) {
  digitalWrite(2, param.asInt());
}


 
void loop()
{
  Blynk.run();
}
