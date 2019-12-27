#ifndef PGEBULLETHELL_ENEMYMOVENONE_H
#define PGEBULLETHELL_ENEMYMOVENONE_H

#include "olcPixelGameEngine.h"
#include "Enemy.h"

class EnemyMoveNone : public Enemy
{
public:
    EnemyMoveNone(Game* game, olc::vf2d position, std::string spriteLocation);

protected:
    void Movement(float fElapsedTime) override;
    void Firing(float fElapsedTime) override;
};

#endif //PGEBULLETHELL_ENEMYMOVENONE_H