#include "Game.h"
#include "EnemyMoveNone.h"
#include "EnemyMoveStraightFast.h"
#include "EnemyMoveStraightSlow.h"
#include "EnemyMoveSinusoidNarrow.h"

Game::Game() : starmap(this), player(this), ui(this)
{
    sAppName = "pgeBulletHell";
}

bool Game::OnUserCreate()
{
    starmap.Generate();
    //GenerateEnemies();
    return true;
}

bool Game::OnUserUpdate(float fElapsedTime)
{
    Clear(olc::BLACK);

    starmap.Update(fElapsedTime);

    switch (phase) {
        case 0:
            TitleScreen(fElapsedTime);
            break;
        case 1:
            PrimaryLoop(fElapsedTime);
            break;
        case 2:
            GameOver(fElapsedTime);
            break;
    }

    //PrimaryLoop(fElapsedTime);

    return true;
}

void Game::GameOver(float fElapsedTime)
{
    ui.DrawGameOver();

    if (GetKey(olc::SPACE).bHeld) {
        // do some resetting here
        enemies.clear();
        fragments.clear();
        eDefs.clear();
        player.health = 100.0f;
        player.bullets.clear();
        player.isDead = false;
        score = 0;
        time = 0;
        interactionDelay = 1.0f;

        player.position = {static_cast<float>((ScreenWidth() - (player.spr->width / 2))), static_cast<float>((ScreenHeight() - 50))};

        phase = 0;
    }
}

void Game::TitleScreen(float fElapsedTime)
{
    ui.DrawTitleScreen();
    interactionDelay -= fElapsedTime;

    if (GetKey(olc::SPACE).bHeld && interactionDelay <= 0) {
        phase = 1;
        GenerateEnemies();
    }
}

void Game::PrimaryLoop(float fElapsedTime)
{
    time += fElapsedTime;

    if (!player.isDead) {
        ProcessPlayerCollision();
    }
    ProcessEnemyCollision();

    SetPixelMode(olc::Pixel::ALPHA);
    if (!player.isDead) {
        player.Update(fElapsedTime);
    }
    ProcessEnemies(fElapsedTime);
    SetPixelMode(olc::Pixel::NORMAL);

    ui.Draw();
}

void Game::GenerateEnemies()
{
    eDefs.push_back({{static_cast<float>(ScreenWidth() * 0.5), 0}, "gfx//enemy1.png", 1, 3.0f});

    eDefs.push_back({{static_cast<float>(ScreenWidth() * 0.25), 0}, "gfx//enemy1.png", 2, 8.0f});
    eDefs.push_back({{static_cast<float>(ScreenWidth() * 0.75), 0}, "gfx//enemy1.png", 2, 8.0f});

    eDefs.push_back({{static_cast<float>(ScreenWidth() * 0.25), 0}, "gfx//enemy1.png", 3, 10.0f});
    eDefs.push_back({{static_cast<float>(ScreenWidth() * 0.5), 0}, "gfx//enemy1.png", 3, 10.0f});
    eDefs.push_back({{static_cast<float>(ScreenWidth() * 0.75), 0}, "gfx//enemy1.png", 3, 10.0f});

    eDefs.push_back({{static_cast<float>(ScreenWidth() * 0.25), 0}, "gfx//enemy1.png", 4, 12.0f});
    eDefs.push_back({{static_cast<float>(ScreenWidth() * 0.75), 0}, "gfx//enemy1.png", 4, 12.0f});

    eDefs.push_back({{static_cast<float>(ScreenWidth() * 0.5), 0}, "gfx//enemy2.png", 4, 13.5f});
    eDefs.push_back({{static_cast<float>(ScreenWidth() * 0.75), 0}, "gfx//enemy2.png", 4, 13.5f});
}

void Game::ProcessEnemies(float fElapsedTime)
{
    // add enemies when their time comes
    for (auto& ed : eDefs) {
        //DrawString({10, 30}, std::to_string(ed.loaded));
        if (ed.startTime <= time && !ed.loaded) {
            //DrawString({10, 30}, std::to_string(ed.startTime));
            switch (ed.type) {
                case 1:
                    enemies.emplace_back(new EnemyMoveNone(this, ed.pos, ed.spriteLocation));
                    break;
                case 2:
                    enemies.emplace_back(new EnemyMoveStraightFast(this, ed.pos, ed.spriteLocation));
                    break;
                case 3:
                    enemies.emplace_back(new EnemyMoveStraightSlow(this, ed.pos, ed.spriteLocation));
                    break;
                case 4:
                    enemies.emplace_back(new EnemyMoveSinusoidNarrow(this, ed.pos, ed.spriteLocation));
                    break;
            }

            ed.loaded = true;
        }
    }

    // update and draw each active enemy
    for (auto& e : enemies) {
        e->Update(fElapsedTime);
    }

    // remove enemies when they've reached the bottom of the screen or they're dead
    enemies.remove_if([&](Enemy* e) {return e->GetPosition().y >= ScreenHeight() || e->isDead;});

    // update and draw explosions
    for (auto& f : fragments) {
        f.position += (f.velocity + olc::vf2d(0.0f, scrollSpeed)) * fElapsedTime;
        Draw(f.position, olc::YELLOW);
    }

    // remove fragments that are now offscreen
    fragments.remove_if([&](Bullet f) {
        return f.position.x < 0 || f.position.x > ScreenWidth() || f.position.y < 0 || f.position.y > ScreenHeight();
    });
}

float Game::GetPlayerHealth()
{
    return player.health;
}

void Game::ProcessPlayerCollision()
{
    // if ((b.pos - (vPlayerPos + olc::vf2d(24.0f, 24.0f))).mag2() < fPlayerShipRad)
    for (auto& e : enemies) {
        //DrawString({10, 50}, "An enemy");
        for (auto& b : e->bullets) {
            //DrawString({10, 80}, "A bullet");
            if ((b.position - (player.position + olc::vf2d(player.spr->width / 2, player.spr->height / 2))).mag2() < player.radius) {
                player.health -= 3.0f;
                b.isDead = true;
            }
        }
    }

    if (player.health <= 0) {
        player.health = 0;
        player.isDead = true;

        // trigger explosion
        for (int i = 0; i < 500; i++)
        {
            float angle = ((float)rand() / (float)RAND_MAX) * 2.0f * 3.14159f;
            float speed = ((float)rand() / (float)RAND_MAX) * 200.0f + 50.0f;
            olc::vf2d position = {
                    player.position + olc::vf2d({static_cast<float>(player.spr->width / 2), static_cast<float>(player.spr->height / 2)}),
            };
            olc::vf2d velocity = {
                    cosf(angle) * speed,
                    sinf(angle) * speed
            };
            fragments.push_back(Bullet(position, velocity));
        }

        phase = 2;
    }
}

void Game::ProcessEnemyCollision()
{
    for (auto& e : enemies) {
        for (auto& b : player.bullets) {
            if ((b.position - (e->position + olc::vf2d(e->spr->width / 2, e->spr->height / 2))).mag2() < e->radius) {
                e->health -= 1.0f;

                if (e->health <= 0.0f) {
                    e->isDead = true;
                    score += e->value;

                    // trigger explosion
                    for (int i = 0; i < 500; i++)
                    {
                        float angle = ((float)rand() / (float)RAND_MAX) * 2.0f * 3.14159f;
                        float speed = ((float)rand() / (float)RAND_MAX) * 200.0f + 50.0f;
                        olc::vf2d position = {
                                e->position + olc::vf2d({static_cast<float>(e->spr->width / 2), static_cast<float>(e->spr->height / 2)}),
                        };
                        olc::vf2d velocity = {
                                cosf(angle) * speed,
                                sinf(angle) * speed
                        };
                        fragments.push_back(Bullet(position, velocity));
                    }
                }

                b.isDead = true;
            }
        }
    }
}