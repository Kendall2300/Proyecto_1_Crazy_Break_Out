#include "SocketServer.h"

SocketServer::SocketServer() {}

bool SocketServer::create_socket(){
    descriptor = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); 
    if(descriptor < 0){
        return false;
    }

    info.sin_family = AF_INET;
    info.sin_addr.s_addr = INADDR_ANY;
    info.sin_port = htons(4050);
    memset(&info.sin_zero, 0,sizeof(info.sin_zero));
    return true;

}

bool SocketServer::bind_kernell(){
    if(bind(descriptor, (sockaddr *)&info, (socklen_t)sizeof(info)) < 0){
        return false;
    }
}