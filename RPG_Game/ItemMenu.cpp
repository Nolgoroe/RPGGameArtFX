#include "ItemMenu.h"



SDL_Texture * ItemMenu::generateTextTexture(TTF_Font * _font, SDL_Color _color, string _text)
{
	SDL_Surface* textSurface = TTF_RenderText_Blended(_font, _text.c_str(), _color);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_FreeSurface(textSurface);

	return textTexture;
}

ItemMenu::ItemMenu()
{
}


ItemMenu::~ItemMenu()
{
	SDL_DestroyTexture(nothing);
	SDL_DestroyTexture(chocolate);
	SDL_DestroyTexture(grenade);
	SDL_DestroyTexture(atkBoost);
	SDL_DestroyTexture(defBoost);
	SDL_DestroyTexture(cancel);
}

void ItemMenu::setup(SDL_Renderer * _renderer, int * _items, int _x, int _y)
{
	renderer = _renderer;
	x = _x;
	y = _y;
	items = _items;

	TTF_Font* font = TTF_OpenFont("assets/vermin_vibes_1989.ttf", 16);
	SDL_Color textColor = { 0,0,0,0 };

	nothing = generateTextTexture(font, textColor, "--");
	chocolate = generateTextTexture(font, textColor, "Chocolate");
	grenade = generateTextTexture(font, textColor, "Grenade");
	atkBoost = generateTextTexture(font, textColor, "Atk Boost");
	defBoost = generateTextTexture(font, textColor, "Def Boost");
	cancel = generateTextTexture(font, textColor, "Cancel");

	TTF_CloseFont(font);
}

void ItemMenu::moveUp()
{
	selectedItemIndex--;

	if (selectedItemIndex < 0)
	{
		selectedItemIndex = 0;
	}
}

void ItemMenu::moveDown()
{
	selectedItemIndex++;

	if (selectedItemIndex > 10)
	{
		selectedItemIndex = 10;
	}

}

void ItemMenu::draw()
{
	if (!isVisible)
	{
		return;
	}

	SDL_Rect itemButton = { x,y, 100,20 };

	for (int i = 0; i < 10; i++)
	{
		itemButton.y = y + (i* itemButton.h);

		if (selectedItemIndex == i)
		{
			SDL_SetRenderDrawColor(renderer, 217, 43, 90, 255);
		}
		else
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}

		SDL_RenderFillRect(renderer, &itemButton);

		SDL_Texture* tempTex = nothing;

		switch (items[i])
		{
		case 1:
			tempTex = chocolate;
			break;
		case 2:
			tempTex = grenade;
			break;
		case 3:
			tempTex = atkBoost;
			break;
		case 4:
			tempTex = defBoost;
			break;
		default:
			break;
		}

		SDL_Rect textRect;
		textRect.x = itemButton.x + 2;
		textRect.y = itemButton.y + 2;

		SDL_QueryTexture(tempTex, NULL, NULL, &textRect.w, &textRect.h);

		SDL_RenderCopy(renderer, tempTex, NULL, &textRect);


	}

	if (selectedItemIndex == 10)
	{
		SDL_SetRenderDrawColor(renderer, 217, 43, 90, 255);
	}
	else
	{
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	}

	itemButton.y = y + (10* itemButton.h);

	SDL_RenderFillRect(renderer, &itemButton);

	SDL_Rect textRect;
	textRect.x = itemButton.x + 2;
	textRect.y = itemButton.y + 2;

	SDL_QueryTexture(cancel, NULL, NULL, &textRect.w, &textRect.h);

	SDL_RenderCopy(renderer, cancel, NULL, &textRect);
}
