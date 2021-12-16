#include "ButtonManager.h"



ButtonManager::ButtonManager()
{

}


ButtonManager::~ButtonManager()
{
	if (textTexture != NULL) 
	{
		SDL_DestroyTexture(textTexture);
	}
}

void ButtonManager::setup(SDL_Renderer * _renderer, SDL_Rect _buttonRect, string _text)
{
	renderer = _renderer;
	buttonRect = _buttonRect;

	TTF_Font* font = TTF_OpenFont("assets/vermin_vibes_1989.ttf", 16);
	SDL_Color textColor = { 0,0,0,0 };
	SDL_Surface* textSurface = TTF_RenderText_Blended(font, _text.c_str(), textColor);
	textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_FreeSurface(textSurface);
	TTF_CloseFont(font);

	textRect.x = buttonRect.x + 2;
	textRect.y = buttonRect.y + 2;
	SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);

	isSelected = false;
}

void ButtonManager::draw()
{
	if (isSelected)
	{
		SDL_SetRenderDrawColor(renderer, 217, 43, 90, 255);
	}
	else 
	{
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	}


	SDL_RenderFillRect(renderer, &buttonRect);


	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(renderer, &buttonRect);

	SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
}

void ButtonManager::drawInactive()
{
	SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);


	SDL_RenderFillRect(renderer, &buttonRect);


	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(renderer, &buttonRect);

	SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
}
