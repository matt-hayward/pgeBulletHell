#include "Game.h"

int main()
{
    Game game;

    if (game.Construct(1024, 640, 1, 1)) {
        game.Start();
    }

    return 0;
}
