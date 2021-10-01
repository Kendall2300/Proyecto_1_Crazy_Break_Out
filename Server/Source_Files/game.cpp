#include "game.hpp"
#include "painter.hpp"
#include "iostream"

using namespace std;


void Game::draw(Painter &p) const
{
  wall_.draw(p);
  ball_.draw(p);
  pedal_.draw(p);

}

void Game::setX(int x)
{
  pedal_.setX(x);
}
void Game::tick()
{
  Force f = wall_.tick(ball_);
  GScore=wall_.score;
  f += pedal_.tick(ball_);
  ball_.tick(f);
  if (ball_.y() > Wall::HEIGHT){
      ball_ = Ball();
      ballCounter--;
      if(ballCounter == 0){ //GAME OVER
          exit(0);
      }
      cout << "Balls:" << ballCounter << endl;
  }
  if(wall_.getItsSurprise()){
      pedal_.surpRoller();
      wall_.setItsSurprise(false);
  }
}
