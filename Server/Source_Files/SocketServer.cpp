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
    if(bind(descriptor, (sockaddr *)&info, (socklen_t)sizeof(info)) < 0) {
        return false;
    }
    listen(descriptor, 4);
    return true;


}

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
        cout << message << endl;
    }
    close(data->descriptor);
    pthread_exit(NULL);
}

void SocketServer::setMsj(const char *msn) {
    for(int i = 0; i < clients.size(); i++){
        send(clients[i], msn, strlen(msn), 0);
    }
}