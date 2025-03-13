#include "BluetoothSerial.h"                //Inclure la bibliothèque BluetoothSerial.h
BluetoothSerial SerialBT;                   //Créer une instance de BluetoothSerial nommée SerialBT
const int led = 2;  ;                       //Définir la broche GPIO2 comme sortie et la nommer led
char incomingChar;                          //Déclarer une variable pour stocker le caractère entrant

void setup() {

 pinMode(led, OUTPUT);                      //Initialiser la broche led en tant que sortie
  Serial.begin(115200);                     //Initialiser la communication série à une vitesse de 115200 bauds
  SerialBT.begin("ESP32_Labo_GE");          //Démarrer le service Bluetooth avec le nom "ESP32_Labo_GE"
  Serial.println("Start pairing!");         //Afficher "Start pairing!" sur le port série
}

void loop() {
 if (SerialBT.available()){                 //Vérifier si des données sont disponibles sur le port série Bluetooth
    char incomingChar = SerialBT.read();    //Lire le caractère entrant et le stocker dans la variable incomingChar
    if (incomingChar =='1'){                //Si le caractère entrant est '1'
    digitalWrite(led, HIGH);                //Allumer la LED
    Serial.println("LED ON");               //Afficher "LED ON" sur le port série
  }
    if (incomingChar =='0'){                //Si le caractère entrant est '0'
    digitalWrite(led, LOW);                 //Éteindre la LED
    Serial.println("LED OFF");              //Afficher "LED OFF" sur le port série

  }
 }
}
