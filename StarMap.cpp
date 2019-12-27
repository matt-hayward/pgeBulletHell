#include "StarMap.h"
#include "Game.h"

StarMap::StarMap(Game* game)
{
    this->game = game;
}

void StarMap::Generate()
{
    for (auto& s : stars) {
        s = {(float)(rand() % game->ScreenWidth()), (float)(rand() % game->ScreenHeight())};
    }
}

void StarMap::Update(float fElapsedTime)
{
    for (size_t i = 0; i < stars.size(); i++) {
        auto& s = stars[i];
        float modifier = 1.0f;
        olc::Pixel colour = olc::WHITE;

        if (i <= stars.size() * 0.25f) {
            modifier = 0.4f;
            colour = olc::VERY_DARK_GREY;
        } else if (i <= stars.size() * 0.5f) {
            modifier = 0.6f;
            colour = olc::DARK_GREY;
        } else if (i <= stars.size() * 0.75f) {
            modifier = 0.8f;
            colour = olc::GREY;
        }

        s.y += game->scrollSpeed * fElapsedTime * modifier;

        if (s.y >= game->ScreenHeight()) {
            s = {(float)(rand() % game->ScreenWidth()), 0.0f};
        }

        game->Draw(s, colour);
    }
}