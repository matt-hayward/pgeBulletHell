#include "EnemyMoveNone.h"
#include "Game.h"

EnemyMoveNone::EnemyMoveNone(Game* game, olc::vf2d position, std::string spriteLocation) :
    Enemy(game, position, spriteLocation) {}

void EnemyMoveNone::Movement(float fElapsedTime) {}

void EnemyMoveNone::Firing(float fElapsedTime) {
    // check input to create new bullets based on cooldown
    bulletCooldown += fElapsedTime;
    if (bulletCooldown >= bulletTriggerTime) {
        bullets.emplace_back(Bullet({position.x + (spr->width / 2), position.y + spr->height}));
        //bullets.push_back({position.x + (spr->width / 2), position.y + spr->height});

        bulletCooldown = 0.0f;
    }

    // remove bullets if they're off screen or have collided with the player
    bullets.remove_if([&](const Bullet b) {return b.position.y <= 0 || b.isDead;});

    // draw bullets
    for (auto& b : bullets) {
        // update position of bullet
        b.position.y += (speed * 1.5) * fElapsedTime;

        game->FillCircle(b.position, 3, olc::DARK_RED);
    }
}
