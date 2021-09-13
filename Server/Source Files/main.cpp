#include "SocketServer.h"

using namespace std;

SocketServer* server;
void * serverRun(void *){
    try{
        server->run();
    } catch (string ex){
        cout << ex << endl;
    }
    pthread_exit(NULL);
}

int main(){
    server = new SocketServer;
    pthread_t hiloS;
    pthread_create(&hiloS, 0, serverRun, NULL);
    pthread_detach(hiloS);

    string json = "Hola desde el server";
    while(1){
        string msn;
        cin >> msn;
        if(msn == "salir"){
            break;
            
        }
        server->setMsj(json.c_str());
    }
    delete server;

    return 0; 
}