#pragma once
#include <SDL.h>
class HealthBar
{
public:
	int x, y;
	int hp, hpMax;
	SDL_Renderer* renderer;

	
	HealthBar();
	~HealthBar();

	void setup(SDL_Renderer* _renderer, int _x, int _y);
	void draw();
};

