#include "custom_socket.h"

// define any type of data to be transmitted/recieved
typedef struct
{
    int data;
    char s;

}__attribute__((__packed__))SockTx;

typedef struct
{
    double ack;

}__attribute__((__packed__))SockRx;

int main()
{
    // Init the socket object
    std::unique_ptr<CustomSocket<SockTx,SockRx>> sock = std::make_unique<CustomSocket<SockTx,SockRx>>();
    SockSetup setup;
    // specify the socket ip port and type
    setup.ip = "127.0.0.1";
    setup.port = 1234;
    setup.type = SockType::eClient;

    // init the connection
    sock->initSocket(setup);

    SockTx tx;
    SockRx rx;

    tx.data = 1;
    tx.s = 'a';

    // Send / Recieve loop starts
    while(1)
    {
    
        std::cout<<"DATA SENT: "<<sock->sendData(tx)<<std::endl;
        std::cout<<"DATA RECV: "<<sock->recieveData(rx)<<std::endl;

        std::cout<<"Recieved data: "<<rx.ack<<std::endl;
        usleep(1000000);
    }
}