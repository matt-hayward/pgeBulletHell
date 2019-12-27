#ifndef PGEBULLETHELL_UI_H
#define PGEBULLETHELL_UI_H

#include "olcPixelGameEngine.h"

class Game;

class UI
{
public:
    UI(Game* game);

public:
    void Draw();
    void DrawTitleScreen();
    void DrawGameOver();

protected:
    Game* game;
};


#endif //PGEBULLETHELL_UI_H
