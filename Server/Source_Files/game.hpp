/**
 * @file game.hpp
 * @authors Kendall Martinez Carvajal (kendallmc@estudiantec.cr) && Daniel Urena Lopez (dlurena24@estudiantec.cr)
 * @brief
 * Este codigo define los metodos y atributos para controlar el pedal, wall y ball.
 *
 * @version 1.0
 *
 * @copyright Copyright (c) 2021
 */
#pragma once
#include "ball.hpp"
#include "wall.hpp"
#include "pedal.hpp"

class Game
{
public:
  void draw(Painter &) const;
  void setX(int x);
  void tick();
private:
  Ball ball_;
  Wall wall_;
  Pedal pedal_;
public:
    int ballCounter = 5;
    int GScore=0;
};
