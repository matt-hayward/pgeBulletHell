#ifndef PGEBULLETHELL_ENEMYMOVESTRAIGHTFAST_H
#define PGEBULLETHELL_ENEMYMOVESTRAIGHTFAST_H

#include "olcPixelGameEngine.h"
#include "Enemy.h"

class EnemyMoveStraightFast : public Enemy
{
public:
    EnemyMoveStraightFast(Game* game, olc::vf2d position, std::string spriteLocation);

protected:
    void Movement(float fElapsedTime) override;
    void Firing(float fElapsedTime) override;
};


#endif //PGEBULLETHELL_ENEMYMOVESTRAIGHTFAST_H
