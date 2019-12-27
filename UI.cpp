#include "UI.h"
#include "Game.h"

UI::UI(Game* game)
{
    this->game = game;
}

void UI::Draw()
{
    olc::vf2d healthBarPosition = {60, 8};
    olc::vf2d healthBarSize = {
            static_cast<float>(game->ScreenWidth() - 70) * (game->GetPlayerHealth() / 100),
            10.0f
    };

    game->DrawString({10, 10}, "Health:");
    game->FillRect(healthBarPosition, healthBarSize, olc::BLUE);
    game->DrawString({10, 30}, "Score: " + std::to_string(game->score));
}

void UI::DrawTitleScreen()
{
    game->DrawString({game->ScreenWidth() / 2 - 200, game->ScreenHeight() / 2 - 150}, "pgeBulletHell", olc::DARK_RED, 4);
    game->DrawString({game->ScreenWidth() / 2 - 75, game->ScreenHeight() / 2 - 75}, "Press space to start", olc::WHITE);
    game->DrawString({game->ScreenWidth() / 2 - 100, game->ScreenHeight() - 40}, "Developed by SaladinAkara", olc::WHITE);
}

void UI::DrawGameOver()
{
    game->DrawString({game->ScreenWidth() / 2 - 175, game->ScreenHeight() / 2 - 150}, "Game Over!", olc::RED, 4);
    game->DrawString ({game->ScreenWidth() / 2 - 50, game->ScreenHeight() / 2 - 75}, "Score: " + std::to_string(game->score), olc::WHITE);
}