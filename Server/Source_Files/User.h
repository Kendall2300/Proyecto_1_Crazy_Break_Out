/**
 * @file brick.h
 * @authors Kendall Martinez Carvajal (kendallmc@estudiantec.cr) && Daniel Urena Lopez (dlurena24@estudiantec.cr)
 * @brief
 * Este codigo es la definicion de los atributos y metodos del user.
 *
 * @version 1.0
 *
 * @copyright Copyright (c) 2021
 */
 #pragma once
#include <string.h>
#include <iostream>
#include <unistd.h>

using namespace std;


class User
{
public:
    string clientUsername;

    void setClientUsername(const string &clientUsername);

    void setClientIp(const string &clientIp);

    void setClientPuerto(const string &clientPuerto);

    string clientIp;
    string clientPuerto;
    bool beginGame;
    int ctr = 0;

    int getCtr() const;

    void setCtr(int ctr);

    bool isBeginGame() const;

    void setBeginGame(bool beginGame);

    User(const string &clientUsername);

    User();

    int getclientInfoCounter();
    int setclientInfoCounter(int num);
};
