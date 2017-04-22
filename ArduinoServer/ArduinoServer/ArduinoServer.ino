
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#define PWMA D1 
#define PWMB D2
#define DA D3
#define DB D4

const char *ssid = "RC";
const char *password = "12345678";
const int port = 3305;
const int channel = 3;

WiFiUDP udp;

void setup() {
  // Set pins  
  pinMode(PWMA,OUTPUT);
  pinMode(PWMB,OUTPUT);
  pinMode(DA,OUTPUT);
  pinMode(DB,OUTPUT);

  // Start serial
  Serial.begin(9600);
  Serial.println("Configuring access point...");

  // Start Access point on specified channel
  WiFi.softAP(ssid, password, channel);
  IPAddress myIP = WiFi.softAPIP();

  // Debug
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  // Start capture
  udp.begin(port);
  Serial.println("Server started");
}

void loop() {
  int packetSize = udp.parsePacket();
  
  if (packetSize) {
    char buf[packetSize];

    // Debug
    Serial.print("Received packet of size ");
    Serial.println(packetSize);
    Serial.print("From ");
    IPAddress remoteIp = udp.remoteIP();
    Serial.print(remoteIp);
    Serial.print(", port ");
    Serial.println(udp.remotePort());

    int len = udp.read(buf, packetSize);
    if (len > 0) { buf[len] = 0; }

    // Debug
    Serial.println("Contents:");
    Serial.println(buf);
    
    if (strcmp(buf, "w") == 0) { moveForward(); }
    
    if (strcmp(buf, "s") == 0) { moveBackward(); }

    if (strcmp(buf, "a") == 0) { turnLeft(); }
    
    if (strcmp(buf, "d") == 0) { turnRight(); }  
     
    if (strcmp(buf, "b") == 0) { stop(); }
    
  } else { stopMotors(); }
}

void moveForward() {
  digitalWrite(DA,HIGH);    //使直流电机（右）GO
  digitalWrite(DB,HIGH);
  analogWrite(PWMA,255);    //使直流电机（左）GO
  analogWrite(PWMB,255);
}

void moveBackward() {
  digitalWrite(DA,LOW);     //使直流电机（右）GO
  digitalWrite(DB,LOW);
  analogWrite(PWMA,255);    //使直流电机（左）GO
  analogWrite(PWMB,255);
}

void turnLeft() {
  digitalWrite(DA,HIGH);    //使直流电机（右）GO
  digitalWrite(DB,HIGH);
  analogWrite(PWMA,100);    //使直流电机（左）GO
  analogWrite(PWMB,255);
  delay(400);
  
  digitalWrite(DA,HIGH);    //使直流电机（右）GO
  digitalWrite(DB,HIGH);
  analogWrite(PWMA,255);    //使直流电机（左）GO
  analogWrite(PWMB,255);
  delay(400);
}

void turnRight() {
  digitalWrite(DA,HIGH);    //使直流电机（右）GO
  digitalWrite(DB,HIGH);
  analogWrite(PWMA,255);    //使直流电机（左）GO
  analogWrite(PWMB,100);
  delay(400);
  
  digitalWrite(DA,HIGH);    //使直流电机（右）GO
  digitalWrite(DB,HIGH);
  analogWrite(PWMA,255);    //使直流电机（左）GO
  analogWrite(PWMB,255);
  delay(400);
}

void stopMotors() {
  digitalWrite(DA,LOW);     //使直流电机（右）GO
  digitalWrite(DB,LOW);
  analogWrite(PWMA,0);      //使直流电机（左）GO
  analogWrite(PWMB,0);
}

