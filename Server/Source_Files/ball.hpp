#pragma once
#include "force.hpp"
#include <time.h>
#include <stdlib.h>

class Painter;

class Ball
{
public:
    constexpr static const float DT = 0.001;
    Ball();
    void draw(Painter &) const;
    float x() const { return x_; }
    float y() const { return y_; }
    void tick(Force);
    int surpRoller();
private:
    float x_;
    float y_;
    float vx_;
    float vy_;
    int surpRand;
};
