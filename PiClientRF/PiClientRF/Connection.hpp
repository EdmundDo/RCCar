#ifndef Connection_hpp
#define Connection_hpp

#include <RF24/RF24.h>

class Connection {
public:
    Connection(uint8_t address);
    void sendsig(void *msg, int msgSize);
    
private:
    RF24 radio;                                     // Default CE, CSN pins using BCM
    uint8_t address;                                // Address... usually given in 0x0000000000 format
    
    int init();
};

#endif
