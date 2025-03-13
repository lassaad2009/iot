// Load Wi-Fi library
#include <WiFi.h>
int in1=23; int in2=22; int in3=19; int in4=21;
int enA=4; int enB=6;
int sw0=13; int sw1=27; int sw2=14;
int F0=34; int F1=35; int F2=32;
int d1=2000;
// Replace with your network credentials
const char* ssid = "jsdjerba";
const char* password = "Hackerspace";
int E0=0; int E1=0;int E2=0;
// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String output25State = "off";
String output26State = "off";
String output27State = "off";

// Assign output variables to GPIO pins
const int AE0 = 0;
const int AE1 = 4;
const int AE2 = 22;

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

void setup() {
  Serial.begin(115200);
  // Initialize the output variables as outputs
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(sw0, INPUT); pinMode(sw1, INPUT); pinMode(sw2, INPUT);
  pinMode(F0, INPUT); pinMode(F1, INPUT); pinMode(F2, INPUT);
  pinMode(AE0, OUTPUT);
  pinMode(AE1, OUTPUT);
  pinMode(AE2, OUTPUT);
  // Set outputs to LOW
  digitalWrite(AE0, LOW);
  digitalWrite(AE1, LOW);
  digitalWrite(AE2, LOW);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void monter() {
digitalWrite(in1, 1);
digitalWrite(in2, 0);
}

void descendre() {
digitalWrite(in1, 0);
digitalWrite(in2, 1);

}

void stop() {
digitalWrite(in1, 0);
digitalWrite(in2, 0);

}

void loop(){
  
if ((digitalRead(F0)==1)||(E0==1)){ 
  while (digitalRead(sw0)==1)
   {descendre();  } 
}else stop();     

if ((digitalRead(F1)==1)||(E1==1)){ 
  if (digitalRead(sw2)==0){
    while (digitalRead(sw1)==1)
      {descendre();  } } else stop();  }

if ((digitalRead(F1)==1)||(E2==1)){ 
  if (digitalRead(sw0)==0){
    while (digitalRead(sw1)==1)
      {monter();  } } else stop();  }

if ((digitalRead(F2)==1)||(E2==1)){ 
  while (digitalRead(sw2)==1)
   {monter();  } 
}else stop();  
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected() && currentTime - previousTime <= timeoutTime) {  // loop while the client's connected
      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // turns the GPIOs on and off
            if (header.indexOf("GET /26/on") >= 0) {
              Serial.println("GPIO AE1 on");
              output26State = "on";
              E1=1;
              digitalWrite(AE1, HIGH);
            } else if (header.indexOf("GET /26/off") >= 0) {
              Serial.println("GPIO 26 off");
              output26State = "off";
              E1=0;
              digitalWrite(AE1, LOW);
            } else if (header.indexOf("GET /27/on") >= 0) {
              Serial.println("GPIO AE2 on");
              output27State = "on";
              E2=1;
              digitalWrite(AE2, HIGH);
            } else if (header.indexOf("GET /27/off") >= 0) {
              Serial.println("GPIO AE2 off");
              output27State = "off";
              E2=0;
              digitalWrite(AE2, LOW);
            } else if (header.indexOf("GET /25/on") >= 0) {
              Serial.println("GPIO AE0 off");
              output25State = "off";
              Serial.println("GPIO AE0 on");
              E0=1;
              output25State = "on";
              digitalWrite(AE0, HIGH);
            } else if (header.indexOf("GET /25/off") >= 0) {
              digitalWrite(AE0, LOW);
              E0=0;
            }
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");
            
     // Web Page Heading
           // client.println("<body><h2>Formation I.o.T</h2>");
           // client.println("<body><h2>Commande à distance des systemes techniques</h2>");
           // client.println("<body><h1> ASSENCEUR CONNECTE </h1>");
           
           client.println("<body><h1> ASSENCEUR CONNECTE </h1>");
           client.println("<body><h2> Malek ABAAB </h2>");
           client.println("<body><h2> ---------------------------------------------- </h2>");


            // Display current state, and ON/OFF buttons for GPIO 26  
            client.println("<p>Appel Etage 2 - Etat " + output26State + "</p>");
            // If the output26State is off, it displays the ON button       
            if (output26State=="off") {
              client.println("<p><a href=\"/26/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/26/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
               
            // Display current state, and ON/OFF buttons for GPIO 27  
            client.println("<p>Appel Etage 1- Etat " + output27State + "</p>");
            // If the output27State is off, it displays the ON button       
            if (output27State=="off") {
              client.println("<p><a href=\"/27/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/27/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            client.println("</body></html>");

            // Display current state, and ON/OFF buttons for GPIO 25  
            client.println("<p>Appel Etage 0 - Etat  " + output25State + "</p>");
            // If the output25State is off, it displays the ON button       
            if (output25State=="off") {
              client.println("<p><a href=\"/25/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/25/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
