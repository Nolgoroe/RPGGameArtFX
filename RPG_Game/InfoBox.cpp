#include "InfoBox.h"



InfoBox::InfoBox()
{
	/// QUESTION: Why was this constructor not called when it was written in Game Manager? it was only called at start of game
	//font = TTF_OpenFont("assets/vermin_vibes_1989.ttf", 16);
}


InfoBox::~InfoBox()

///QUESTION: ask Gaetan for explination about why is this beign called after constructor and how to stop it from happening
{
	//if (textTexture != NULL)
	//{
	//	SDL_DestroyTexture(textTexture);
	//}
	//TTF_CloseFont(font);
}

void InfoBox::setup(SDL_Renderer * _renderer)
{
	font = TTF_OpenFont("assets/vermin_vibes_1989.ttf", 16);

	renderer = _renderer;
}

void InfoBox::setText(string _text)
{
	if (text != _text && _text != "")
	{
		if (textTexture != NULL)
		{
			cout << textTexture << endl;
			cout << &textTexture << endl;

			SDL_DestroyTexture(textTexture);
		}

		text = _text;

		SDL_Color textColor = { 0,0,0,0 };

		// ttf work in a way that load text onto a surface and then transforms the surface to a texture - which we then load(render copy)
		SDL_Surface* textSurface = TTF_RenderText_Blended(font, text.c_str(), textColor);

		textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

		SDL_FreeSurface(textSurface);

		SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);

		textRect.x = RENDERER_LOGICAL_SIZE_W / 2 - textRect.w / 2;
		textRect.y = RENDERER_LOGICAL_SIZE_H / 2 - textRect.h / 2;

		// background box for the text - just to make it nicer
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
		//draw background fill all the rect with color
		SDL_SetRenderDrawColor(renderer, 217, 43, 90, 255);
		SDL_RenderFillRect(renderer, &backgroundBoxRect);

		// draw background fill the OUTLINE with color
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderDrawRect(renderer, &backgroundBoxRect);

		//copy text texture to renderer
		SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
	}
}
