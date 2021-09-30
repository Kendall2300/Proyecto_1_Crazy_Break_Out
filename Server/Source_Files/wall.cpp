#include "wall.hpp"
#include "ball.hpp"
#include "iostream"

using namespace std;

//bool brk = false;

Wall::Wall() //Creación de bricks
{
    srand(time(NULL));
    //int counter =0;

    id_ = rand() % 6 + 1;
    for (int row = 0; row < 10; ++row){
        /*if(row == randNumy && counter<=3){
            for (int col = 0; col < COLS_COUNT; ++col){
                if(col == randNumx /*&& counter<=3){
                    bricks_.push_back(Brick(col, row, ematoma));
                    randNumx = rand() % 16 + randNumx;
                    //randNumy ++;
                    ematoma = rand() % 6;
                    counter ++;
                }
                else {
                    bricks_.push_back(Brick(col, row, commonBrick));
                }
                randNumy ++;
            }
        }
        else{*/
            for (int col = 0; col < COLS_COUNT; ++col){
                    bricks_.push_back(Brick(col, row, id_));
                    id_ = rand() % 6 + 1;
            }
        /*}*/
    }
}

void Wall::draw(Painter &p) const
{
  for (Bricks::const_iterator i = bricks_.begin();i != bricks_.end(); ++i)
    i -> draw(p);
}

Force Wall::tick(const Ball &ball)
{
  Force result(0, 0);
  if (1 - ball.x() > 0)
    result += Force(1 - ball.x(), 0);
  if (WIDTH - ball.x() -1 < 0)
    result += Force(WIDTH - ball.x() -1, 0);
  if (1 - ball.y() > 0)
    result += Force(0, 1 - ball.y());

  for (Bricks::iterator i = bricks_.begin(); i != bricks_.end(); ++i)
  {
    Force f = i -> tick(ball);
    result += f;
    if (f.x != 0 || f.y != 0){
        i -> destroy();
        if(i->getDestroyed() && !i->getBrk()){
            if(i->getId()==1){
                score+=10;
                i->setBrk(true);
            }if(i->getId()==2){
                if(i->getDtcounter() > 24){
                    score+=15;
                    i->setBrk(true);
                }
                else{
                    i->setDtcounter(1);
                }
            }if(i->getId()==3){
                if(i->getDtcounter() > 48){
                    score+=20;
                    i->setBrk(true);
                }
                else{
                    i->setDtcounter(1);
                }
            }
            cout << "Score:" << score << endl;
        }
    }
  }

  return result;
}
