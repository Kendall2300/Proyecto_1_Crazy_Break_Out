#include "ball.hpp"
#include "painter.hpp"
#include "wall.hpp"

Ball::Ball(): x_(Wall::WIDTH / 2),
	      y_(Wall::HEIGHT - 400),
          surpRand(0),
	      vx_(0),
	      vy_(150)
          {}

void Ball::draw(Painter &p) const
{
  p.setColor(Painter::WHITE);
  p.ball(x_, y_);
}

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

int Ball::surpRoller()
{
    srand(time(NULL));
    surpRand = rand() % 3 + (-3);
}
