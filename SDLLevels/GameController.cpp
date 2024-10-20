#include "GameController.h"
#include "Renderer.h"
#include "SpriteAnim.h"
#include "SpriteSheet.h"
#include "TTFont.h"
#include "Timing.h"
#include <random>

struct Warrior {
    float x;
    float y;
    float speed;
    float direction;
    float animationSpeed;
    bool isDead;
    bool isAnimatingDeath;
    float deathTimer;
};

struct Rock {
    float x;
    float y;
    float speed;
    float animationSpeed;
    bool active;
};

float GetRandomFloat(float min, float max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(min, max);
    return dist(gen);
}

GameController::GameController() {
    m_sdlEvent = { };
}

void GameController::RunGame() {
    AssetController::Instance().Initialize(10000000);
    Renderer* r = &Renderer::Instance();
    Timing* t = &Timing::Instance();
    r->Initialize(1920, 1080);

    TTFont* font = new TTFont();
    font->Initialize(20);

    Point ws = r->GetWindowSize();

    SpriteSheet::Pool = new ObjectPool1<SpriteSheet>();
    SpriteAnim::Pool = new ObjectPool1<SpriteAnim>();

    SpriteSheet* warriorSheet = SpriteSheet::Pool->GetResource();
    warriorSheet->Load("../Assets/Textures/Warrior.tga");
    warriorSheet->SetSize(17, 6, 69, 44);
    warriorSheet->AddAnimation(EN_AN_RUN, 6, 8, 0.3f);
    warriorSheet->AddAnimation(EN_AN_DEATH, 27, 10, 0.4f);

    SpriteSheet* rockSheet = SpriteSheet::Pool->GetResource();
    rockSheet->Load("../Assets/Textures/Rock.tga");
    rockSheet->SetSize(1, 4, 20, 20);
    rockSheet->AddAnimation(EN_AN_ROCK_FALL, 0, 4, 0.5f);

    std::vector<Warrior> warriors;
    for (unsigned int i = 0; i < 10; i++) {
        Warrior w;
        w.x = 0;
        w.y = 10 + (i * 100);
        w.speed = GetRandomFloat(80.0f, 100.0f);
        w.direction = 1.0f;
        w.animationSpeed = 4.8f + ((w.speed - 80.0f) / 20.0f) * (6.0f - 4.8f);
        w.isDead = false;
        w.isAnimatingDeath = false;
        w.deathTimer = 0.0f;
        warriors.push_back(w);
    }

    std::vector<Rock> rocks;
    for (unsigned int i = 0; i < 10; i++) {
        Rock r;
        r.x = 50 + (i * 100);
        r.y = 0;
        r.speed = GetRandomFloat(80.0f, 100.0f);
        r.animationSpeed = 4.8f + ((r.speed - 80.0f) / 20.0f) * (6.0f - 4.8f);
        r.active = true;
        rocks.push_back(r);
    }

    std::ofstream autoSaveStream("Level1.bin", std::ios::out | std::ios::binary);
    bool isAutoSaved = false;
    bool level2Loaded = false;
    bool rocksInitialized = false;

    float autoSaveTimer = 0.0f;
    float gameTime = 0.0f;

    while (m_sdlEvent.type != SDL_QUIT) {
        t->Tick();
        SDL_PollEvent(&m_sdlEvent);

        float deltaTime = t->GetDeltaTime();

        if (deltaTime > 0.1f) {
            deltaTime = 0.1f;
        }

        r->ClearScreen();
        autoSaveTimer += deltaTime;
        gameTime += deltaTime;

        if (autoSaveTimer >= 5.0f && !isAutoSaved) {
            isAutoSaved = true;
            autoSaveTimer = 0.0f;
        }

        bool anyWarriorOffScreen = false;

        for (auto& warrior : warriors) {
            if (warrior.x > r->GetWindowSize().X) {
                anyWarriorOffScreen = true;
                break;
            }
        }

        if (!level2Loaded && anyWarriorOffScreen) {
            level2Loaded = true;
            LoadLevel2();

            gameTime = 0.0f;
            isAutoSaved = false;
            autoSaveTimer = 0.0f;

            for (unsigned int i = 0; i < warriors.size(); ++i) {
                warriors[i].x = 0;
                warriors[i].y = 10 + (i * 100);
                warriors[i].speed = GetRandomFloat(80.0f, 100.0f);
                warriors[i].isDead = false;
                warriors[i].isAnimatingDeath = false;
                warriors[i].deathTimer = 0.0f;
            }

            rocksInitialized = true;
        }

        if (level2Loaded) {
            r->SetDrawColor(Color(0, 128, 0, 255));
        }
        else {
            r->SetDrawColor(Color(128, 128, 128, 255));
        }

        for (auto& warrior : warriors) {
            if (warrior.isDead) {
                if (warrior.isAnimatingDeath) {
                    r->RenderTexture(warriorSheet, warriorSheet->Update(EN_AN_DEATH, warrior.animationSpeed * deltaTime),
                        Rect(warrior.x, warrior.y, static_cast<int>(69 * 1.8), static_cast<int>(44 * 1.8)));

                    warrior.deathTimer += deltaTime;

                    if (warrior.deathTimer >= 2.0f) {
                        warrior.isAnimatingDeath = false;
                    }
                }
                warrior.x += warrior.speed * warrior.direction * deltaTime;
                continue;
            }

            warrior.x += warrior.speed * warrior.direction * deltaTime;
            r->RenderTexture(warriorSheet, warriorSheet->Update(EN_AN_RUN, warrior.animationSpeed * deltaTime),
                Rect(warrior.x, warrior.y, static_cast<int>(69 * 1.8), static_cast<int>(44 * 1.8)));
        }

        if (rocksInitialized) {
            for (auto& rock : rocks) {
                if (!rock.active) continue;

                rock.y += rock.speed * deltaTime;

                for (auto& warrior : warriors) {
                    if (!warrior.isDead && rock.y >= warrior.y && rock.y <= (warrior.y + 44) &&
                        rock.x >= warrior.x && rock.x <= (warrior.x + 69)) {

                        warrior.isDead = true;
                        warrior.isAnimatingDeath = true;
                        warrior.deathTimer = 0.0f;
                        rock.active = false;
                    }
                }

                r->RenderTexture(rockSheet, rockSheet->Update(EN_AN_ROCK_FALL, deltaTime),
                    Rect(rock.x, rock.y, 20, 20));

            }
        }

        std::string fps = "Frames per Second : " + std::to_string(t->GetFPS());
        font->Write(r->GetRenderer(), fps.c_str(), SDL_Color{ 0, 0, 255 }, SDL_Point{ 0, 0 });

        std::string timeText = "Game Time: " + std::to_string(static_cast<int>(gameTime));
        font->Write(r->GetRenderer(), timeText.c_str(), SDL_Color{ 0, 0, 255 }, SDL_Point{ 250, 0 });

        std::string saveStatus = isAutoSaved ? "Auto Saved: Yes" : "Auto Saved: No";
        font->Write(r->GetRenderer(), saveStatus.c_str(), SDL_Color{ 0, 0, 255 }, SDL_Point{ 500, 0 });

        SDL_RenderPresent(r->GetRenderer());
    }

    delete SpriteAnim::Pool;
    delete SpriteSheet::Pool;

    font->Shutdown();
    r->Shutdown();
}

void GameController::LoadLevel2() {
    Renderer::Instance().SetDrawColor(Color(0, 128, 0, 255));
}

GameController::~GameController() {
}
