#include "Game.h"

int main()
{
    //============= INIT SRAND ===================//
    std::srand(static_cast<unsigned>(time(0)));

    //============= INIT GAME ENGINE =============//
    Game game;

    //============= GAME LOOP ====================//
    while (game.running() && !game.getEndGame())
    {
        game.update();
        game.render();
    }

    return 0;
}