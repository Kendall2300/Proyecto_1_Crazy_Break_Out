/**
 * @file painter.hpp
 * @authors Kendall Martinez Carvajal (kendallmc@estudiantec.cr) && Daniel Urena Lopez (dlurena24@estudiantec.cr)
 * @brief
 * Este codigo define los metodos y atributos creados para dibujar y pintar de un color especifico cada bloque.
 *
 * @version 1.0
 *
 * @copyright Copyright (c) 2021
 */
#pragma once

class Painter
{
public:
  enum Color { WHITE, CYAN, BLUE, DARK_BLUE, PURPLE, GRAY, PINK, BLACK };
  void bar(int x1,  int y1, int x2, int y2);
  void ball(int x, int y);
  void setColor(Color);
};
