#pragma once
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <fstream>
#include <list>
#include <stdlib.h>
#include <time.h>

#include "Hero.h"
#include "MapObject.h"
#include "InfoBox.h"
#include "BattleManager.h"
#include "SoundManager.h"

using namespace std;

class Map
{
public:
	Hero* hero;
	ItemMenu* itemMenu;
	SoundManager* sm;

	int map[10][10];

	MapObject heroIcon;
	MapObject exitDungeonDoorIcon;
	list<MapObject> mapObjectsIcons;

	SDL_Renderer* renderer;
	SDL_Texture *heroTexture, *exitDungeonDoorTexture, *globEnemyTexture, *chestTexture;

	bool quitGame = false;
	bool escapedDungeon = false;
	bool isDoorLocked = true;

	InfoBox* infoBox;

	Map(SDL_Renderer* _renderer, Hero* _hero, ItemMenu* itemMenu, InfoBox* _infoBox, SoundManager* _sm);
	Map();
	~Map();

	//void itemFound();

	void update();
	void draw();
};

