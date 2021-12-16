#pragma once
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

#include "InfoBox.h"

using namespace std;

#define MAX_ITEMS_INVENTORY 10

class ItemMenu
{
public:
	SDL_Texture* generateTextTexture(TTF_Font* _font, SDL_Color _color, string _text, InfoBox* _infoBox);

	SDL_Renderer* renderer;

	SDL_Texture *nothing, *chocolate, *grenade, *atkBoost, *defBoost, *cancel;

	InfoBox* infoBox;

	int x, y;

	int selectedItemIndex;

	bool isVisible = false;

	int items[MAX_ITEMS_INVENTORY];

	ItemMenu();
	~ItemMenu();

	void setup(SDL_Renderer* _renderer, int _x, int _y, InfoBox* _infoBox);
	void initItemList();

	int* getItemList();

	void moveUp();
	void moveDown();
	void draw();

	void itemFound();
};

