#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "StandardIncludes.h"

class GameController : public Singleton<GameController>
{
public:
	// Constructors and Destructors
	GameController();
	virtual ~GameController();

	// Methods
	void RunGame();
	void LoadLevel2();

private:
	// Members
	SDL_Event m_sdlEvent;
};

#endif // !GAME_CONTROLLER_H

