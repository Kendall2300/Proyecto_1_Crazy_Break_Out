/**
 * @file main.cpp
 * @authors Kendall Martinez Carvajal (kendallmc@estudiantec.cr) && Daniel Urena Lopez (dlurena24@estudiantec.cr)
 * @brief
 * Este codigo se enarga de recibir los datos del cliente y de correr toda la logica del juego.
 *
 * @version 1.0
 *
 * @copyright Copyright (c) 2021
 */
#include <sstream>
#include "SocketServer.h"
#include "string.h"
#include "painter.hpp"
#include "wall.hpp"
#include "game.hpp"
#include "GL/glut.h"

using namespace std;
Game game;
/**
 * @brief
 * Este metodo se encarga de crear la pantalla que se muertra al ejecutar el juego, asi mismo muestra el puntaje/score
 * y el contador de cuantas bolas le quedan al usuario
 */
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
    ss<<game.GScore;
    string str = ss.str();
    char const* points=str.c_str();
    for(int i=0; i<strlen(points);i++){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,points[i]);
    }
    glColor3f(2,0,0);
    glRasterPos3f(1100,760,0);
    char Bolas[]="Bolas: ";
    for(int i=0; i < strlen(Bolas); i++){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, Bolas[i]);
    }
    glColor3f(2,0,0);
    glRasterPos3f(1165,760,0);
    stringstream s2;
    s2<<game.ballCounter;
    string str2 = s2.str();
    char const* Balls=str2.c_str();
    for(int i=0; i<strlen(Balls);i++){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,Balls[i]);
    }
    

    glutSwapBuffers();
}
/**
 * @brief
 * Este metodo se encarga de crear el menu que se visualiza antes de acceder al juego, en este puedes elegir que accion tomar
 */
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
/**
 * @brief
 * Este metodo s eencarga de llamara al juego as[i como de llevar la cantidad de fps o ticks por segundo que se llevan
 * a cabo durante la ejecucion
 */
void timer(int = 0)
{
    for (int i = 0; i < 1.0 / 25 / Ball::DT; ++i)
        game.tick();
    display();
    glutTimerFunc(1000 / 25, timer, 0);
}

/**
 * @brief
 * Este metodo se encarga de escuchar los movimientos en x del raton para mover el pedal/barra/paddle.
 * @param x integer que corresponde al valor de x que posee el puntero del mouse.
 */
void mouse(int x, int)
{
    game.setX(x);
}

/**
 * @brief
 * Este metodo se encarga de esuchar cuando el es que una tecla es oprimida para desencadera una reaccion de ser necesaria
 * @param key char que corresponde a la tecla oprimida
 */
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
/**
 * @brief
 * Este metodo se encarga de correr el socket servidor
 * @return
 */
void * serverRun(void *){
    try{
        server->run();
    } catch (string ex){
        cout << ex << endl;
    }
    pthread_exit(NULL);
}


/**
 * @brief
 * Este metodo se encarga de correr y llamar a todos los metodos para ejecutar el programa.
 * @param argc int
 * @param argv char
 * @return int que se encarga de finalizar la ejecucion
 */
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