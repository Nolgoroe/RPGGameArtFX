#pragma once
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

using namespace std;

class ItemMenu
{
public:
	SDL_Texture* generateTextTexture(TTF_Font* _font, SDL_Color _color, string _text);

	SDL_Renderer* renderer;
	int* items;

	SDL_Texture *nothing, *chocolate, *grenade, *atkBoost, *defBoost, *cancel;

	int x, y;

	int selectedItemIndex;

	bool isVisible = false;


	ItemMenu();
	~ItemMenu();

	void setup(SDL_Renderer* _renderer, int* _items, int _x, int _y);
	void moveUp();
	void moveDown();
	void draw();
};

