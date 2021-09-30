#include "brick.hpp"
#include "painter.hpp"
#include "ball.hpp"

Brick::Brick(int col, int row, int id):
  col_(col), 
  row_(row),
  id_(id),
  countDownTimer_(-1),
  counter(0),
  Destroyed(false)
{}

void Brick::draw(Painter &p) const
{
    if (countDownTimer_ == -1)
    {
    p.setColor(static_cast<Painter::Color>(id_));//Color brick
    p.bar(col_ * WIDTH + 1, row_ * HEIGHT + 1,(col_ + 1) * WIDTH - 1, (row_ + 1) * HEIGHT - 1);
    }
    else if (countDownTimer_ != 0)//Explosion brick
    {
        if(id_ == 2){
            if(20 < counter){
                p.setColor(static_cast<Painter::Color>(1));
                p.bar(col_ * WIDTH + 1, row_ * HEIGHT + 1,(col_ + 1) * WIDTH - 1, (row_ + 1) * HEIGHT - 1);
            }
        }
        else if(id_ == 3){
            if(counter > 20){
                p.setColor(static_cast<Painter::Color>(2));
                p.bar(col_ * WIDTH + 1, row_ * HEIGHT + 1,(col_ + 1) * WIDTH - 1, (row_ + 1) * HEIGHT - 1);
            }
            if(counter > 30){
                p.setColor(static_cast<Painter::Color>(1));
                p.bar(col_ * WIDTH + 1, row_ * HEIGHT + 1,(col_ + 1) * WIDTH - 1, (row_ + 1) * HEIGHT - 1);
            }
        }
        else{
            p.setColor(static_cast<Painter::Color>(0));
            p.bar(col_ * WIDTH + 1, row_ * HEIGHT + 1,(col_ + 1) * WIDTH - 1, (row_ + 1) * HEIGHT - 1);
        }
    }
}

Force Brick::tick(const Ball &ball){


    if (countDownTimer_ == 0) {
        return Force(0, 0);
    }
    if (id_ == 2){
        if (counter > 25){
            if (countDownTimer_ > 0) {
                --countDownTimer_;
            }
        }

    }
    else if(id_ == 3){
        if (counter > 50){
            if (countDownTimer_ > 0) {
                --countDownTimer_;
            }
        }
    }

    else{
        if (countDownTimer_ > 0) {
            --countDownTimer_;
        }
    }

    Force result(0, 0);
    float f1 = (ball.y() - row_ * HEIGHT) * WIDTH - (ball.x() - col_ * WIDTH) * HEIGHT;
    float f2 = (ball.y() - row_ * HEIGHT - HEIGHT) * WIDTH + (ball.x() - col_ * WIDTH) * HEIGHT;
    bool d = f1 < 0;
    bool u = f2 < 0;

    if(id_ == 2 || id_ == 3){

        if (d && u) // top
        {
            if (row_ * HEIGHT - ball.y() - 1 < 0)
                result += Force(0, row_ * HEIGHT - ball.y() - 1);
//                counter++;
        }
        else if (d && !u) // right
        {
            if (col_ * WIDTH + WIDTH - ball.x() + 1 > 0)
                result += Force(col_ * WIDTH + WIDTH - ball.x() + 1,0);
//                counter++;
        }
        else if (!d && u) // left
        {
            if (col_ * WIDTH - ball.x() - 1 < 0)
                result += Force(0, col_ * WIDTH - ball.x() - 1);
//                counter++;
        }
        else // if (!d && !u) // bottom
        {
            if (row_ * HEIGHT + HEIGHT - ball.y() + 1 > 0){
                result += Force(0, row_ * HEIGHT + HEIGHT - ball.y() + 1);
                counter++;
            }
        }
    }
    else{
      if (d && u) // top
      {
          if (row_ * HEIGHT - ball.y() - 1 < 0)
              result += Force(0, row_ * HEIGHT - ball.y() - 1);
      }
      else if (d && !u) // right
      {
          if (col_ * WIDTH + WIDTH - ball.x() + 1 > 0)
              result += Force(col_ * WIDTH + WIDTH - ball.x() + 1,
                              0);
      }
      else if (!d && u) // left
      {
          if (col_ * WIDTH - ball.x() - 1 < 0)
              result += Force(0, col_ * WIDTH - ball.x() - 1);
      }
      else // if (!d && !u) // bottom
      {
          if (row_ * HEIGHT + HEIGHT - ball.y() + 1 > 0)
              result += Force(0, row_ * HEIGHT + HEIGHT - ball.y() + 1);
      }
    }

    return result;
}

void Brick::destroy()
{
  if(id_ == 5){
      if (countDownTimer_ == -1)
          countDownTimer_ = -1;
  }
  else{
      if (countDownTimer_ == -1)
          countDownTimer_ = 60;
      Destroyed=true;
  }

}
int Brick::getId() {
    return id_;
}
bool Brick::getDestroyed() {
    return Destroyed;
}
/*void Brick::setDestroyed() {
    Destroyed=true;
}*/