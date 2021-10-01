/**
 * @file SocketClient.h
 * @authors Kendall Martinez Carvajal (kendallmc@estudiantec.cr) && Daniel Urena Lopez (dlurena24@estudiantec.cr)
 * @brief
 * Este codigo es la definicion de los atributos y metodos del SocketCLient.
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



