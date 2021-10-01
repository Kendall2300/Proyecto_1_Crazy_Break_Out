/**
 * @file force.cpp
 * @authors Kendall Martinez Carvajal (kendallmc@estudiantec.cr) && Daniel Urena Lopez (dlurena24@estudiantec.cr)
 * @brief
 * Este codigo manipula los metodos creados por el header, para establecer la fuerza con la que rebota la bola
 *
 * @version 1.0
 *
 * @copyright Copyright (c) 2021
 */
#include "force.hpp"

Force::Force(float ax, float ay): x(ax), y(ay) {}

const Force &Force::operator+=(const Force f)
{
  x += f.x;
  y += f.y;
  return *this;
}
