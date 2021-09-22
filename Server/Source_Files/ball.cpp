#include "ball.hpp"
#include "painter.hpp"
#include "wall.hpp"

Ball::Ball(): x_(Wall::WIDTH / 2),
	      y_(Wall::HEIGHT - 50),
	      vx_(160),
	      vy_(-160){}

void Ball::draw(Painter &p) const
{
  p.setColor(Painter::WHITE);
  p.ball(x_, y_);
}

void Ball::tick(Force f)
{
  float x = f.x;
  float y = f.y;
  const float LIM = 30;
  if (x > LIM)
    x = LIM;
  if (x < -LIM)
    x = -LIM;
  if (y > LIM)
    y = LIM;
  if (y < -LIM)
    y = -LIM;

  vx_ += 20 * x;
  vy_ += 20 * y;
  x_ += vx_ * DT;
  y_ += vy_ * DT;
}
