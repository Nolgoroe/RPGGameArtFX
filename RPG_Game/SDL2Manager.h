#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>

using namespace std;

class SDL2Manager
{
public:
	~SDL2Manager();
	int initAllSdlLibs();
};

