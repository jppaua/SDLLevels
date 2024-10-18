#ifndef STANDARD_INCLUDES_H
#define STANDARD_INCLUDES_H

#define SDL_MAIN_HANDLED

// Include standard headers
#include <string>
#include <vector>
#include <iostream>
#include <cinttypes>
#include <stdio.h>
#include <thread>
// Code for WEEK 4 for ASSET MANAGEMENT
#include <map> // WEEK 4
// Code for Pool Based Allocation
#include <fstream>
// Code for week 6 Graphics Core 1
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_pixels.h>

// Project headers
#include "Singleton.h"
#include "BasicStructs.h"

// OS specific includes and defines
#ifdef _WIN32
#include <Windows.h>
#include <direct.h>
#define M_ASSERT(_cond, _msg) \
    if (!(_cond)) { OutputDebugStringA(_msg); std::abort(); }
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

using namespace std;

#endif // STANDARD_INCLUDES_H

