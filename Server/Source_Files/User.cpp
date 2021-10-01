/**
 * @file brick.cpp
 * @authors Kendall Martinez Carvajal (kendallmc@estudiantec.cr) && Daniel Urena Lopez (dlurena24@estudiantec.cr)
 * @brief
 * Este codigo recibe y almacena los datos del cliente
 * @version 1.0
 *
 * @copyright Copyright (c) 2021
 */
 #include "User.h"

User::User() {}

/**
 * @brief
 * Este metodo modifica la variable clientUsername
 *
 */
void User::setClientUsername(const string &clientUsername) {
    User::clientUsername = clientUsername;
}

/**
 * @brief
 * Este metodo modifica la variable clientIp
 *
 */
void User::setClientIp(const string &clientIp) {
    User::clientIp = clientIp;
}

/**
 * @brief
 * Este metodo modifica la variable clientPuerto
 *
 */
void User::setClientPuerto(const string &clientPuerto) {
    User::clientPuerto = clientPuerto;
}

/**
 * @brief
 * Este metodo devuelve el bool beginGame
 *
 */
bool User::isBeginGame() const {
    return beginGame;
}

/**
 * @brief
 * Este metodo modifica la variable beginGame
 *
 */
void User::setBeginGame(bool beginGame) {
    User::beginGame = beginGame;
}

int User::getCtr() const {
    return ctr;
}

void User::setCtr(int ctr) {
    User::ctr = ctr;
}

