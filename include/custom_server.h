#ifndef CUSTOM_SERVER_H
#define CUSTOM_SERVER_H

#include "custom_socket_interface.h"

template<class Tx, class Recv> 
class CustomServer : public CustomSockInterface<Tx,Recv>
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

template<class Tx,class Recv>
bool CustomServer<Tx,Recv>::initSocket(char* ip, const int& port)
{
    int ret;
    struct sockaddr_in server_addr, new_addr;
    socklen_t addr_size;
    server_fd_ = socket(AF_INET,SOCK_STREAM,0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip);
    if(bind(server_fd_,(struct sockaddr*)&server_addr,sizeof(server_addr)) < 0)
    {
        return false;
    }
    ret = listen(server_fd_,1);
    addr_size = sizeof(new_addr);
    sockfd_ = accept(server_fd_,(struct sockaddr*)&new_addr,&addr_size);


    return (ret < 0) ? 0:1;
}

template<class Tx,class Recv>
bool CustomServer<Tx,Recv>::sendData(const Tx& txframe)
{
    int ret = send(sockfd_,&txframe,sizeof(Tx),0);
    return (ret > 0) ? 1 : 0;
}

template<class Tx,class Recv>
bool CustomServer<Tx,Recv>::recieveData(Recv& rxframe)
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
bool CustomServer<Tx,Recv>::reConnect(char* ip)
{
    int ret = -1; 
    char new_ip[50];
    struct sockaddr_in new_addr;
    socklen_t addr_size;
    close(sockfd_);
    ret = listen(server_fd_,1);
    sockfd_ = accept(server_fd_,(struct sockaddr*)&new_addr,&addr_size);
    inet_ntop(AF_INET, (struct sockaddr*)&new_addr.sin_addr, new_ip, sizeof(new_ip));
    strcpy(ip,new_ip);
    return (ret < 0) ? 0 : 1;
    
}

template<class Tx,class Recv>
void CustomServer<Tx,Recv>::deleteSocket()
{
    close(server_fd_);
    close(sockfd_);
}






#endif