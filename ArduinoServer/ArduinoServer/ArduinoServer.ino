
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char *ssid = "RC";
const char *password = "12345678";
const int port = 3305;

WiFiUDP udp;

void setup() {
  Serial.begin(9600);

  Serial.println("Configuring access point...");
  
  WiFi.softAP(ssid, password, 3);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  
  udp.begin(port);
  Serial.println("Server started");
}

void loop() {
  int packetSize = udp.parsePacket();
  
  if (packetSize) {
    char buf[packetSize];
    
    Serial.print("Received packet of size ");
    Serial.println(packetSize);
    
    Serial.print("From ");
    IPAddress remoteIp = udp.remoteIP();
    Serial.print(remoteIp);
    
    Serial.print(", port ");
    Serial.println(udp.remotePort());

    int len = udp.read(buf, packetSize);
    if (len > 0) {
      buf[len] = 0;
    }
    
    Serial.println("Contents:");
    Serial.println(buf);
  }
  
}
