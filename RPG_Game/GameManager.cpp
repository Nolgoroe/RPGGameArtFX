#include "GameManager.h"




GameManager::GameManager()
{
}

GameManager::~GameManager()
{
}

int GameManager::initGameSystems()
{
	// recieve user input for the name of the hero
	cout << "Please Enter Your Name!" << endl;
	string name;
	cin >> name;

	// create the player hero with basic stats
	//Hero hero;
	hero.setupStats(35, 5, 3, 2);
	hero.setName(name);

	// init SDL2 and check if init successfull
	int isOK = sdlManager.initAllSdlLibs();
	if (isOK != 0)
	{
		cout << "Something went wrong with init of SDL! - quitting system" << endl;
		return 1;
	}

	// init draw manager
	isOK = drawManager.setupDrawManager();
	if (isOK != 0)
	{
		cout << "Something went wrong with init of Draw Manager! - quitting system" << endl;
		return 1;
	}

	// setup the info box class used to display text on screen
	infoBox.setup(drawManager.getRenderer());
	infoBox.setText("Welcome To The Dungeon!");

	//init Item list - all items set to 0 which is empty
	itemMenu.initItemList();
	// setup item list UI with defult values. specific values will be set when loading combat screen
	itemMenu.setup(drawManager.getRenderer(), 0,0, &infoBox);

	// setup sound manager
	sm.setup();

	// construct the map object which will manage where icons and textures are drawn
	map = Map(drawManager.getRenderer(), &hero, &itemMenu, &infoBox, &sm);


	// call MAIN game loop
	gameLoopUpdate();

	return 0;
}

void GameManager::gameLoopUpdate()
{
	while (isGameOn)
	{
		// clear screen in order to draw new frame
		SDL_RenderClear(drawManager.getRenderer());

		// get input and player actions on map screen
		map.update();

		// get all the draw DATA for the map screen
		map.draw();

		// draw new frame
		SDL_RenderPresent(drawManager.getRenderer());

		// check if game is over
		if (map.quitGame)
		{
			isGameOn = false;
		}
	}
}
