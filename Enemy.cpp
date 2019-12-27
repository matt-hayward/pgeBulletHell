#include "Enemy.h"
#include "Game.h"

Enemy::Enemy(Game* game, olc::vf2d position, std::string spriteLocation)
{
    this->game = game;
    this->spr = new olc::Sprite(spriteLocation);

    olc::vf2d positionModifier = {static_cast<float>(spr->width / 2), 0.0f};
    this->position = position - positionModifier;

    radius = (spr->width / 2) * (spr->width / 2);
}

void Enemy::Update(float fElapsedTime)
{
    position.y += game->scrollSpeed * fElapsedTime;

    this->Movement(fElapsedTime);

    this->Firing(fElapsedTime);

    game->DrawSprite(position, spr);
    //olc::vf2d centre = {position.x + spr->width/2, position.y+spr->height/2};
    //game->DrawCircle(centre, radius);
}

olc::vf2d Enemy::GetPosition() {
    return position;
}
