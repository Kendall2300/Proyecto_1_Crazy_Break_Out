/**
 * @file pedall.hpp
 * @authors Kendall Martinez Carvajal (kendallmc@estudiantec.cr) && Daniel Urena Lopez (dlurena24@estudiantec.cr)
 * @brief
 * Este codigo define los metodos y atributos creados para la clase pedal.
 *
 * @version 1.0
 *
 * @copyright Copyright (c) 2021
 */
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
