/**
 * @file force.h
 * @authors Kendall Martinez Carvajal (kendallmc@estudiantec.cr) && Daniel Urena Lopez (dlurena24@estudiantec.cr)
 * @brief
 * Este codigo es la definicion de los atributos y metodos del force.
 *
 * @version 1.0
 *
 * @copyright Copyright (c) 2021
 */
 #pragma once

struct Force
{
  Force(float x, float y);
  float x, y;
  const Force &operator+=(const Force f);
};
