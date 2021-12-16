#include "Map.h"



Map::Map()
{
}


Map::Map(SDL_Renderer * _renderer, Hero * _hero, int * _items)
{
	srand(time(NULL));
	
	renderer = _renderer;
	hero = _hero;
	items = _items;

	for (int y = 0; y < 10; y++)
	{
		for (int x = 0; x < 10; x++)
		{
			map[x][y] = 0;
		}
	}

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

		heroTexture = IMG_LoadTexture(renderer, "assets/girlTile.png");
		exitDungeonDoorTexture = IMG_LoadTexture(renderer, "assets/doorTile.png");
		globEnemyTexture = IMG_LoadTexture(renderer, "assets/globTile.png");
		chestTexture = IMG_LoadTexture(renderer, "assets/chestTile.png");

		infoBox.setup(renderer);
		infoBox.setText("Welcome To The Dungeon!");

		sm.setup();
	}
}

Map::~Map()
{
	SDL_DestroyTexture(heroTexture);
	SDL_DestroyTexture(exitDungeonDoorTexture);
	SDL_DestroyTexture(globEnemyTexture);
	SDL_DestroyTexture(chestTexture);
}

void Map::itemFound()
{
	int itemNum = rand() % 4 + 1;
	
	bool freeSlotFound = false;

	for (int i = 0; i < 10; i++)
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
			infoBox.setText("Found Chocolate!");
			break;
		case 2:
			infoBox.setText("Found Grenade!");

			break;
		case 3:
			infoBox.setText("Found ATK Boost!");

			break;
		case 4:
			infoBox.setText("Found DEF Boost!");
			break;
		default:
			break;
		}
	}
	else 
	{
		infoBox.setText("No free space in bag!");
	}

	infoBox.visible = true;
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
			int heroX = heroIcon.x;
			int heroY = heroIcon.y;

			if (inputEvent.key.keysym.scancode == SDL_SCANCODE_ESCAPE) 
			{
				quitGame = true;
			}
			else if (inputEvent.key.keysym.scancode == SDL_SCANCODE_SPACE)
			{
				infoBox.visible = false;
			}

			if (!infoBox.visible && hero->getHP() > 0)
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

				if (heroX >= 0 && heroX <= 9 && heroY >= 0 && heroY <= 9 && map[heroX][heroY] == 1)
				{
					heroIcon.x = heroX;
					heroIcon.y = heroY;

					if (!isDoorLocked && !escapedDungeon && heroIcon.x == exitDungeonDoorIcon.x && heroIcon.y == exitDungeonDoorIcon.y)
					{
						infoBox.setText("Escaped Dungeon!!");
						infoBox.visible = true;
						escapedDungeon = true;
					}
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
									BattleManager battle(renderer, hero, items, globEnemyType, &sm);
									battle.update();
									sm.playMusicTrack(0);

									if (battle.quitBattle)
									{
										quitGame = true;
									}
									else if(hero->getHP() <= 0)
									{
										infoBox.setText("You died!!");
										infoBox.visible = true;
									}
									break;
								}
								case 4://mimic enemy
								{
									BattleManager battle(renderer, hero, items, mimicEnemyType, &sm);
									battle.update();
									sm.playMusicTrack(0);

									if (battle.quitBattle)
									{
										quitGame = true;
									}
									else if (hero->getHP() <= 0)
									{
										infoBox.setText("You died!!");
										infoBox.visible = true;
									}
								}
									break;
								case 5: //chest
									itemFound();
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

	if (!infoBox.visible && isDoorLocked)
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

		if (!areMonstersAlive)
		{
			isDoorLocked = false;
			infoBox.setText("Escape door is unlocked!");
			infoBox.visible = true;
		}
	}

	if (!infoBox.visible && (escapedDungeon || hero->getHP() <= 0))
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
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			}

			if (map[x][y] == 1) 
			{
				SDL_SetRenderDrawColor(renderer, 136, 60, 100, 255);
			}

			tile.x = x * tile.w;
			tile.y = y * tile.h;

			SDL_RenderFillRect(renderer, &tile);
		}
	}

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

	tile.x = exitDungeonDoorIcon.x * tile.w;
	tile.y = exitDungeonDoorIcon.y * tile.h;
	SDL_RenderCopy(renderer, exitDungeonDoorTexture, NULL, &tile);

	tile.x = heroIcon.x * tile.w;
	tile.y = heroIcon.y * tile.h;
	SDL_RenderCopy(renderer, heroTexture, NULL, &tile);

	infoBox.draw();
}
