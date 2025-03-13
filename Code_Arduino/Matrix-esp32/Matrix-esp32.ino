#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

// Uncomment according to your hardware type
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
//#define HARDWARE_TYPE MD_MAX72XX::GENERIC_HW

// Defining size, and output pins
#define MAX_DEVICES 1
#define CS_PIN 5

MD_Parola Display = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

void setup() {
 
  Display.begin();
  Display.setIntensity(2);
  Display.displayClear();
}

void loop() {
  Display.setTextAlignment(PA_CENTER);
  Display.print("2");
  delay(2000);
  
  Display.setTextAlignment(PA_CENTER);
  Display.print("1");
  delay(2000);

  Display.setTextAlignment(PA_CENTER);
  Display.print("0");
  delay(2000);


  Display.setTextAlignment(PA_RIGHT);
  Display.print("/");
  delay(2000);

  Display.setTextAlignment(PA_CENTER);
  //Display.setInvert(true);
  Display.print("M");
  delay(2000);

  Display.setInvert(false);
  delay(2000);
}
