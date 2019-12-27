#ifndef PGEBULLETHELL_BULLET_H
#define PGEBULLETHELL_BULLET_H

#include "olcPixelGameEngine.h"

class Bullet {
public:
    Bullet(olc::vf2d position);
    Bullet(olc::vf2d position, olc::vf2d velocity);

public:
    olc::vf2d position;
    olc::vf2d velocity;
    bool isDead = false;
};


#endif //PGEBULLETHELL_BULLET_H
