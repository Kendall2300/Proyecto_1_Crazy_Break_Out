/**
 * @file SocketServer.cpp
 * @authors Kendall Martinez Carvajal (kendallmc@estudiantec.cr) && Daniel Urena Lopez (dlurena24@estudiantec.cr)
 * @brief
 * Este codigo manipula los metodos creados por el header, para el socket del servidor.
 *
 * @version 1.0
 *
 * @copyright Copyright (c) 2021
 */
#include "SocketServer.h"
#include "User.h"

User u;
SocketServer::SocketServer()
//clientInfoCounter(0)
{}

/**
 * @brief
 * Este metodo crea el socket del servidor.
 * @return
 */
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
/**
 * @brief
 * Este metodo se encarga de enlazar el kernell del dispositivo.
 * @return boolean Un valor que define si se pulo enlazar correctamente el kernell
 */
bool SocketServer::bind_kernell(){
    if(bind(descriptor, (sockaddr *)&info, (socklen_t)sizeof(info)) < 0) {
        return false;
    }
    listen(descriptor, 4);
    return true;


}

/**
 * @brief
 * Este metodo se encarga de hacer funcionar al servidor asi como crear el socket y revisar la conexion con el kernell
 *
 */
void SocketServer::run() {
    if(!create_socket())
        throw string("Error al crear el socket");

    if(!bind_kernell())
        throw string("Error al enlazar el kernell");


    bool ack = true;
    while(true){
        dataSocket data;
        socklen_t t = sizeof(data.info);
        cout << "Esperando a conectar con cliente" << endl;
        data.descriptor = accept(descriptor, (sockaddr *)&data.info, &t);
        if(data.descriptor < 0){
            cout << "Error al aceptar cliente" << endl;
            break;
        }
        else{
            clients.push_back(data.descriptor);
            cout << "Cliente conectado" << endl;
            pthread_t hilo;
            pthread_create(&hilo, 0, SocketServer::clientController, (void *)&data);
            pthread_detach(hilo);
            ack = false;
        }
    }
    close(descriptor);
}
/**
 * @brief
 * Este metodo se encarga de controlar los datos de informacion enviados por el ciente en forma de objetos.
 * @param obj Un objeto que se transforma en formato string
 * @return
 */
void * SocketServer::clientController(void *obj){
    dataSocket* data = (dataSocket *)obj;
    while(true){
        string message;
        char buffer[1024] = {0};
        while (1){
            memset(buffer, 0, 1024);
            int bytes = recv(data->descriptor, buffer, 1024, 0);
            message.append(buffer, bytes);
            if(bytes <= 0){
                close(data->descriptor);
                pthread_exit(NULL);
            }
            if(bytes < 1024){
                break;
            }
        }
        int clientInfoCounter = 0;
        string clientUsername;
        string clientIp;
        string clientPuerto;

//        cout << message << " yep" << endl;
        if(u.getCtr() == 0){
            clientUsername = message;
            u.setCtr(2);
            cout << "0"<< clientUsername << endl;
            u.setClientUsername(clientUsername);
        }
        else if(u.getCtr() == 2){
            clientIp = message;
            u.setCtr(4);
            cout << "1"<< clientIp << endl;
            u.setClientIp(clientIp);
        }
        else if(u.getCtr() == 4){
            clientPuerto = message;
            cout << "2"<< clientPuerto << endl;
            u.setClientPuerto(clientPuerto);
            cout << "Listos para iniciar" << endl;
            u.setBeginGame(true);
        }

    }
    close(data->descriptor);
    pthread_exit(NULL);
}

/**
 * @brief
 * Este metodo convierte los mensajes a chars para luego enviarlos al cliente.
 * @param msn char
 */
void SocketServer::setMsj(const char *msn) {
    for(int i = 0; i < clients.size(); i++){
        send(clients[i], msn, strlen(msn), 0);
    }

}