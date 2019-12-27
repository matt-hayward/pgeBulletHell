#ifndef PGEBULLETHELL_ENEMY_H
#define PGEBULLETHELL_ENEMY_H

#include "olcPixelGameEngine.h"
#include "Bullet.h"
#include <list>
#include <string>

class Game;

class Enemy {
public:
    Enemy(Game* game, olc::vf2d position, std::string spriteLocation);

public:
    void Update(float fElapsedTime);
    olc::vf2d GetPosition();

protected:
    virtual void Movement(float fElapsedTime) = 0;
    virtual void Firing(float fElapsedTime) = 0;

protected:
    Game* game;
    float speed = 200.0f;
    float bulletCooldown = 0.0f;
    float bulletTriggerTime = 0.3f;
    std::array<float, 4> moveData { 0 };

public:
    olc::Sprite* spr = nullptr;
    std::list<Bullet> bullets;
    olc::vf2d position = { 20.0f, 20.0f };
    float radius;
    float health = 3.0f;
    bool isDead = false;
    int value = 100;
};


#endif //PGEBULLETHELL_ENEMY_H
