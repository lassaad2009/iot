 /*************************************************************
MADE BY LASSAAD AKROUT
JSDJERBA 2023
/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

/* Fill-in your Template ID (only if using Blynk.Cloud) */
#define BLYNK_TEMPLATE_ID   "TMPLZzz3zcD-"


#include <WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "smvN190KKU80ZT2fHcJR63FNF_PeUmt4";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "CPFPH";
char pass[] = "20222023";

#define RightMotorSpeed 5
#define RightMotorDir   0 
#define LeftMotorSpeed  4
#define LeftMotorDir    2

int x = 50;
int y = 50;
int Speed;

int minRange = 312;
int maxRange = 712;

int minSpeed = 150;
int maxSpeed = 1020;
int noSpeed = 0;

void setup()
{
  // Debug console
  Serial.begin(115200);
  pinMode(2, OUTPUT);
  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
  pinMode(RightMotorSpeed, OUTPUT);
  pinMode(LeftMotorSpeed, OUTPUT);
  pinMode(RightMotorDir, OUTPUT);
  pinMode(LeftMotorDir, OUTPUT);

  digitalWrite(RightMotorSpeed, LOW);
  digitalWrite(LeftMotorSpeed, LOW);
  digitalWrite(RightMotorDir, HIGH);
  digitalWrite(LeftMotorDir,HIGH);
}
// Get the joystick values
BLYNK_WRITE(V2) {
  x = param[0].a0sInt();
}
BLYNK_WRITE(V3) {
  y = param[0].asInt();
}
BLYNK_WRITE(V1) {
  Speed = param.asInt();
}


void smartcar() {
  if (y > 70) {
    carForward();
    Serial.println("carForward");
  } else if (y < 30) {
    carBackward();
    Serial.println("carBackward");
  } else if (x < 30) {
    carLeft();
    Serial.println("carLeft");
  } else if (x > 70) {
    carRight();
    Serial.println("carRight");
  } else if (x < 70 && x > 30 && y < 70 && y > 30) {
    carStop();
    Serial.println("carstop");
  }
}    
void loop()
{
  Blynk.run();
  smartcar();// Call the main function
}

/**************Motor movement functions Lassaad****************/
void carForward() {
    digitalWrite(RightMotorDir,HIGH); 
    digitalWrite(LeftMotorDir,HIGH);
    analogWrite(RightMotorSpeed,Speed);
    analogWrite(LeftMotorSpeed,Speed);
}
void carBackward() {
    digitalWrite(RightMotorDir,LOW);
    digitalWrite(LeftMotorDir,LOW);
    analogWrite(RightMotorSpeed,Speed);
    analogWrite(LeftMotorSpeed,Speed);
 }
void carLeft() {
    digitalWrite(RightMotorDir,HIGH);
    digitalWrite(LeftMotorDir,HIGH);
    analogWrite(RightMotorSpeed,Speed);
    analogWrite(LeftMotorSpeed,noSpeed);

}
void carRight() {
    digitalWrite(RightMotorDir,HIGH);
    digitalWrite(LeftMotorDir,HIGH);
    analogWrite(RightMotorSpeed,noSpeed);
    analogWrite(LeftMotorSpeed,Speed);
}
void carStop() {
    analogWrite(RightMotorSpeed,noSpeed);
    analogWrite(LeftMotorSpeed,noSpeed);
}
