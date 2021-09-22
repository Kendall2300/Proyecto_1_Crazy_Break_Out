#include "SocketClient.h"

SocketClient* client;


void * clientRun(void * ){
    try{
        client ->conect();
    }catch(string ex){
        cout << ex << endl;
    }
    pthread_exit(NULL);
}
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
        }
        client->setMsj(json.c_str());
    }
    delete client;
    return 0;
}