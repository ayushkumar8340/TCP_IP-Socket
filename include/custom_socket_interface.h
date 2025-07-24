#ifndef CUSTOM_SOCKET_INTERFACE_H
#define CUSTOM_SOCKET_INTERFACE_H

#include<arpa/inet.h>
#include<stdlib.h>
#include<iostream>
#include<string.h>
#include <sys/socket.h>
#include<unistd.h>
#include<stdint.h>
#include "vector"
#include "unistd.h"
#include <cstring>
#include "memory"

enum SockType
{
    eServer,
    eClient,
    eDummy
};

typedef struct
{
    std::string ip;
    int port;
    SockType type;
    
}SockSetup;

template <class Tx,class Recv> class CustomSockInterface
{
    public:
        virtual ~CustomSockInterface() = default;
        virtual bool initSocket(char* ip,const int& port) = 0;
        virtual bool sendData(const Tx& txframe) = 0;
        virtual bool recieveData(Recv& rxframe) = 0;
        virtual bool reConnect(char* ip) = 0;
        virtual void deleteSocket() = 0;
};

#endif