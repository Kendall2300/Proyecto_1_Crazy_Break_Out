#pragma once

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <iostream>
#include <pthread.h>
#include <vector>
#include <unistd.h>

using namespace std;

struct dataSocket{
    int descriptor;
    sockaddr_in info;
};

class SocketServer{
public:
    SocketServer();
    void run();
    void setMsj(const char* msn);

private:
    int descriptor;
    sockaddr_in info;
    vector<int> clients;

    bool create_socket();
    bool bind_kernell();
    static void* clientController(void* obj);

};



