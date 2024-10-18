
// SDLLevels.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "GameController.h"

int main()
{
    GameController::Instance().RunGame();

    return 0;
}

