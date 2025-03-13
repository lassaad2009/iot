//Mohamed Helal
/*************************************************************

  This is a simple demo of sending and receiving some data.
  Be sure to check out other examples!
 *************************************************************/

/* Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID "TMPLunPhMhke"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "3zs_0x7TiSaUJo9jaaJT8kvo0YtyRtuV"
//Ce programme est réalisé par Lassaad AKROUT
/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "med";
char pass[] = "123456789";
int valvp1 = 14;


#define DHTPIN 5          // What digital pin we're connected to

// Uncomment whatever type you're using!
#define DHTTYPE DHT11     // DHT 11
DHT dht(DHTPIN, DHTTYPE);


BlynkTimer timer;
/*
// This function is called every time the device is connected to the Blynk.Cloud
BLYNK_CONNECTED()
{
  // Change Web Link Button message to "Congratulations!"
  Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
  Blynk.setProperty(V3, "onImageUrl",  "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
  Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}*/

// This function sends Arduino's uptime every second to Virtual Pin 2.
void connect()
{
  WiFi.begin(ssid, pass);             // Connect to the network
  Serial.print("Connecting to ");
  Serial.print(ssid); Serial.println(" ...");

  while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
    delay(1000);
    Serial.print(".");
  }
  Serial.println('\n');
  Serial.println("Connection established!");  
}
void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V7, millis() / 1000);
}

BLYNK_WRITE(V0)
{
  int Led2 = param.asInt(); // assigning incoming value from pin V1 to a variable
  Serial.println(Led2);
  digitalWrite(valvp1, Led2);
}
/*
BLYNK_WRITE(V1)
{
  int ev1 = param.asInt(); // assigning incoming value from pin V1 to a variable
  digitalWrite(12, ev1);
}

BLYNK_WRITE(V2)
{
  int ev2 = param.asInt(); // assigning incoming value from pin V1 to a variable
  digitalWrite(13, ev2);
}

BLYNK_WRITE(V3)
{
  int ev3 = param.asInt(); // assigning incoming value from pin V1 to a variable
  digitalWrite(14, ev3);
}
*/
void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Serial.println("temp : ");
  Serial.println(t);
  Serial.println("hum : ");
  Serial.println(h);
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, t);
  Blynk.virtualWrite(V6, h);
}

void SoilSensor()
{
  float s = analogRead(A0);

  Blynk.virtualWrite(V7, s);
 
}

void setup()
{
  // Debug console
  Serial.begin(115200);
  connect();
  pinMode(2, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(14, OUTPUT);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // You can also specify server:
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, IPAddress(192,168,1,100), 8080);
   dht.begin(); 
  // Setup a function to be called every second 
  timer.setInterval(1000L, sendSensor);
  timer.setInterval(1000L, myTimerEvent);
  timer.setInterval(1000L , SoilSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
}
