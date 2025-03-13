#include <WiFi.h>
const char* ssid     = "jsdjerba";
const char* password = "Hackerspace";
const char* host = "education.didamind.cloud";
const char* API_KEY = "DM664511676493037";
String line;
String Etat_LED0,Etat_LED1, Etat_LED2, Etat_LED3, Etat_LED4; 
const int LED0 =  2;
const int LED1 =  12;
const int LED2 =  14;
const int LED3 =  27;
const int LED4 =  26;

void setup()
{
    Serial.begin(115200);
    //delay(10);
    pinMode(LED0,OUTPUT);
    pinMode(LED1,OUTPUT);
    pinMode(LED2,OUTPUT);
    pinMode(LED3,OUTPUT);
    pinMode(LED4,OUTPUT);
    // Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(100);
    }
    Serial.println(WiFi.localIP());
}

int value = 0;
void loop()
{
    delay(100);
    ++value;
    line.reserve(8192);
    WiFiClient client;
    const int httpPort = 80;
    if (!client.connect(host, httpPort)) {
    }
  String url = "/led.php";
    url += "?api_key=";
    url += API_KEY;
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n\r\n");
    unsigned long timeout = millis();
    while (client.available() == 0) {
        if (millis() - timeout > 5000) {
          //  Serial.println(">>> Client Timeout !");
            client.stop();
            return;
        }
    }
    while(client.available()) {
        char c = client.read();
        line = line+c;
        //Serial.print(c);
        //if (line.endsWith("LED=")){
        //  line="";
       // }
        if (line.endsWith("LED0=1")){
          Etat_LED0="1";
          Serial.println("LED0 ON");
        }
         if (line.endsWith("LED0=0")){
          Etat_LED0="0";
         Serial.println("LED0 Off");
        }
        if (line.endsWith("LED1=1")){
          Etat_LED1="1";
         Serial.println("LED1 On");
        }
         if (line.endsWith("LED1=0")){
          Etat_LED1="0";
          Serial.println("LED1 off");
        }
        if (line.endsWith("LED2=1")){
          Etat_LED2="1";
        }
         if (line.endsWith("LED2=0")){
          Etat_LED2="0";
        }
        if (line.endsWith("LED3=1")){
          Etat_LED3="1";
        }
         if (line.endsWith("LED3=0")){
          Etat_LED3="0";
        }
        if (line.endsWith("LED4=1")){
          Etat_LED4="1";
        }
         if (line.endsWith("LED4=0")){
          Etat_LED4="0";
        }
        //Serial.print(line);
        //Serial.print("ETAT_LED1=" + Etat_LED1);
        
    }
    // test sur etat LED
    if(Etat_LED0 =="0"){
      digitalWrite(LED0,0);
    }
    if(Etat_LED0 =="1"){
      digitalWrite(LED0,1);
    }
    if(Etat_LED1 =="0"){
      digitalWrite(LED1,0);
    }
    if(Etat_LED1 =="1"){
      digitalWrite(LED1,1);
    }
    if(Etat_LED2 =="0"){
      digitalWrite(LED2,0);
    }
    if(Etat_LED2 =="1"){
      digitalWrite(LED2,1);
    }
    if(Etat_LED3 =="0"){
      digitalWrite(LED3,0);
    }
    if(Etat_LED3 =="1"){
      digitalWrite(LED3,1);
    }
    if(Etat_LED4 =="0"){
      digitalWrite(LED4,0);
    }
    if(Etat_LED4 =="1"){
      digitalWrite(LED4,1);
    }

}
