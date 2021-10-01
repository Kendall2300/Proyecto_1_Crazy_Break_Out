/**
 * @file pedal.cpp
 * @authors Kendall Martinez Carvajal (kendallmc@estudiantec.cr) && Daniel Urena Lopez (dlurena24@estudiantec.cr)
 * @brief
 * Este codigo manipula los metodos creados por el header, para la barra o pedal del juego.
 *
 * @version 1.0
 *
 * @copyright Copyright (c) 2021
 */
#include "pedal.hpp"
#include "wall.hpp"
#include "painter.hpp"
#include "ball.hpp"

/**
 * @brief
 * Este metodo se encarga de crear al objeto
 */
Pedal::Pedal():
x_(Wall::WIDTH / 2),
surpRand(0)
{}

/**
 * @brief
 * Este metodo se encarga de dibujar el objeto.
 * @param p
 */
void Pedal::draw(Painter &p) const
{
  p.setColor(Painter::CYAN);
  p.bar(x_ - (WIDTH-surpRand) / 2, Wall::HEIGHT - 35,x_ + (WIDTH-surpRand) - (WIDTH-surpRand) / 2, Wall::HEIGHT-30);
}

/**
 * @brief
 * Este metodo se encarga de actualizar la fuerza con que la barra repele a la bola cada ciertos ticks
 * @param ball obj hace referencia la bola
 * @return un valor de tipo force
 */
Force Pedal::tick(const Ball &ball)
{
  float s = ball.x() - x_ + WIDTH / 2;
  if (s >= 0 && s < WIDTH && Wall::HEIGHT - 50 - ball.y() < 0) {
      return Force((Wall::HEIGHT - 50 - ball.y())  * (x_ - ball.x()) / WIDTH, Wall::HEIGHT - 50 - ball.y());
  }
  else
    return Force(0, 0);
}
/**
 * @brief
 * Este metodo se encarga de colocar la posicion x de la barra
 * @param x
 */
void Pedal::setX(int x)
{
  x_ = x;
}
/**
 * @brief
 * Este metodo se encarga de cambiar el tamanio de la barra de forma aleatoria cuando se destruye un bloque sorpresa
 * @return
 */
int Pedal::surpRoller()
{
    srand(time(NULL));
    surpRand = rand() % 50 + (-50);
}
