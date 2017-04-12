#include "Connection.hpp"

#include <wiringPi.h>
#include <iostream>
#include <string.h>
using namespace std;

int main(int argc, const char *argv[]) {
    
    wiringPiSetupPhys();
    
    pinMode(29, INPUT);
    pullUpDnControl(29, PUD_DOWN);
    
    pinMode(31, INPUT);
    pullUpDnControl(31, PUD_DOWN);
    
    pinMode(32, INPUT);
    pullUpDnControl(32, PUD_DOWN);
    
    pinMode(33, INPUT);
    pullUpDnControl(33, PUD_DOWN);
    
    pinMode(35, INPUT);
    pullUpDnControl(35, PUD_DOWN);
    
    pinMode(37, INPUT);
    pullUpDnControl(37, PUD_DOWN);
    
    Connection server("192.168.6.102", "3305");
    
    while(true) {
        if(digitalRead(29) == HIGH) {
            char *msg = "Hello";
            server.sendsig(msg, strlen(msg));
        } else if(digitalRead(31) == HIGH) {
            char *msg = "World!";
            server.sendsig(msg, strlen(msg));
        } else if(digitalRead(32) == HIGH) {
            char *msg = "How";
            server.sendsig(msg, strlen(msg));
        } else if(digitalRead(33) == HIGH) {
            char *msg = "Are";
            server.sendsig(msg, strlen(msg));
        } else if(digitalRead(35) == HIGH) {
            char *msg = "You";
            server.sendsig(msg, strlen(msg));
        } else if(digitalRead(37) == HIGH) {
            char *msg = "Today";
            server.sendsig(msg, strlen(msg));
        }
    }
    
    return 0;
}
