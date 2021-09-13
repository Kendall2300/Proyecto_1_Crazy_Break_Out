#pragma once

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <iostream>
#include <pthread.h>
#include <vector>
#include <unistd.h>
#include <arpa/inet.h>

using namespace std;


class SocketClient{
public:
    SocketClient();
    void conect();
    void setMsj(const char* msn);

private:
    int descriptor;
    sockaddr_in info;
    static void* Controller(void* obj);

};



