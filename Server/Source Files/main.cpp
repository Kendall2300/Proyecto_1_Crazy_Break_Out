#include "SocketServer.h"
#include "Game.h"
#include "State_Menu.h"
#include "string.h"

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

int main(int argc, char **argv){
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

    //Llamando al juego base

    struct Game_Conf conf = {
            //Argumentos
            .argc = argc,
            .argv = argv,

            //Titulo pantalla
            .title = "Crazy_Breakout",

            //Tamaño de la pantalla
            .width = 800,
            .height = 600,

            //Cuadros por segundo (FPS)
            .framerate = 60,

            //Pantalla completa
            .fullscreen = false,

            //Usar un buffer adicional
            .buffer = true,
    };

    if (Game_Init(&conf)){
        Game_Run(STATE_MENU); //Empezando en el menu
    }

    delete server;

    return 0; 
}