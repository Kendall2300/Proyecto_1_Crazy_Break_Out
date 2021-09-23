#pragma once
#include "force.hpp"
#include "brick.hpp"
#include <vector>
#include <stdlib.h>
#include <time.h>

class Painter;
class Ball;

class Wall
{
public:
  enum { ROWS_COUNT = 16,
	 COLS_COUNT = 8 * 3 };
  enum { WIDTH = ROWS_COUNT * Brick::WIDTH,
	 HEIGHT = COLS_COUNT * Brick::HEIGHT };
  Wall();
  void draw(Painter &) const;
  Force tick(const Ball &);
public:
  typedef std::vector<Brick> Bricks;
  Bricks bricks_;
  int randNumx;
  int randNumy;
  int commonBrick = 0;
  int doubleBrick = 1;
  int tripleBrick = 2;
  int inBrick = 3;
  int deepBrick = 4;
  int surpriseBrick = 5;
};
