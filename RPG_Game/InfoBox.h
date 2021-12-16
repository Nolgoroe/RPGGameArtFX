#pragma once
#include <iostream>
#include <string>
#include <SDL.h>
#include<SDL_ttf.h>

#include "DrawManager.h"
using namespace std;

class InfoBox
{
public:

	SDL_Renderer* renderer;

	TTF_Font* font;
	string text;
	SDL_Texture* textTexture;
	SDL_Rect textRect;
	SDL_Rect backgroundBoxRect;

	bool visible = true;

	InfoBox();
	~InfoBox();

	void setup(SDL_Renderer* _renderer);
	void setText(string _text);
	void draw();
};

