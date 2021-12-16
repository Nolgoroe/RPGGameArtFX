#include "HealthBar.h"



HealthBar::HealthBar()
{
	hp = hpMax = 100;
}


HealthBar::~HealthBar()
{

}

void HealthBar::setup(SDL_Renderer * _renderer, int _x, int _y)
{
	renderer = _renderer;
	x = _x;
	y = _y;
}

void HealthBar::draw()
{
	SDL_Rect background = { x,y,102,12 };
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &background);


	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(renderer, &background);

	float hpF = hp;
	int currentHPBarWidth = (hpF / hpMax) * 100; // 100 = width of pixles of health bar - change to variable

	if (currentHPBarWidth < 0)
	{
		currentHPBarWidth = 0;
	}

	SDL_SetRenderDrawColor(renderer, 217, 43, 90, 255);
	SDL_Rect hpColorBar = { x + 1, y + 1, currentHPBarWidth, 10 };
	SDL_RenderFillRect(renderer, &hpColorBar);
}
