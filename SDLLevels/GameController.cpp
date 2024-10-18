#include "GameController.h"
#include "Renderer.h"
#include "SpriteAnim.h"
#include "SpriteSheet.h"
#include "TTFont.h"
#include "Timing.h"

GameController::GameController()
{
	m_sdlEvent = { };
}

GameController::~GameController()
{
}

void GameController::RunGame()
{
	AssetController::Instance().Initialize(10000000);	// Allocate 10MB
	Renderer* r = &Renderer::Instance();
	Timing* t = &Timing::Instance();
	r->Initialize(800, 600);

	TTFont* font = new TTFont();
	font->Initialize(20);

	// Code for WEEK 7 for Graohics COre 2
	Point ws = r->GetWindowSize();

	/*Texture::Pool = new ObjectPool1<Texture>();
	Texture* texture = Texture::Pool->GetResource();
	texture->Load("../Assets/Textures/Warrior.tga");*/

	SpriteSheet::Pool = new ObjectPool1<SpriteSheet>();
	SpriteAnim::Pool = new ObjectPool1<SpriteAnim>();

	SpriteSheet* sheet = SpriteSheet::Pool->GetResource();
	sheet->Load("../Assets/Textures/Warrior.tga");

	sheet->SetSize(17, 6, 69, 44);
	sheet->AddAnimation(EN_AN_IDLE, 0, 6, 6.0f);
	sheet->AddAnimation(EN_AN_RUN, 6, 8, 6.0f);

	/*ofstream writeStream("resource.bin", ios::out | ios::binary);
	sheet->Serialize(writeStream);
	writeStream.close();

	delete SpriteAnim::Pool;
	delete SpriteSheet::Pool;
	AssetController::Instance().Clear();
	AssetController::Instance().Initialize(10000000);
	SpriteSheet::Pool = new ObjectPool1<SpriteSheet>();
	SpriteAnim::Pool = new ObjectPool1<SpriteAnim>();

	SpriteSheet* sheet2 = SpriteSheet::Pool->GetResource();
	ifstream readStream("resource.bin", ios::in | ios::binary);
	sheet2->Deserialize(readStream);
	readStream.close();*/

	while (m_sdlEvent.type != SDL_QUIT)
	{
		t->Tick();

		SDL_PollEvent(&m_sdlEvent);

		r->SetDrawColor(Color(255, 255, 255, 255));
		r->ClearScreen();

		r->RenderTexture(sheet, sheet->Update(EN_AN_IDLE, t->GetDeltaTime()), Rect(0, 0, 69 * 3, 44 * 3));
		r->RenderTexture(sheet, sheet->Update(EN_AN_RUN, t->GetDeltaTime()), Rect(0, 150, 69 * 3, 150 + 44 * 3));
		//font->Write(r->GetRenderer(), "Testing 123!!!", SDL_Color{ 0, 255, 0 }, SDL_Point{ 150, 50 });

		std::string s = "Frame number: " + std::to_string(sheet->GetCurrentClip(EN_AN_IDLE));
		font->Write(r->GetRenderer(), s.c_str(), SDL_Color{ 0, 255, 0 }, SDL_Point{ 250, 50 });

		s = "Frame number: " + std::to_string(sheet->GetCurrentClip(EN_AN_RUN));
		font->Write(r->GetRenderer(), s.c_str(), SDL_Color{ 0, 255, 0 }, SDL_Point{ 250, 200 });

		std::string fps = "Frames per Second : " + std::to_string(t->GetFPS());
		font->Write(r->GetRenderer(), fps.c_str(), SDL_Color{ 0, 0, 255 }, SDL_Point{ 0, 0 });

		SDL_RenderPresent(r->GetRenderer());
	}

	delete SpriteAnim::Pool;
	delete SpriteSheet::Pool;

	font->Shutdown();
	r->Shutdown();
}

//while (m_sdlEvent.type != SDL_QUIT)
	//{
	//	SDL_PollEvent(&m_sdlEvent);
	//	//r->SetDrawColor(Color(255, 0, 0, 255));
	//	//r->ClearScreen();
	//	//r->SetDrawColor(Color(255, 255, 0, 255));	// Yellow dotted line
	//	//for (unsigned int count = 0; count < 800; count++)
	//	//{
	//	//	if (count % 2 == 0) r->RenderPoint(Point(count, 300));
	//	//}
	//	//r->SetDrawColor(Color(0, 0, 255, 255));	//Blue solid line
	//	//r->RenderLine(Rect(400, 0, 400, 600));
	//	//r->SetDrawColor(Color(0, 255, 0, 255));	// Green rectangle
	//	//r->RenderRectangle(Rect(200, 200, 300, 300));
	//	//r->SetDrawColor(Color(255, 255, 255, 255));	// White fill rectangle
	//	//r->RenderFillRectangle(Rect(400, 400, 500, 500));
	//	//r->RenderTexture(texture, Point(10, 10));

	//	// Code for WEEK 7 for Graphics COre 2
	//	//r->SetViewport(Rect(0, 0, ws.X, ws.Y));
	//	r->SetDrawColor(Color(255, 255, 255, 255));
	//	r->ClearScreen();
	//	//r->SetViewport(Rect(0, 0, ws.X / 2, ws.Y / 2));		// Top-left
	//	//r->RenderTexture(texture, Point(0, 0));
	//	//r->SetViewport(Rect(ws.X / 2, 0, ws.X, ws.Y / 2));		// Top-right
	//	//r->RenderTexture(texture, Rect(0, 0, ws.X / 2, ws.Y / 2));
	//	//r->SetViewport(Rect(0, ws.Y / 2, ws.X / 2, ws.Y));		// Bottom-left
	//	//r->RenderTexture(texture, Rect(0, 0, ws.X / 2, ws.Y / 2));
	//	//r->SetViewport(Rect(ws.X / 2, ws.Y / 2, ws.X, ws.Y));	// Bottom-right
	//	//r->RenderTexture(texture, Point(0, 0));
	//	for (unsigned int count = 0; count < 6; count++)
	//	{
	//		unsigned int xPos = count * 69;
	//		r->RenderTexture(texture, Rect(xPos, 0, xPos + 69, 44), Rect(xPos, 100, xPos + 69 * 2, 100 + 44 * 2));
	//	}
	//	SDL_RenderPresent(r->GetRenderer());
	//}

	//delete Texture::Pool;