#pragma once
#include "force.hpp"

class Painter;
class Ball;

class Brick
{
public:
  enum { WIDTH = 80,
	 HEIGHT = 32 };
  Brick(int col, int row, int id);
  void draw(Painter &) const;
  void destroy();
  Force tick(const Ball &);
private:
  int col_;
  int row_;
  int countDownTimer_;
  int id_;
};
