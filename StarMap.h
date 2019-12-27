#ifndef PGEBULLETHELL_STARMAP_H
#define PGEBULLETHELL_STARMAP_H

#include "olcPixelGameEngine.h"
#include <array>

class Game;

class StarMap {
public:
    StarMap(Game* game);

public:
    void Generate();
    void Update(float fElapsedTime);

protected:
    Game* game;
    std::array<olc::vf2d, 1000> stars;
};

#endif //PGEBULLETHELL_STARMAP_H