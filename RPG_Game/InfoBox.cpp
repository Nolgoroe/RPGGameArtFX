#include "InfoBox.h"



InfoBox::InfoBox()
{
	font = TTF_OpenFont("assets/vermin_vibes_1989.ttf", 16);
}


InfoBox::~InfoBox()
{
	if (textTexture != NULL)
	{
		SDL_DestroyTexture(textTexture);
	}
	TTF_CloseFont(font);
}

void InfoBox::setup(SDL_Renderer * _renderer)
{
	renderer = _renderer;
}

void InfoBox::setText(string _text)
{
	if (text != _text && _text != "")
	{
		if (textTexture != NULL)
		{
			SDL_DestroyTexture(textTexture);
		}

		text = _text;

		SDL_Color textColor = { 0,0,0,0 };

		SDL_Surface* textSurface = TTF_RenderText_Blended(font, text.c_str(), textColor);

		textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

		SDL_FreeSurface(textSurface);

		SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);

		textRect.x = 320 / 2 - textRect.w / 2;
		textRect.y = 240 / 2 - textRect.h / 2;

		backgroundBoxRect.x = textRect.x - 4;
		backgroundBoxRect.y = textRect.y - 4;
		backgroundBoxRect.w = textRect.w + 8;
		backgroundBoxRect.h = textRect.h + 8;
	}
}

void InfoBox::draw()
{
	if (visible && textTexture != NULL && text != "") 
	{
		SDL_SetRenderDrawColor(renderer, 217, 43, 90, 255);
		SDL_RenderFillRect(renderer, &backgroundBoxRect);

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderDrawRect(renderer, &backgroundBoxRect);

		SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
	}
}
