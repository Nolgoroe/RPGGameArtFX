#pragma once
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

using namespace std;

class ButtonManager
{
public:
	SDL_Renderer* renderer;
	SDL_Rect buttonRect;
	SDL_Texture* textTexture;
	SDL_Rect textRect;

	bool isSelected;

	ButtonManager();
	~ButtonManager();

	void setup(SDL_Renderer* _renderer, SDL_Rect _buttonRect, string _text);
	void draw();

};

