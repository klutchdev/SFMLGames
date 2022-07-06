#include "Game.h"

#include <time.h>

int main()
{
  // Init srand
  // std::srand(static_cast<unsigned int>(time(0)));

  Game game;

  game.run();

  return 0;
}