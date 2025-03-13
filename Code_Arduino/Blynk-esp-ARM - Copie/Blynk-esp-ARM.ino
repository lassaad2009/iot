 /*************************************************************
BLYNK ESP8266 ARM
MADE BY LASSAAD AKROUT
JSDJERBA 2023
/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

/* Fill-in your Template ID (only if using Blynk.Cloud) */
#define BLYNK_TEMPLATE_ID   "TMPL05KrBdrg"


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "WRxzPFmcgk2uk_wo5XZhOkSFYi6a0TUI";
#define D 50
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "CPFPH";
char pass[] = "20222023";
#include <Servo.h>
 int pos0, pos1, pos2, pos3, pos4;
Servo servo0;
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

void setup()
{
  // Debug console
  Serial.begin(115200);
  servo0.attach(16);  // attaches the servo on GPIO16=D0
  servo1.attach(5);  // attaches the servo on GPIO5=D1
  servo2.attach(4);  // attaches the servo on GPIO4=D2  
  servo3.attach(0);  // attaches the servo on GPIO0=D3
  servo4.attach(2);  // attaches the servo on GPIO2=D4
  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
  pinMode(2, OUTPUT);
}


BLYNK_WRITE(V2) {
 pos2=param.asInt();
 servo2.write(pos2); 
 delay(D);
}
BLYNK_WRITE(V4) {
 pos4=param.asInt();
 servo4.write(pos4); 
 delay(D);
}
BLYNK_WRITE(V5) {
 pos1=param.asInt();
 servo1.write(pos1); 
 delay(D);
}
BLYNK_WRITE(V15) {
 pos0=param.asInt();
 servo0.write(pos0); 
 delay(D);
}
BLYNK_WRITE(V3) {
 pos3=param.asInt();
 servo3.write(pos3); 
 delay(D);
}
BLYNK_WRITE(V0) {
 digitalWrite(2, param.asInt());
}

 
void loop()
{
   Blynk.run();
}
