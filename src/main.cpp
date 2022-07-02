#include "Game.h"
#include <time.h>

int main()
{
  //============= INIT SRAND ===================//
  std::srand(static_cast<unsigned int>(time(0)));

  //============= INIT GAME ENGINE =============//
  Game game;

  //============= GAME LOOP ====================//
  game.run();

  return 0;
}