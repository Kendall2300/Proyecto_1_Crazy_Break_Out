#pragma once
#include "force.hpp"
#include <time.h>
#include <stdlib.h>

class Painter;
class Ball;

class Pedal
{
public:
  enum { WIDTH = 300 };
  Pedal();
  void draw(Painter &) const;
  Force tick(const Ball &);
  void setX(int x);
  int surpRoller();
private:
  int x_;
  int surpRand;
};
