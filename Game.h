#ifndef PGEBULLETHELL_GAME_H
#define PGEBULLETHELL_GAME_H

#include "olcPixelGameEngine.h"
#include "StarMap.h"
#include "Player.h"
#include "Enemy.h"
#include "UI.h"
#include <list>

class Game : public olc::PixelGameEngine
{
public:
    Game();

public:
    bool OnUserCreate() override;
    bool OnUserUpdate(float fElapsedTime) override;

protected:
    void TitleScreen(float fElapsedTime);
    void PrimaryLoop(float fElapsedTime);
    void GameOver(float fElapsedTime);
    void GenerateEnemies();
    void ProcessEnemies(float fElapsedTime);
    void ProcessPlayerCollision();
    void ProcessEnemyCollision();

public:
    float GetPlayerHealth();

protected:
    struct enemyDef {
        olc::vf2d pos;
        std::string spriteLocation;
        int type;
        float startTime;
        bool loaded = false;
    };

protected:
    int phase = 0;
    StarMap starmap;
    Player player;
    UI ui;
    std::list<Enemy*> enemies;
    std::list<Bullet> fragments;

public:
    float scrollSpeed = 60.0f;
    float time = 0.0f;
    std::vector<enemyDef> eDefs;
    int score = 0;
    float interactionDelay = 0;
};

#endif //PGEBULLETHELL_GAME_H