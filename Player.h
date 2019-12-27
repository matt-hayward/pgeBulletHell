#ifndef PGEBULLETHELL_PLAYER_H
#define PGEBULLETHELL_PLAYER_H

#include "olcPixelGameEngine.h"
#include "Bullet.h"
#include <list>

class Game;

class Player {
public:
    Player(Game* game);

public:
    //void Init();
    void Update(float fElapsedTime);
    void AdjustHealth(float healthModifier);

protected:
    void HandleBullets(float fElapsedTime);

protected:
    Game* game;
    float speed = 200.0f;
    float bulletCooldown = 0.0f;
    float bulletTriggerTime = 0.1f;

public:
    float health = 100.0f;
    float radius;
    olc::Sprite* spr = new olc::Sprite("gfx//player.png");
    olc::vf2d position = { 20.0f, 20.0f };
    std::list<Bullet> bullets;
    bool isDead = false;
};

#endif //PGEBULLETHELL_PLAYER_H