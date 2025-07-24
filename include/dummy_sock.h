#ifndef DUMMY_SOCK_H
#define DUMMY_SOCK_H

#include "custom_socket_interface.h"

template<class Tx, class Recv> 
class DummySock : public CustomSockInterface<Tx,Recv>
{
    public:
        bool initSocket(char* ip, const int& port) {return true;}
        bool sendData(const Tx& txframe) {return true;}
        bool recieveData(Recv& rxframe) {return true;}
        bool reConnect(char* ip) {return true;}
        void deleteSocket() {return ;}
    private:
        int server_fd_,sockfd_;

};

#endif