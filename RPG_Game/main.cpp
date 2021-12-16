#include <iostream>
#include <string>
#include "Character.h"
#include "Hero.h"
#include "Map.h"
#include "SoundManager.h"

//SDL Libs
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

int main(int argc, char** argv) 
{

	Hero hero;
	hero.setupStats(15, 5, 2, 2);

	cout << "Please Enter Your Name!"<< endl;
	string name;
	cin >> name;
	hero.setName(name);

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		cout << "Failed to initialize SDL2!!" << endl;
		cout << SDL_GetError() << endl;
		system("pause");
		return 1;
	}

	int initFlags = IMG_INIT_JPG | IMG_INIT_PNG;
	int inittedFlags = IMG_Init(initFlags);

	if ((inittedFlags & initFlags) != initFlags)
	{
		cout << "Failed to initialize JPG and PNG support!!" << endl;
		cout << IMG_GetError() << endl;
		system("pause");
		return 1;
	}

	if (TTF_Init() != 0)
	{
		cout << "Failed to initialize TTF support!!" << endl;
		cout << TTF_GetError() << endl;
		system("pause");
		return 1;
	}

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) != 0)
	{
		cout << "Failed to initialize Mixer Sound support!!" << endl;
		cout << Mix_GetError() << endl;
		system("pause");
		return 1;
	}

	SDL_Window* window = SDL_CreateWindow("RPG_Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,640,480,SDL_WINDOW_SHOWN);
	if(window == NULL)
	{
		cout << "Failed to initialize WINDOW!!" << endl;
		cout << SDL_GetError() << endl;
		SDL_Quit();
		system("pause");
		return 1;
	}


	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL)
	{
		cout << "Failed to initialize RENDERER!!" << endl;
		cout << SDL_GetError() << endl;
		SDL_Quit();
		system("pause");
		return 1;
	}

	SDL_RenderSetLogicalSize(renderer, 320, 240);
	SDL_Texture* testTexture = IMG_LoadTexture(renderer, "assets/girlIdle.png");

	int items[10];
	for (int i = 0; i < 10; i++)
	{
		items[i] = 0;
	}

	Map map = Map(renderer, &hero, items);


	bool isGameOn = true;

	while (isGameOn) 
	{
		SDL_SetRenderDrawColor(renderer, 23, 209, 249, 255);
		SDL_RenderClear(renderer);

		SDL_Rect srcRect;
		srcRect.x = 0;
		srcRect.y = 0;
		srcRect.w = 107;
		srcRect.h = 137;


		SDL_Rect destRect;
		destRect.x = 70;
		destRect.y = 20;
		destRect.w = 107;
		destRect.h = 137;

		SDL_RenderCopy(renderer, testTexture, &srcRect, &destRect);
		//SDL_Rect rect;
		//rect.x = 10;
		//rect.y = 10;
		//rect.w = 50;
		//rect.h = 50;
		//SDL_SetRenderDrawColor(renderer, 34, 76, 22, 255);
		//SDL_RenderFillRect(renderer, &rect);
		
		map.update();

		if (map.quitGame)
		{
			isGameOn = false;
		}

		map.draw();


		SDL_RenderPresent(renderer);

		//if (SDL_GetTicks() > 500000) 
		//{
		//	isGameOn = false;
		//}

	}

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyTexture(testTexture);
	SDL_Quit();

	system("pause");
	return 0;
}