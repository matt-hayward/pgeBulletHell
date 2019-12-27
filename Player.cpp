#include "Player.h"
#include "Game.h"

Player::Player(Game* game)
{
    this->game = game;
    radius = (spr->width / 2) * (spr->width / 2);
    position = {static_cast<float>((game->ScreenWidth() - (spr->width / 2))), static_cast<float>((game->ScreenHeight() - 50))};
}

void Player::Update(float fElapsedTime)
{
    position.y += fElapsedTime * game->scrollSpeed;

    // handle input
    if (game->GetKey(olc::W).bHeld) position.y -= (speed + game->scrollSpeed) * fElapsedTime;
    if (game->GetKey(olc::S).bHeld) position.y += speed * fElapsedTime;
    if (game->GetKey(olc::A).bHeld) position.x -= speed * fElapsedTime;
    if (game->GetKey(olc::D).bHeld) position.x += speed * fElapsedTime;

    // clamp to edges
    if (position.y < 0) position.y = 0.0f;
    if (position.x < 0) position.x = 0.0f;
    if (position.y + spr->height > game->ScreenHeight()) position.y = game->ScreenHeight() - spr->height;
    if (position.x + spr->width > game->ScreenWidth()) position.x = game->ScreenWidth() - spr->width;

    HandleBullets(fElapsedTime);

    game->DrawSprite(position, spr);
    //olc::vf2d centre = {position.x + spr->width/2, position.y+spr->height/2};
    //game->DrawCircle(centre, radius);
}

void Player::HandleBullets(float fElapsedTime)
{
    // check input to create new bullets based on cooldown
    bulletCooldown += fElapsedTime;
    if (bulletCooldown >= bulletTriggerTime) {
        if (game->GetKey(olc::SPACE).bHeld) {
            bullets.emplace_back(Bullet({position.x + (spr->width / 2), position.y}));
            //bullets.push_back({position.x + (spr->width / 2), position.y});
        }

        bulletCooldown = 0.0f;
    }

    // remove bullets if they're off screen or have hit an enemy
    bullets.remove_if([&](const Bullet& b) {return b.position.y <= 0 || b.isDead;});

    // draw bullets
    for (auto& b : bullets) {
        // update position of bullet
        b.position.y -= (speed * 1.5) * fElapsedTime;

        game->FillCircle(b.position, 3, olc::GREEN);
    }
}

void Player::AdjustHealth(float healthModifier)
{
    health += healthModifier;
}
