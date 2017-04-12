#ifndef Connection_hpp
#define Connection_hpp

class Connection {
public:
    Connection(char *ip, char *port);
    void sendsig(void *msg, int msgSize);
    
private:
    int sfd;
    char *ip, *port;
    
    int init();
};

#endif
