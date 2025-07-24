#ifndef CUSTOM_CLIENT_H
#define CUSTOM_CLIENT_H

#include "custom_socket_interface.h"

template<class Tx, class Recv> class CustomClient : public CustomSockInterface<Tx,Recv>
{
    public:
        bool initSocket(char* ip, const int& port);
        bool sendData(const Tx& txframe);
        bool recieveData(Recv& rxframe);
        bool reConnect(char* ip);
        void deleteSocket();
    private:
        int server_fd_,sockfd_;
};

#endif

template<class Tx, class Recv>
bool CustomClient<Tx,Recv>::initSocket(char* ip, const int& port)
{   
    int ret;
    struct sockaddr_in server_addr;
    sockfd_ = socket(AF_INET,SOCK_STREAM,0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip);
    ret = connect(sockfd_,(struct sockaddr*)&server_addr,sizeof(server_addr));    
    
    return (ret < 0) ? 0 : 1;
}

template<class Tx,class Recv>
bool CustomClient<Tx,Recv>::sendData(const Tx& txframe)
{
    int ret = send(sockfd_,&txframe,sizeof(Tx),0);
    return (ret > 0) ? 1 : 0;
}

template<class Tx,class Recv>
bool CustomClient<Tx,Recv>::recieveData(Recv& rxframe)
{
    int ret = 1;
    std::vector<unsigned char> buffer(sizeof(Recv));
    size_t received = 0;
    while (received < sizeof(Recv)) 
    {
        ssize_t bytes = read(sockfd_, buffer.data() + received, sizeof(Recv) - received);
        if (bytes <= 0) 
        {
            ret = -1;
            break;
        }
        received += bytes;
    }

    std::memcpy(&rxframe, buffer.data(), sizeof(Recv));
    return (ret > 0) ? 1 : 0;
}

template<class Tx,class Recv>
bool CustomClient<Tx,Recv>::reConnect(char* ip)
{
    return true;
}

template<class Tx,class Recv>
void CustomClient<Tx,Recv>::deleteSocket()
{
    close(sockfd_);
}