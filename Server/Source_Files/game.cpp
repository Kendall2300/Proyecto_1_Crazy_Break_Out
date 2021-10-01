/**
 * @file game.cpp
 * @authors Kendall Martinez Carvajal (kendallmc@estudiantec.cr) && Daniel Urena Lopez (dlurena24@estudiantec.cr)
 * @brief
 * Este codigo manipular las clases de wall, ball y pedal. Asi como definir el final del juego y pintar los objetos.
 *
 * @version 1.0
 *
 * @copyright Copyright (c) 2021
 */
#include "game.hpp"
#include "painter.hpp"
#include "iostream"

using namespace std;

/**
 * @brief
 * Este metodo se encarga de pintar o dibujar en pantalla a los bloques, la bola y el pedal
 * @param p
 */
void Game::draw(Painter &p) const
{
  wall_.draw(p);
  ball_.draw(p);
  pedal_.draw(p);

}
/**
 * @brief
 * Este metodo se encarga de colocar la posicion del pedal segun la posicion del puntero del raton.
 * @param x int correspondiente a la posicion x del puntero del mraton.
 */
void Game::setX(int x)
{
  pedal_.setX(x);
}
/**
 * @brief
 * Este metodo se encarga de revisar por segundo que acciones suceden durante al ejecucion del prgrama y define el final del juego
 */
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
      ball_.surpRoller();
      wall_.setItsSurprise(false);
  }
}
