/*#include "SocketServer.h"
#include "string.h"
#include "painter.hpp"
#include "wall.hpp"
#include "game.hpp"
#include <GL/glut.h>


using namespace std;

Game game;
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    Painter p;
    game.draw(p);
    glutSwapBuffers();
}

void timer(int = 0)
{
    for (int i = 0; i < 1.0 / 25 / Ball::DT; ++i)
        game.tick();
    display();
    glutTimerFunc(1000 / 25, timer, 0);
}

void mouse(int x, int)
{
    game.setX(x);
}


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

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(
            Wall::WIDTH,
            Wall::HEIGHT);
    glutInitWindowPosition(100, 780);
    glutCreateWindow("Breakout");
    glClearColor(0, 0, 0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, Wall::WIDTH, Wall::HEIGHT, 0, -1.0, 1.0);
    glutDisplayFunc(display);
    glutPassiveMotionFunc(mouse);
    timer();

    glutMainLoop();

    delete server;

    return 0; 
}*/