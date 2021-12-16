#include "SDL2Manager.h"


SDL2Manager::~SDL2Manager()
{
}

int SDL2Manager::initAllSdlLibs()
{
	// init all of normal SDL systems - window, renderers, rects...
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		cout << "Failed to initialize SDL2!!" << endl;
		cout << SDL_GetError() << endl;
		system("pause");
		return 1;
	}

	// set init flags for sdl_image for checkup
	int initFlags = IMG_INIT_JPG | IMG_INIT_PNG;
	int inittedFlags = IMG_Init(initFlags);

	// init SDL_Image to support flag file endings - JPG and PNG
	if ((inittedFlags & initFlags) != initFlags)
	{
		cout << "Failed to initialize JPG and PNG support!!" << endl;
		cout << IMG_GetError() << endl;
		system("pause");
		return 1;
	}

	// Init SDL_TTF
	if (TTF_Init() != 0)
	{
		cout << "Failed to initialize TTF support!!" << endl;
		cout << TTF_GetError() << endl;
		system("pause");
		return 1;
	}

	// Init SDL_Mixer with default values found on the internet
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) != 0)
	{
		cout << "Failed to initialize Mixer Sound support!!" << endl;
		cout << Mix_GetError() << endl;
		system("pause");
		return 1;
	}

	return 0;
}
