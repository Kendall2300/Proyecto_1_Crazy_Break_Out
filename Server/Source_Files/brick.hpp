/**
 * @file brick.h
 * @authors Kendall Martinez Carvajal (kendallmc@estudiantec.cr) && Daniel Urena Lopez (dlurena24@estudiantec.cr)
 * @brief
 * Este codigo es la definicion de los atributos y metodos del brick.
 *
 * @version 1.0
 *
 * @copyright Copyright (c) 2021
 */
#pragma once
#include "force.hpp"
#include "painter.hpp"

class Painter;
class Ball;

class Brick
{
public:
    enum { WIDTH = 80, HEIGHT = 32 };
    Brick(int col, int row, int id);
    void draw(Painter &) const;
    void destroy();
    Force tick(const Ball &);
    int getId();
    bool getDestroyed();
    bool getBrk();
    bool setBrk(bool b);
    int getDtcounter();
    int setDtcounter(int dtc);
private:
    int col_;
    int row_;
    int countDownTimer_;
    int id_;
    int counter;
    bool destroyed;
    bool brk;
    int dtcounter;
};
