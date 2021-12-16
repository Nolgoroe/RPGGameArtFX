#include "Map.h"



Map::Map(SDL_Renderer * _renderer, Hero * _hero, ItemMenu* _itemMenu, InfoBox* _infoBox, SoundManager* _sm)
{
	srand(time(NULL));	
	renderer = _renderer;
	cout << "MAP: " << renderer << endl;
	hero = _hero;
	itemMenu = _itemMenu;
	infoBox = _infoBox;
	sm = _sm;

	//set all tiles to default value
	for (int y = 0; y < 10; y++)
	{
		for (int x = 0; x < 10; x++)
		{
			map[x][y] = 0;
		}
	}

	// read map.txt file
	fstream mapFile("assets/map.txt");
	if (mapFile.is_open())
	{
		for (int y = 0; y < 10; y++)
		{
			for (int x = 0; x < 10; x++)
			{
				char tileChar;
				mapFile >> tileChar;

				switch (tileChar)
				{
					case '0':
						map[x][y] = 0; //wall
						break;
					case '1':
						map[x][y] = 1; //ground
						break;
					case 'h':
						heroIcon.type = 1;
						heroIcon.x = x;
						heroIcon.y = y;
						map[x][y] = 1; //ground
						break;
					case 'd':
						exitDungeonDoorIcon.type = 2;
						exitDungeonDoorIcon.x = x;
						exitDungeonDoorIcon.y = y;
						map[x][y] = 1; //ground
						break;
					case 'c':
					{
						MapObject chest;
						chest.type = 5;
						chest.x = x;
						chest.y = y;
						mapObjectsIcons.push_back(chest);
						map[x][y] = 1; //ground
						break;
					}
					case 'g':
					{
						MapObject globEnemy;
						globEnemy.type = 3;
						globEnemy.x = x;
						globEnemy.y = y;
						mapObjectsIcons.push_back(globEnemy);
						map[x][y] = 1; //ground
						break;
					}
					case 'm':
					{
						MapObject mimicEnemy;
						mimicEnemy.type = 4;
						mimicEnemy.x = x;
						mimicEnemy.y = y;
						mapObjectsIcons.push_back(mimicEnemy);
						map[x][y] = 1; //ground
						break;
					}
					default:
						break;
				}
			}
		}
		mapFile.close();

		// load all game map icons
		heroTexture = IMG_LoadTexture(renderer, "assets/girlTile.png");
		exitDungeonDoorTexture = IMG_LoadTexture(renderer, "assets/doorTile.png");
		globEnemyTexture = IMG_LoadTexture(renderer, "assets/globTile.png");
		chestTexture = IMG_LoadTexture(renderer, "assets/chestTile.png");

	}
}

Map::Map()
{
}

Map::~Map()
{
	/// QUESTION: ask Gaetan for explination about why is this beign called after constructor and how to stop it from happening
	//SDL_DestroyTexture(heroTexture);
	//SDL_DestroyTexture(exitDungeonDoorTexture);
	//SDL_DestroyTexture(globEnemyTexture);
	//SDL_DestroyTexture(chestTexture);
}

void Map::update()
{
	SDL_Event inputEvent;
	while (SDL_PollEvent(&inputEvent))
	{
		if (inputEvent.type == SDL_QUIT)
		{
			quitGame = true;
		}
		
		if (inputEvent.type == SDL_KEYDOWN )
		{
			// position of hero icon on map
			int heroX = heroIcon.x;
			int heroY = heroIcon.y;

			if (inputEvent.key.keysym.scancode == SDL_SCANCODE_ESCAPE) 
			{
				quitGame = true;
			}
			else if (inputEvent.key.keysym.scancode == SDL_SCANCODE_SPACE)
			{
				infoBox->visible = false;
			}

			// check if plyer still alive and there are no text boxes open = player can move
			if (!infoBox->visible && hero->getHP() > 0)
			{
				if (inputEvent.key.keysym.scancode == SDL_SCANCODE_RIGHT)
				{
					heroX++;
				}
				else if (inputEvent.key.keysym.scancode == SDL_SCANCODE_LEFT)
				{
					heroX--;
				}
				else if (inputEvent.key.keysym.scancode == SDL_SCANCODE_UP)
				{
					heroY--;
				}
				else if (inputEvent.key.keysym.scancode == SDL_SCANCODE_DOWN)
				{
					heroY++;
				}

				// limit player movement
				if (heroX >= 0 && heroX <= 9 && heroY >= 0 && heroY <= 9 && map[heroX][heroY] == 1)
				{
					heroIcon.x = heroX;
					heroIcon.y = heroY;

					//check win condition
					if (!isDoorLocked && !escapedDungeon && heroIcon.x == exitDungeonDoorIcon.x && heroIcon.y == exitDungeonDoorIcon.y)
					{
						infoBox->setText("Escaped Dungeon!!");
						infoBox->visible = true;
						escapedDungeon = true;
					}

					// check event condition for each interactable ON THE SCREEN
					for (list<MapObject>::iterator mo = mapObjectsIcons.begin(); mo != mapObjectsIcons.end(); mo++)
					{
						if (mo->active)
						{
							if (heroIcon.x == mo->x  && heroIcon.y == mo->y) 
							{
								mo->active = false;
								
								switch (mo->type)
								{
								case 3://glob enemy
								{
									// launch battle - system goes to battleManager from here to loop until battle is over
									BattleManager battle(renderer, hero, itemMenu, globEnemyType, sm);
									battle.update();

									//return to map here.. battle is over
									sm->playMusicTrack(0);

									if (battle.quitBattle)
									{
										quitGame = true;
									}
									else if(hero->getHP() <= 0)
									{
										infoBox->setText("You died!!");
										infoBox->visible = true;
									}
									break;
								}
								case 4://mimic enemy
								{
									// launch battle - system goes to battleManager from here to loop until battle is over
									BattleManager battle(renderer, hero, itemMenu, mimicEnemyType, sm);
									battle.update();

									//return to map here.. battle is over
									sm->playMusicTrack(0);

									if (battle.quitBattle)
									{
										quitGame = true;
									}
									else if (hero->getHP() <= 0)
									{
										infoBox->setText("You died!!");
										infoBox->visible = true;
									}
								}
									break;
								case 5: //chest
									// give loot from a chest - RANDOM
									itemMenu->itemFound();
									break;
								default:
									break;
								}
							}
						}
					}
				}
				else
				{
					cout << "INVALID MOVE, WTF BRO" << endl;
				}
			}
		}

	}

	// check if player can win the game = all mosters are dead and there are no visible text boxes
	if (!infoBox->visible && isDoorLocked)
	{
		bool areMonstersAlive = false;

		for (MapObject mo : mapObjectsIcons)
		{
			if (mo.type == 3 || mo.type == 4) 
			{
				if (mo.active)
				{
					areMonstersAlive = true;
					break;
				}
			}
		}

		// if ALL mosters are dead... unlock escape door
		if (!areMonstersAlive)
		{
			isDoorLocked = false;
			infoBox->setText("Escape door is unlocked!");
			infoBox->visible = true;
		}
	}

	// check lose/win condition at the end of the function to know if we must leave the game.
	// we leave the game if the player won or died
	if (!infoBox->visible && (escapedDungeon || hero->getHP() <= 0))
	{
		quitGame = true;
	}
}

void Map::draw()
{
	SDL_Rect tile = { 0,0,32,32 };

	for (int x = 0; x < 10; x++)
	{
		for (int y = 0; y < 10; y++)
		{
			if (map[x][y] == 0)
			{
				// background for walls is black
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			}

			if (map[x][y] == 1) 
			{
				// background for ground is pink
				SDL_SetRenderDrawColor(renderer, 136, 60, 100, 255);
			}

			//grid style drawing
			tile.x = x * tile.w;
			tile.y = y * tile.h;

			SDL_RenderFillRect(renderer, &tile);
		}
	}

	// draw all the map icons on screen (except hero and escape door)
	for (MapObject mo : mapObjectsIcons)
	{
		if (mo.active)
		{
			tile.x = mo.x * tile.w;
			tile.y = mo.y * tile.h;

			switch (mo.type)
			{
			case 3:
				SDL_RenderCopy(renderer, globEnemyTexture, NULL, &tile);
				break;
			case 4:
				SDL_RenderCopy(renderer, chestTexture, NULL, &tile);
				break;
			case 5:
				SDL_RenderCopy(renderer, chestTexture, NULL, &tile);
				break;
			default:
				break;
			}
		}
	}

	//draw escape door map icon
	tile.x = exitDungeonDoorIcon.x * tile.w;
	tile.y = exitDungeonDoorIcon.y * tile.h;
	SDL_RenderCopy(renderer, exitDungeonDoorTexture, NULL, &tile);

	//draw hero map icon
	tile.x = heroIcon.x * tile.w;
	tile.y = heroIcon.y * tile.h;
	SDL_RenderCopy(renderer, heroTexture, NULL, &tile);

	// draw messages that were set before the map.draw() function
	infoBox->draw();

	//SDL_RenderPresent(renderer);
}
