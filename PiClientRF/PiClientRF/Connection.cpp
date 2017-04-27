#include "Connection.hpp"
#include <RF24/RF24.h>
#include <iostream>

Connection::Connection(uint8_t address) : address(address), radio(RPI_V2_GPIO_P1_15, RPI_V2_GPIO_P1_24, BCM2835_SPI_SPEED_8MHZ) {
    init();
}

int Connection::init() {
    std::cout << "Setting up..." << std::endl;

    radio.begin();
    radio.setChannel(76);                   // Set channel. Change if interference. Must match Arduino.
    radio.setPALevel(RF24_PA_MAX);          // Power usage. Low is RF24_PA_MIN
    radio.setDataRate(RF24_1MBPS);          // Transfer rate. Slower => longer range
    radio.setAutoAck(1);
    radio.enableDynamicPayloads();
    radio.printDetails();

    radio.openWritingPipe(address);
    radio.stopListening();

    std::cout << "Ready to broadcast." << std::endl;

    return 0;
}

void Connection::sendsig(void *msg, int msgSize) {
    if(radio.write(msg, msgSize)) {
        std::cout << "Sent" << std::endl;
    } else {
        std::cout << "Failed" << std::endl;
    }
}

