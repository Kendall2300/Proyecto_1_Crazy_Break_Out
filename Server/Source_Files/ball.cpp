/**
 * @file ball.cpp
 * @authors Kendall Martinez Carvajal (kendallmc@estudiantec.cr) && Daniel Urena Lopez (dlurena24@estudiantec.cr)
 * @brief
 * Este codigo recibe las ordenes de game para crear la bola cada vez que game lo requiera
 * @version 1.0
 *
 * @copyright Copyright (c) 2021
 */
#include "ball.hpp"
#include "painter.hpp"
#include "wall.hpp"


Ball::Ball(): x_(Wall::WIDTH / 2),
	      y_(Wall::HEIGHT - 400),
          surpRand(0),
	      vx_(0),
	      vy_(150)
          {}

/**
* @brief
* Este metodo le pide a painter que elija el color de la bola y dibujarla
*
*/
void Ball::draw(Painter &p) const
{
  p.setColor(Painter::WHITE);
  p.ball(x_, y_);
}

/**
 * @brief
 * Este metodo establece parametros para cuando la bola rebota en objetos
 *
 */
void Ball::tick(Force f)
{
  float x = f.x;
  float y = f.y;
  const float LIM = 1;
  if (x > LIM)
    x = LIM;
  if (x < -LIM)
    x = -LIM;
  if (y > LIM)
    y = LIM;
  if (y < -LIM)
    y = -LIM;

  vx_ += 12 * x;
  vy_ += 20 * y;
  x_ += vx_ * DT;
  y_ += vy_ * DT;
}

/**
 * @brief
 * Este metodo que elije la velocidad aleatoria de la bola cuando explota un brick sorpresa
 *
 */
int Ball::surpRoller()
{
    srand(time(NULL));
    surpRand = rand() % 3 + (-3);
}
