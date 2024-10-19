/*
Group Members:
1. John Paua
2. Colton Hennessye
3. Ana Patel
*/

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
	float direction; // Direction of movement (1 for up, -1 for down)
	float animationSpeed; // Animation speed of the warrior
};

// Function to generate a random float between min and max
float GetRandomFloat(float min, float max) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dist(min, max);
	return dist(gen);
}

GameController::GameController()
{
	m_sdlEvent = { };
}

void GameController::RunGame()
{
}

void GameController::LoadLevel2() {
	// Renderer::Instance().SetDrawColor(Color(0, 128, 0, 255));
	Renderer* r = &Renderer::Instance();
	//r->Initialize(1920, 1080);
	r->SetDrawColor(Color(0, 128, 0, 255));
}

GameController::~GameController()
{
	AssetController::Instance().Initialize(10000000);	// Allocate 10MB
	Renderer* r = &Renderer::Instance();
	Timing* t = &Timing::Instance();
	r->Initialize(1920, 1080);

	TTFont* font = new TTFont();
	font->Initialize(20);

	// Code for WEEK 7 for Graohics COre 2
	Point ws = r->GetWindowSize();

	SpriteSheet::Pool = new ObjectPool1<SpriteSheet>();
	SpriteAnim::Pool = new ObjectPool1<SpriteAnim>();

	SpriteSheet* sheet = SpriteSheet::Pool->GetResource();
	sheet->Load("../Assets/Textures/Warrior.tga");

	sheet->SetSize(17, 6, 69, 44);
	//sheet->AddAnimation(EN_AN_IDLE, 0, 6, 6.0f);
	sheet->AddAnimation(EN_AN_RUN, 6, 8, 6.0f);

	// Create warriors
	std::vector<Warrior> warriors;
	for (unsigned int i = 0; i < 10; i++) {
		Warrior w;
		w.x = 0; // Start at the left of the screen
		w.y = 10 + (i * 100);
		w.speed = GetRandomFloat(80.0f, 100.0f);
		w.direction = 1.0f; // Always move right
		// Calculate animation speed based on running speed
		w.animationSpeed = 4.8f + ((w.speed - 80.0f) / 20.0f) * (6.0f - 4.8f);
		warriors.push_back(w);
		SDL_FLIP_HORIZONTAL;
	}

	// Auto-save functionality
	std::ofstream autoSaveStream("Level1.bin", std::ios::out | std::ios::binary);
	bool isAutoSaved = false;
	bool level2Loaded = false;

	float autoSaveTimer = 0.0f;

	while (m_sdlEvent.type != SDL_QUIT)
	{
		t->Tick();

		SDL_PollEvent(&m_sdlEvent);

		//r->SetDrawColor(Color(128, 128, 128, 255));
		r->ClearScreen();

		autoSaveTimer += t->GetDeltaTime();
		if (autoSaveTimer >= 5.0f && !isAutoSaved) {
			// Auto-save the level state
			// You should implement a Serialize method to save your game state
			// Example:
			// Serialize(autoSaveStream);
			isAutoSaved = true;
			autoSaveTimer = 0.0f; // Reset timer
		}

		bool isFirstWarriorOffScreen = false;

		// Render warriors
		for (auto& warrior : warriors) {

			// Set the background color based on whether the first warrior is off-screen
			if (isFirstWarriorOffScreen) {
				//r->SetDrawColor(Color(0, 128, 0, 255));  // Green background
				//for (unsigned int i = 0; i < warriors.size(); ++i) {
				//	warriors[i].x = 0;  // Reset to the starting X position (left of the screen)
				//	warriors[i].y = 10 + (i * 100);  // Reset the Y position with spacing
				//	warriors[i].speed = GetRandomFloat(80.0f, 100.0f);  // Re-randomize speed
				//}
				r->SetDrawColor(Color(0, 128, 0, 255));
			}
			else {
				r->SetDrawColor(Color(128, 128, 128, 255));  // Default grey background
			}

			warrior.x += warrior.speed * warrior.direction * t->GetDeltaTime(); // Move the warrior

			//std::cout << "Rendering Warrior at Position: (" << warrior.x << ", " << warrior.y << ")" << std::endl;

			r->RenderTexture(sheet, sheet->Update(EN_AN_RUN, warrior.animationSpeed * t->GetDeltaTime()),
				Rect((warrior.x), (warrior.y), static_cast < int>(69 * 1.8) , static_cast < int>(44 * 1.8)));

			warrior.x += warrior.speed * warrior.direction * t->GetDeltaTime();

			// Check if warrior has reached the right side of the screen
			/*if (warrior.x > 1920) {
				warrior.direction = -warrior.direction; // Reverse direction (move left)
			}*/

			int i = 0;

			// Check if the first warrior is off-screen
			if (i == 0 && warrior.x > r->GetWindowSize().X) 
			{
				isFirstWarriorOffScreen = true;  // Mark the flag
				//for (auto& warrior : warriors)
				//{
				//	for (unsigned int i = 0; i < warriors.size(); ++i) {
				//		warriors[i].x = 0;  // Reset to the starting X position (left of the screen)
				//		warriors[i].y = 10 + (i * 100);  // Reset the Y position with spacing
				//		warriors[i].speed = GetRandomFloat(80.0f, 100.0f);  // Re-randomize speed
				//	}

				//}
			}
		}

		std::string fps = "Frames per Second : " + std::to_string(t->GetFPS());
		font->Write(r->GetRenderer(), fps.c_str(), SDL_Color{ 0, 0, 255 }, SDL_Point{ 0, 0 });
		
		// Get the total game time
		float gameTime = t->GetTotalGameTime();

		// Display the game time
		std::string timeText = "Game Time: " + std::to_string(static_cast<int>(gameTime));
		font->Write(r->GetRenderer(), timeText.c_str(), SDL_Color{ 0, 0, 255 }, SDL_Point{ 250 , 0 });

		std::string saveStatus = isAutoSaved ? "Auto Saved: Yes" : "Auto Saved: No";
		font->Write(r->GetRenderer(), saveStatus.c_str(), SDL_Color{ 0, 0, 255 }, SDL_Point{ 500, 0 });

		SDL_RenderPresent(r->GetRenderer());
	}

	delete SpriteAnim::Pool;
	delete SpriteSheet::Pool;

	font->Shutdown();
	r->Shutdown();
}
