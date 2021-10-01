/**
 * @file main.cpp
 * @authors Kendall Martinez Carvajal (kendallmc@estudiantec.cr) && Daniel Urena Lopez (dlurena24@estudiantec.cr)
 * @brief
 * ESte codigo recibe datos necesarios para conectarse a un servidor donde se hostera una partida del Arkanoid/Breakout
 * el cual utiliza sockets para la conexion entre los dos.
 * @version 1.0
 *
 * @copyright Copyright (c) 2021
 */
#include "SocketClient.h"
#include "cstring"
#include "iostream"

using namespace std;
SocketClient* client;

/**
 * @brief
 * ESte metodo se encarga de ...
 * @return
 */

void * clientRun(void * ){
    try{
        client ->conect();
    }catch(string ex){
        cout << ex << endl;
    }
    pthread_exit(NULL);
}

/**
 * @brief
 * Este es el metodo principal el mismo se encarga de llamar a todas los demas metodos para llevar a cabo los procedimientos
 * requeridos
 *
 * @return int Retorna un valor que termina el programa
 */

int main(){
    client = new SocketClient;
    pthread_t hiloC;
    pthread_create(&hiloC, 0, clientRun, NULL);
    pthread_detach(hiloC);

    string json = "Hola desde el cliente";

    while(1){
        string msn;
        cin >> msn;
        if(msn == "salir"){
            break;
        }else if(msn == "b"){
            //Obteniendo los datos
            cout << "Bienvenido al menu de conexion!" << endl;
            cout << "Por favor ingrese el nombre del usuario"<<endl;
            string user_Name;
            cin >> user_Name;
            cout << "Tu nombre de usuario es: "+user_Name<<endl;
            client->setMsj(user_Name.c_str());
            cout << "Ingresa la Ip del servidor"<<endl;
            string ip;
            cin >> ip;
            cout << "Se usara la siguiente ip: "+ip << endl;
            client->setMsj(ip.c_str());
            cout << "Ingrese el puerto del servidor" << endl;
            string puerto;
            cin >> puerto;
            cout << "EL puerto a utilizar sera el siguiente: "+puerto << endl;
            client->setMsj(puerto.c_str());
            cout << "Pronto te redireccionaremos al menu del juego!!" << endl;
        }
        client->setMsj(json.c_str());
    }
    delete client;
    return 0;
}