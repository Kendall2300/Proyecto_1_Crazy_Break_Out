#include "SocketClient.h"

SocketClient::SocketClient(){}

void SocketClient::conect(){
    descriptor = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); 
    if(descriptor < 0){
        cout << "Error al crear el socket" << endl;
    }

    info.sin_family = AF_INET;
    info.sin_addr.s_addr = inet_addr("192.168.0.6");
    info.sin_port = ntohs(4050);
    memset(&info.sin_zero, 0,sizeof(info.sin_zero));
    
    if(connect(descriptor, (sockaddr *)&info, (socklen_t)sizeof(info))){
        cout << "error al conectar con server" << endl;
    }

    cout << "Conectado correctamente" << endl;
    pthread_t hilo;
    pthread_create(&hilo, 0, SocketClient::Controller, (void *)this);
    pthread_detach(hilo);
}

void * SocketClient::Controller(void *obj){
    SocketClient* c = (SocketClient *)obj;
    while(true){
        string message;
        char buffer[1024] = {0};
        while (1){
            memset(buffer, 0, 1024);
            int bytes = recv(c->descriptor, buffer, 1024, 0);
            message.append(buffer, bytes);
            if(bytes <= 0){
                close(c->descriptor);
                pthread_exit(NULL);
            }
            if(bytes < 1024){
                break;
            }
        }
        cout << message << endl;
    }
    close(c->descriptor);
    pthread_exit(NULL);
}

void SocketClient::setMsj(const char *msn){
    send(descriptor, msn, strlen(msn), 0);
}

