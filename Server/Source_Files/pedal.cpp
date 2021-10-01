#include "pedal.hpp"
#include "wall.hpp"
#include "painter.hpp"
#include "ball.hpp"

Pedal::Pedal():
x_(Wall::WIDTH / 2),
surpRand(0)
{}

void Pedal::draw(Painter &p) const
{
  p.setColor(Painter::CYAN);
  p.bar(x_ - (WIDTH-surpRand) / 2, Wall::HEIGHT - 35,x_ + (WIDTH-surpRand) - (WIDTH-surpRand) / 2, Wall::HEIGHT-30);
}
Force Pedal::tick(const Ball &ball)
{
  float s = ball.x() - x_ + WIDTH / 2;
  if (s >= 0 && s < WIDTH && Wall::HEIGHT - 50 - ball.y() < 0) {
      return Force((Wall::HEIGHT - 50 - ball.y())  * (x_ - ball.x()) / WIDTH, Wall::HEIGHT - 50 - ball.y());
  }
  else
    return Force(0, 0);
}
void Pedal::setX(int x)
{
  x_ = x;
}

int Pedal::surpRoller()
{
    srand(time(NULL));
    surpRand = rand() % 50 + (-50);
}
