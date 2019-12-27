#ifndef PGEBULLETHELL_ENEMYMOVESINUSOIDNARROW_H
#define PGEBULLETHELL_ENEMYMOVESINUSOIDNARROW_H

#include "olcPixelGameEngine.h"
#include "Enemy.h"

class EnemyMoveSinusoidNarrow : public Enemy
{
public:
    EnemyMoveSinusoidNarrow(Game* game, olc::vf2d position, std::string spriteLocation);

protected:
    void Movement(float fElapsedTime) override;
    void Firing(float fElapsedTime) override;
};


#endif //PGEBULLETHELL_ENEMYMOVESINUSOIDNARROW_H
