#include "ItemMenu.h"


//General function used to create and display text to screen
SDL_Texture * ItemMenu::generateTextTexture(TTF_Font * _font, SDL_Color _color, string _text, InfoBox* _infoBox)
{
	SDL_Surface* textSurface = TTF_RenderText_Blended(_font, _text.c_str(), _color);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_FreeSurface(textSurface);

	infoBox = _infoBox;

	return textTexture;
}

ItemMenu::ItemMenu()
{
}


ItemMenu::~ItemMenu()
{
	/// QUESTION: ask Gaetan for explination about why is this beign called after constructor and how to stop it from happening
	//SDL_DestroyTexture(nothing);
	//SDL_DestroyTexture(chocolate);
	//SDL_DestroyTexture(grenade);
	//SDL_DestroyTexture(atkBoost);
	//SDL_DestroyTexture(defBoost);
	//SDL_DestroyTexture(cancel);
}

void ItemMenu::setup(SDL_Renderer * _renderer, int _x, int _y, InfoBox* _infoBox)
{
	renderer = _renderer;
	x = _x;
	y = _y;
	infoBox = _infoBox;

	// load font
	TTF_Font* font = TTF_OpenFont("assets/vermin_vibes_1989.ttf", 16);
	SDL_Color textColor = { 0,0,0,0 };

	// generate and store all of the text textures for items in the variables so I won't need to load them again every time
	nothing = generateTextTexture(font, textColor, "--", infoBox);
	chocolate = generateTextTexture(font, textColor, "Chocolate", infoBox);
	grenade = generateTextTexture(font, textColor, "Grenade", infoBox);
	atkBoost = generateTextTexture(font, textColor, "Atk Boost", infoBox);
	defBoost = generateTextTexture(font, textColor, "Def Boost", infoBox);
	cancel = generateTextTexture(font, textColor, "Cancel", infoBox);

	TTF_CloseFont(font);
}

void ItemMenu::initItemList()
{
	// start the item inventory with no items (0 = no item)
	for (int i = 0; i < MAX_ITEMS_INVENTORY; i++)
	{
		items[i] = 0;
	}
}

int* ItemMenu::getItemList()
{
	return items;
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

	if (selectedItemIndex > MAX_ITEMS_INVENTORY)
	{
		selectedItemIndex = MAX_ITEMS_INVENTORY;
	}

}

void ItemMenu::draw()
{
	if (!isVisible)
	{
		return;
	}

	// size of each item button
	SDL_Rect itemButton = { x,y, 100,22 };

	//draw all the ITEM buttons - create the menu (with out the cancel button which is button number 11 which is outside of
	// array bounds which is MAX_ITEMS_INVENTORY
	for (int i = 0; i < MAX_ITEMS_INVENTORY; i++)
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

		// choose texture to load
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

		// get position of rect to load texture at
		SDL_Rect textRect;
		textRect.x = itemButton.x + 2;
		textRect.y = itemButton.y + 2;

		// get the size of the rect in width and height according to the texutre
		// chocolate is a longer word that "--" but I want the width and height of button to stay the same
		// so I query the texture and get the width and height of the rect according to the size of the word.
		SDL_QueryTexture(tempTex, NULL, NULL, &textRect.w, &textRect.h);

		//copy texture into renderer.
		// NULL here means we want all the texture - we don't want to crop/load the texture from an offset.
		// dstrect is the destination rect - the postion and the rect i want to load the texture at
		SDL_RenderCopy(renderer, tempTex, NULL, &textRect);


	}

	// Draw only the Cancel button...
	if (selectedItemIndex == MAX_ITEMS_INVENTORY)
	{
		SDL_SetRenderDrawColor(renderer, 217, 43, 90, 255);
	}
	else
	{
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	}

	// cancel button pos..
	itemButton.y = y + (MAX_ITEMS_INVENTORY * itemButton.h);

	SDL_RenderFillRect(renderer, &itemButton);

	// cancel button rect (position and size)
	SDL_Rect textRect;
	textRect.x = itemButton.x + 2;
	textRect.y = itemButton.y + 2;

	SDL_QueryTexture(cancel, NULL, NULL, &textRect.w, &textRect.h);

	//copy cancel texture into renderer
	SDL_RenderCopy(renderer, cancel, NULL, &textRect);
}

void ItemMenu::itemFound()
{
	//random between 1 and 4
	int itemNum = rand() % 4 + 1;

	bool freeSlotFound = false;

	// populate free slot with an item
	for (int i = 0; i < MAX_ITEMS_INVENTORY; i++)
	{
		if (items[i] == 0)
		{
			freeSlotFound = true;
			items[i] = itemNum;
			break;
		}
	}

	if (freeSlotFound)
	{
		switch (itemNum)
		{
		case 1:
			infoBox->setText("Found Chocolate!");
			break;
		case 2:
			infoBox->setText("Found Grenade!");

			break;
		case 3:
			infoBox->setText("Found ATK Boost!");

			break;
		case 4:
			infoBox->setText("Found DEF Boost!");
			break;
		default:
			break;
		}
	}
	else
	{
		infoBox->setText("No free space in bag!");
	}

	infoBox->visible = true;
}
