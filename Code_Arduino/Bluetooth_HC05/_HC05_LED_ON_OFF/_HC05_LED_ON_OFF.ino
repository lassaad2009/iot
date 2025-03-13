#include <SoftwareSerial.h>
int bluetoothTx = 2;  // TX-O pin of bluetooth mate, Arduino D2
int bluetoothRx = 3;  // RX-I pin of bluetooth mate, Arduino D3
int led = 13;
int dataFromBt;
SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);
void setup()
{
  bluetooth.begin(9600);  // Start bluetooth serial at 9600
  pinMode(led, OUTPUT);
}
void loop()
{
  if (bluetooth.available()) // If the bluetooth sent any characters
  {delay(3);
     dataFromBt = bluetooth.read();
   if (dataFromBt == '1') {
      digitalWrite(led, HIGH);
       }
    if (dataFromBt == '0') {
      digitalWrite(led, LOW);
    }
  }
}
