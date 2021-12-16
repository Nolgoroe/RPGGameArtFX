#include "DrawManager.h"



DrawManager::DrawManager()
{
}


DrawManager::~DrawManager()
{
	/// QUESTION: ask Gaetan for explination about why is this beign called after constructor and how to stop it from happening
	//SDL_DestroyWindow(getWindow());
	//SDL_DestroyRenderer(getRenderer());
	//SDL_Quit();
}

int DrawManager::setupDrawManager()
{
	// init a window for the game
	window = SDL_CreateWindow("RPG_Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_SIZE_W, WINDOW_SIZE_H, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		cout << "Failed to initialize WINDOW!!" << endl;
		cout << SDL_GetError() << endl;
		SDL_Quit();
		system("pause");
		return 1;
	}

	// init a renderer for the game - THIS WILL BE PASSED TO ALL OTHER SYSTEMS! no need for more than one renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL)
	{
		cout << "Failed to initialize RENDERER!!" << endl;
		cout << SDL_GetError() << endl;
		SDL_Quit();
		system("pause");
		return 1;
	}


	// sets the "logical size" of the renderer to be HALF the window size so that images won't get stretched.
	// it just looks better - it allows for a FIXED SCREEN RATIO to be set no matter the window size.
	SDL_RenderSetLogicalSize(renderer, RENDERER_LOGICAL_SIZE_W, RENDERER_LOGICAL_SIZE_H);

	return 0;
}

SDL_Window * DrawManager::getWindow()
{
	return window;
}

SDL_Renderer * DrawManager::getRenderer()
{
	return renderer;
}
