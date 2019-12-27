#ifndef PGEBULLETHELL_ENEMYMOVESTRAIGHTSLOW_H
#define PGEBULLETHELL_ENEMYMOVESTRAIGHTSLOW_H

#include "olcPixelGameEngine.h"
#include "Enemy.h"

class EnemyMoveStraightSlow : public Enemy
{
public:
    EnemyMoveStraightSlow(Game* game, olc::vf2d position, std::string spriteLocation);

protected:
    void Movement(float fElapsedTime) override;
    void Firing(float fElapsedTime) override;
};


#endif //PGEBULLETHELL_ENEMYMOVESTRAIGHTSLOW_H
