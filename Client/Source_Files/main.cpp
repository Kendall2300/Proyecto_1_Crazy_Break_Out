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

void first_menu(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(2,0,0);
    glRasterPos3f(250,20,0);
    char Game_Tittle[]="Bienvenido al menu principal de: Crazy_Breakout";
    for(int i=0; i < strlen(Game_Tittle); i++){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, Game_Tittle[i]);
    }
    glRasterPos3f(300,550,0);
    char To_Exit[]="Para salir del juego presiona la tecla: K ";
    for(int j=0; j < strlen(Game_Tittle); j++){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, To_Exit[j]);
    }
    glRasterPos3f(300,275,0);
    char To_Start[]="Para empezar presiona la tecla: X ";
    for(int t=0; t < strlen(Game_Tittle); t++){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, To_Start[t]);
    }
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

void keys(unsigned char key, int,int){
    if (key=='x'){
        timer();
    }
    else if(key=='k'){
        exit(1);
    }
    glutPostRedisplay();
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
        if(msn == "begin"){
            //Llamando al juego base
            glutInit(&argc, argv);
            glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
            glutInitWindowSize(
                    Wall::WIDTH,
                    Wall::HEIGHT);
            glutInitWindowPosition(200, 100);
            glutCreateWindow("Breakout");
            glClearColor(0, 0, 0, 1.0);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(0, Wall::WIDTH, Wall::HEIGHT, 0, -1.0, 1.0);
            glutDisplayFunc(first_menu);
            glutKeyboardFunc(keys);
            glutPassiveMotionFunc(mouse);
            glutMainLoop();
            break;
        }
        client->setMsj(json.c_str()); 
    }
    delete client;
    return 0;
}