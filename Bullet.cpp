#include "Bullet.h"

Bullet::Bullet(olc::vf2d position)
{
    this->position = position;
}

Bullet::Bullet(olc::vf2d position, olc::vf2d velocity)
{
    this->position = position;
    this->velocity = velocity;
}