#include <sstream>
#include "SocketServer.h"
#include "string.h"
#include "painter.hpp"
#include "wall.hpp"
#include "game.hpp"
#include "GL/glut.h"

using namespace std;
Wall wall;
Game game;
void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    Painter p;
    game.draw(p);
    glColor3f(2,0,0);
    glRasterPos3f(10,760,0);
    char Score[]="Score: ";
    for(int i=0; i < strlen(Score); i++){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, Score[i]);
    }
    
    glColor3f(2,0,0);
    glRasterPos3f(100,760,0);
    stringstream ss;
    ss<<wall.getScore();
    //cout<<wall.getScore()<<endl;
    string str = ss.str();
    char const* points=str.c_str();

    for(int i=0; i<strlen(points);i++){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,points[i]);
    }

    

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
    for(int j=0; j < strlen(To_Exit); j++){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, To_Exit[j]);
    }
    glRasterPos3f(300,275,0);
    char To_Start[]="Para empezar presiona la tecla: X ";
    for(int t=0; t < strlen(To_Start); t++){
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
        exit(0);
    }
    glutPostRedisplay();
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
        if(msn == "b"){
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
        server->setMsj(json.c_str());
    }

    delete server;
    return 0; 
}