/**
 * @file SocketServer.h
 * @authors Kendall Martinez Carvajal (kendallmc@estudiantec.cr) && Daniel Urena Lopez (dlurena24@estudiantec.cr)
 * @brief
 * Este codigo se encarga de establecer los atributos y metodos, para el socket del servidor.
 *
 * @version 1.0
 *
 * @copyright Copyright (c) 2021
 */
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
//    string clientUsername;
//    string clientIp;
//    string clientPuerto;
//    int clientInfoCounter;

    bool create_socket();
    bool bind_kernell();
    static void* clientController(void* obj);

};



