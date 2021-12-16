#pragma once
#include <iostream>
#include <string>
#include "Character.h"
#include "Hero.h"
#include "Map.h"
#include "SoundManager.h"
#include "SDL2Manager.h"
#include "DrawManager.h"
#include "ItemMenu.h"
#include "InfoBox.h"
#include "SoundManager.h"

//SDL Libs
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

class GameManager
{
public:
	GameManager();
	~GameManager();
	bool isGameOn = true;
	SDL2Manager sdlManager;
	DrawManager drawManager;
	Map map;
	ItemMenu itemMenu;
	InfoBox infoBox;
	Hero hero;
	SoundManager sm;

	int initGameSystems();

	void gameLoopUpdate();
};

