#include "custom_socket.h"


typedef struct
{
    int data;
    char s;

}__attribute__((__packed__))SockRx;

typedef struct
{
    double ack;

}__attribute__((__packed__))SockTx;

int main()
{
    std::unique_ptr<CustomSocket<SockTx,SockRx>> sock = std::make_unique<CustomSocket<SockTx,SockRx>>();
    SockSetup setup;
    setup.ip = "127.0.0.1";
    setup.port = 1234;
    setup.type = SockType::eServer;

    std::cout<<"Waiting for clients to get connected"<<std::endl;
    sock->initSocket(setup);
    std::cout<<"Connected "<<std::endl;
    
    SockTx tx;
    SockRx rx;

    tx.ack = 2;

    while(1)
    {
        std::cout<<"DATA SENT: "<<sock->recieveData(rx)<<std::endl;
        std::cout<<"DATA RECV: "<<sock->sendData(tx)<<std::endl;

        std::cout<<"Recieved data: "<<rx.data<<", "<<rx.s<<std::endl;
        usleep(1000000);
    }
}