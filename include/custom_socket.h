#ifndef CUSTOM_SOCKET_H
#define CUSTOM_SOCKET_H

#include "custom_server.h"
#include "custom_client.h"
#include "dummy_sock.h" 


template<class Tx,class Rx>class CustomSocket
{
    public:
        bool initSocket(const SockSetup& setup);
        bool sendData(const Tx& txframe);
        bool recieveData(Rx& rxframe);
        bool reConnect(char* ip);
        void deleteSocket();
    private:
        std::unique_ptr<CustomSockInterface<Tx,Rx>> sock_;

};

template<class Tx, class Rx>
bool CustomSocket<Tx,Rx>::initSocket(const SockSetup& setup)
{
    switch(setup.type)
    {
        case SockType::eServer:
            sock_ = std::make_unique<CustomServer<Tx,Rx>>();
            break;
        case SockType::eClient:
            sock_ = std::make_unique<CustomClient<Tx,Rx>>();
            break;
        case SockType::eDummy:
            sock_ = std::make_unique<DummySock<Tx,Rx>>();
            break;
        default:
            sock_ = std::make_unique<CustomServer<Tx,Rx>>();
            break;
    }

    std::vector<char> ip(setup.ip.begin(), setup.ip.end());
    ip.push_back('\0');

    return sock_->initSocket(ip.data(), setup.port);
}

template<class Tx, class Rx>
bool CustomSocket<Tx,Rx>::sendData(const Tx& txframe)
{
    return sock_->sendData(txframe);
}

template<class Tx, class Rx>
bool CustomSocket<Tx,Rx>::recieveData(Rx& rxframe)
{
    return sock_->recieveData(rxframe);
}

template<class Tx, class Rx>
bool CustomSocket<Tx,Rx>::reConnect(char* ip)
{
    return sock_->reConnect(ip);
}

template<class Tx, class Rx>
void CustomSocket<Tx,Rx>::deleteSocket()
{
    sock_->deleteSocket();
}

#endif