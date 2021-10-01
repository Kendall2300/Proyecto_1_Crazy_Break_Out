/**
 * @file painter.cpp
 * @authors Kendall Martinez Carvajal (kendallmc@estudiantec.cr) && Daniel Urena Lopez (dlurena24@estudiantec.cr)
 * @brief
 * Este codigo manipula los metodos creados por el header, para pintar y dibujar los objetos.
 *
 * @version 1.0
 *
 * @copyright Copyright (c) 2021
 */
#include "painter.hpp"
#include <GL/gl.h>
#include <math.h>

/**
 * @brief
 * ESte metodo se encarga de establecer la posicion y dibujar el contorno del objeto.
 * @param x1 int coordenada x1
 * @param y1 int coordenada y1
 * @param x2 int coordenada x2
 * @param y2 int coordenada y2
 */
void Painter::bar(int x1, int y1, int x2, int y2)
{
  glBegin(GL_QUADS);
  glVertex2f(x1, y1);
  glVertex2f(x2, y1);
  glVertex2f(x2, y2);
  glVertex2f(x1, y2);
  glEnd();
}


/**
 * @brief
 * Este metodo dibuja el contorno de la bola y define su ubicacion en x e y
 * @param x int coordenada x
 * @param y int coordenada y
 */
void Painter::ball(int x, int y)
{
  glBegin(GL_POLYGON);
  /*glVertex2f(x + 20, y);
  glVertex2f(x, y + 20);
  glVertex2f(x - 20, y);
  glVertex2f(x, y - 20);*/
  float theta;
  for(int i=0; i<360; i++){
      theta=i*3.142/180;
      glVertex2f(x+15*cos(theta), y+15*sin(theta));
  }
  glEnd();
}

/**
 * @brief
 * Este metodo se encarga de pintar por colores el relleno de los objetos que ya poseen contorno
 * @param color obj Que refiere al color del objeto
 */
void Painter::setColor(Color color)
{
  static const struct
  {
    float r, g, b;
  } colors[] = 
      {
	{ 255, 255, 255 }, // white
	{ 0, 0.9, 0.9 }, // cyan
	{ 0.1, 0.5, 0.8 }, // blue
	{ 0.1, 0.2, 0.5 }, // dark blue
	{ 0.5, 0, 0.8 }, // purple
	{ 0.6, 0.6, 0.6 }, // gray
    { 0.9, 0, 0.9 }, // pink
    { 0, 0, 0 }, // black
      };
  glColor3f(colors[color].r, 
	    colors[color].g, 
	    colors[color].b);
}
