#include <SPI.h>
#include "RF24.h"
#include "printf.h"

#define DW 1 
#define DA 2
#define DS 3
#define DD 4

RF24 radio(8,7);  // CE, CSN

void setup() {
  Serial.begin(9600);
  printf_begin();
  
  radio.begin();
  radio.setChannel(76);                       // Change if there is interference
  radio.setPALevel(RF24_PA_MAX);              // Power level. Change to RF24_PA_MIN.
  radio.setDataRate(RF24_1MBPS);              // Speed. Lower, better range.
  radio.setAutoAck(1);
  radio.openReadingPipe(1, 0xF0F0F0F0E1LL);   // Opens address on pipe 1
  radio.enableDynamicPayloads();
  radio.startListening();
  radio.printDetails();                       // Debug
  radio.powerUp();
}

void loop() {
  delay(200);
  
  if (radio.available()) {
    uint8_t len = radio.getDynamicPayloadSize();
    byte data[len];
    
    radio.read(&data, len);
    
    if (len > 0) { data[len] = 0; }

    // Debug
    Serial.println("Contents:");
    
    for(int i = 0; i < 32; i++) {
      Serial.print(data[i]);
      Serial.print(" ");
    }
    Serial.println();
    
    if (data[0] == 'w') { moveForward(); }
    
    if (data[0] == 's') { moveBackward(); }

    if (data[0] == 'a') { turnLeft(); }
    
    if (data[0] == 'd') { turnRight(); }  
     
    if (data[0] == 'b') { stopMotors(); }
    
  } else { stopMotors(); }
}

void moveForward() {
  Serial.println("W pressed");
  digitalWrite(DW,HIGH);    //使直流电机（右）GO
  digitalWrite(DS,LOW);    //使直流电机（右）GO
  digitalWrite(DA,LOW);    //使直流电机（右）GO
  digitalWrite(DD,LOW);    //使直流电机（右）GO
}

void moveBackward() {
  Serial.println("S pressed");
  digitalWrite(DW,LOW);    //使直流电机（右）GO
  digitalWrite(DS,HIGH);    //使直流电机（右）GO
  digitalWrite(DA,LOW);    //使直流电机（右）GO
  digitalWrite(DD,LOW);    //使直流电机（右）GO
}

void turnLeft() {
  Serial.println("A pressed");
  digitalWrite(DW,LOW);    //使直流电机（右）GO
  digitalWrite(DS,LOW);    //使直流电机（右）GO
  digitalWrite(DA,HIGH);    //使直流电机（右）GO
  digitalWrite(DD,LOW);    //使直流电机（右）GO
 
}

void turnRight() {
  Serial.println("D pressed");
  digitalWrite(DW,LOW);    //使直流电机（右）GO
  digitalWrite(DS,LOW);    //使直流电机（右）GO
  digitalWrite(DA,LOW);    //使直流电机（右）GO
  digitalWrite(DD,HIGH);    //使直流电机（右）GO
  

}

void stopMotors() {
  digitalWrite(DW,LOW);    //使直流电机（右）GO
  digitalWrite(DS,LOW);    //使直流电机（右）GO
  digitalWrite(DA,LOW);    //使直流电机（右）GO
  digitalWrite(DD,LOW);    //使直流电机（右）GO
}

