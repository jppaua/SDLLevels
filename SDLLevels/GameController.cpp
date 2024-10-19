#include "GameController.h"
#include "Renderer.h"
#include "SpriteAnim.h"
#include "SpriteSheet.h"
#include "TTFont.h"
#include "Timing.h"
#include <random>  // Required for random number generation

struct Warrior {
    float x;       // X position of the warrior
    float y;       // Y position of the warrior
    float speed;   // Speed of the warrior
    float direction; // Direction of movement (1 for right)
    float animationSpeed; // Animation speed of the warrior
};

// Function to generate a random float between min and max
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
    AssetController::Instance().Initialize(10000000);	// Allocate 10MB
    Renderer* r = &Renderer::Instance();
    Timing* t = &Timing::Instance();
    r->Initialize(1920, 1080);

    TTFont* font = new TTFont();
    font->Initialize(20);

    Point ws = r->GetWindowSize();

    SpriteSheet::Pool = new ObjectPool1<SpriteSheet>();
    SpriteAnim::Pool = new ObjectPool1<SpriteAnim>();

    SpriteSheet* sheet = SpriteSheet::Pool->GetResource();
    sheet->Load("../Assets/Textures/Warrior.tga");
    sheet->SetSize(17, 6, 69, 44);
    sheet->AddAnimation(EN_AN_RUN, 6, 8, 6.0f);

    std::vector<Warrior> warriors;
    for (unsigned int i = 0; i < 10; i++) {
        Warrior w;
        w.x = 0; // Start at the left of the screen
        w.y = 10 + (i * 100);
        w.speed = GetRandomFloat(80.0f, 100.0f);
        w.direction = 1.0f; // Always move right
        w.animationSpeed = 4.8f + ((w.speed - 80.0f) / 20.0f) * (6.0f - 4.8f);
        warriors.push_back(w);
    }

    std::ofstream autoSaveStream("Level1.bin", std::ios::out | std::ios::binary);
    bool isAutoSaved = false;
    bool level2Loaded = false;

    float autoSaveTimer = 0.0f;
    float gameTime = 0.0f;

    while (m_sdlEvent.type != SDL_QUIT) {
        t->Tick();
        SDL_PollEvent(&m_sdlEvent);

        r->ClearScreen();
        autoSaveTimer += t->GetDeltaTime();
        gameTime += t->GetDeltaTime();

        // Auto-save after 5 seconds
        if (autoSaveTimer >= 5.0f && !isAutoSaved) {
            // Auto-save the level state
            isAutoSaved = true;
            autoSaveTimer = 0.0f; // Reset timer
        }

        bool anyWarriorOffScreen = false;

        // Check if any warrior goes off-screen
        for (auto& warrior : warriors) {
            if (warrior.x > r->GetWindowSize().X) {
                anyWarriorOffScreen = true;
                break;  // Exit the loop once we find the first warrior off-screen
            }
        }

        // If any warrior is off-screen and Level 2 hasn't been loaded yet, transition
        if (!level2Loaded && anyWarriorOffScreen) {
            level2Loaded = true;
            LoadLevel2(); // Load Level 2

            gameTime = 0.0f;        // Reset the game time
            isAutoSaved = false;    // Reset auto-save flag
            autoSaveTimer = 0.0f;   // Reset the auto-save timer

            // Reset all warriors to starting positions and speeds
            for (unsigned int i = 0; i < warriors.size(); ++i) {
                warriors[i].x = 0;  // Reset to starting X position
                warriors[i].y = 10 + (i * 100);  // Reset Y position
                warriors[i].speed = GetRandomFloat(80.0f, 100.0f);  // Re-randomize speed
            }
        }

        // Set the background color based on the current level
        if (level2Loaded) {
            r->SetDrawColor(Color(0, 128, 0, 255));  // Set background to green
        }
        else {
            r->SetDrawColor(Color(128, 128, 128, 255));  // Default grey background
        }

        // Render warriors
        for (auto& warrior : warriors) {
            warrior.x += warrior.speed * warrior.direction * t->GetDeltaTime(); // Move the warrior

            // Adjusted animation speed
            r->RenderTexture(sheet, sheet->Update(EN_AN_RUN, warrior.animationSpeed * t->GetDeltaTime()),
                Rect(warrior.x, warrior.y, static_cast<int>(69 * 1.8), static_cast<int>(44 * 1.8)));
        }

        // Display FPS, Game Time, and Auto-save status
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
    Renderer::Instance().SetDrawColor(Color(0, 128, 0, 255));  // Set background to green
}

GameController::~GameController() {
    // Clean up any remaining resources
}
