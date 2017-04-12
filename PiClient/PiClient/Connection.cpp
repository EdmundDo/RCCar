#include "Connection.hpp"

#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

Connection::Connection(char *ip, char *port) : ip(ip), port(port) {
    init();
}

int Connection::init() {
    int retStatus, connStatus;
    std::string error;
    
    addrinfo serverInfo, *server;
    memset(&serverInfo, 0, sizeof serverInfo);
    
    serverInfo.ai_family = AF_INET;
    serverInfo.ai_socktype = SOCK_DGRAM;
    serverInfo.ai_flags = AI_PASSIVE;
    
    if((retStatus = getaddrinfo(ip, port, &serverInfo, &server)) == -1) {
        error = gai_strerror(retStatus);
    }
    
    std::cout << "Retrieved server: " << retStatus << " " << error << std::endl;
    
    std::cout << "Opening connection..." << std::endl;
    
    // Opens a socket
    if((sfd = socket(server->ai_family, server->ai_socktype, server->ai_protocol)) == -1) {
        std::cout << "Failed to create socket." << std::endl;
        return -1;
    }
    
    std::cout << "Connecting..." << std::endl;
    
    // Establishes connection
    if((connStatus = connect(sfd, server->ai_addr, server->ai_addrlen)) == -1) {
        std::cout << "Failed to connect." << std::endl;
        return -1;
    }
    
    std::cout << "Connection established. Begin transmitting." << std::endl;
    
    freeaddrinfo(server);
    
    return 0;
}

void Connection::sendsig(void *msg, int msgSize) {
    send(sfd, msg, msgSize, 0);
}
