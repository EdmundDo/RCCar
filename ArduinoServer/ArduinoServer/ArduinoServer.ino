
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <WiFiServer.h>

const char *ssid = "RC";
const char *password = "12345678";

WiFiServer server(3305);

void setup() {
  Serial.begin(9600);
  Serial.println();
  Serial.println("Configuring access point...");
  
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid, password, 3);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  
  server.begin();
  Serial.println("Server started");
}

void loop() {
  WiFiClient client = server.available();

  if(!client) {
    return;
  }
  
  IPAddress clientIP = client.remoteIP();
  Serial.print("Client IP: ");
  Serial.println(clientIP);

  char command = client.read();
  Serial.println(command);
    
  if(command == 'w') {
    Serial.println("W was pressed");
  } else if (command == 'a') {
    Serial.println("A was pressed");
  } else if (command == 'd') {
    Serial.println("D was pressed");
  } else if (command == 's') {
    Serial.println("S was pressed");
  } else {
    Serial.println("Received something");
  }
  
}
