#pragma once

class Painter
{
public:
  enum Color { WHITE, CYAN, BLUE, DARK_BLUE, PURPLE, GRAY, PINK, BLACK };
  void bar(int x1,  int y1, int x2, int y2);
  void ball(int x, int y);
  void setColor(Color);
};
