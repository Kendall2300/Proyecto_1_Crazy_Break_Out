#include "SocketClient.h"
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

SocketClient* client;


void * clientRun(void * ){
    try{
        client ->conect();
    }catch(string ex){
        cout << ex << endl;
    }
    pthread_exit(NULL);
}
int main(int argc, char **argv){
    client = new SocketClient;
    pthread_t hiloC;
    pthread_create(&hiloC, 0, clientRun, NULL);
    pthread_detach(hiloC);

    string json = "Hola desde el cliente";

    while(1){
        string msn;
        cin >> msn;
        if(msn == "b"){
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
            break;
        }
        client->setMsj(json.c_str()); 
    }
    delete client;
    return 0;
} 