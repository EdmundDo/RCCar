#include <wiringPi.h>
#include "Connection.hpp"

#include <iostream>
#include <string>
using namespace std;

int main(int argc, const char *argv[]) {
    
    wiringPiSetupPhys();
    
    if(!bcm2835_init()) {
        printf("GPIO initialization failed!\n");
        return 1;
    }
    
    pinMode(RPI_V2_GPIO_P1_29, BCM2835_GPIO_FSEL_INPT);
    pullUpDnControl(29, PUD_DOWN);
    
    pinMode(RPI_V2_GPIO_P1_31, BCM2835_GPIO_FSEL_INPT);
    pullUpDnControl(31, PUD_DOWN);
    
    pinMode(RPI_V2_GPIO_P1_32, BCM2835_GPIO_FSEL_INPT);
    pullUpDnControl(32, PUD_DOWN);
    
    pinMode(RPI_V2_GPIO_P1_33, BCM2835_GPIO_FSEL_INPT);
    pullUpDnControl(33, PUD_DOWN);
    
    pinMode(RPI_V2_GPIO_P1_35, BCM2835_GPIO_FSEL_INPT);
    pullUpDnControl(35, PUD_DOWN);
    
    pinMode(RPI_V2_GPIO_P1_37, BCM2835_GPIO_FSEL_INPT);
    pullUpDnControl(37, PUD_DOWN);
    
    Connection receiver(0xF0F0F0F0E1);
    
    while(true) {
        if(digitalRead(29) == HIGH) {
            char *msg = "w";
            receiver.sendsig(msg, strlen(msg));
        } else if(digitalRead(31) == HIGH) {
            char *msg = "a";
            receiver.sendsig(msg, strlen(msg));
        } else if(digitalRead(32) == HIGH) {
            char *msg = "s";
            receiver.sendsig(msg, strlen(msg));
        } else if(digitalRead(33) == HIGH) {
            char *msg = "d";
            receiver.sendsig(msg, strlen(msg));
        } else if(digitalRead(35) == HIGH) {
            char *msg = "b";
            receiver.sendsig(msg, strlen(msg));
        } else if(digitalRead(37) == HIGH) {
            char *msg = "h";
            receiver.sendsig(msg, strlen(msg));
        }
        delay(200);
    }
    
    return 0;
}
