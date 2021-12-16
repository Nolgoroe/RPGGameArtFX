#include "BattleManager.h"



BattleManager::BattleManager()
{
}

BattleManager::BattleManager(SDL_Renderer * _renderer, Hero * _hero, ItemMenu* _itemMenu, CharacterTypes _enemyType, SoundManager* soundManager)
{
	//if for some reason we don't have an enemy value for the enemy - set enemy to default glob
	if (_enemyType != globEnemyType && _enemyType != mimicEnemyType)
	{
		_enemyType = globEnemyType;
	}

	renderer = _renderer;
	hero = _hero;
	itemMenu = _itemMenu;

	// load fight bg textrue
	backgroundTexture = IMG_LoadTexture(renderer, "assets/bg.png");

	TTF_Font* font = TTF_OpenFont("assets/vermin_vibes_1989.ttf", 16);
	SDL_Color textColor = { 0,0,0,0 };
	SDL_Surface* textSurface = TTF_RenderText_Blended(font, _hero->getName().c_str(), textColor);
	nameTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_FreeSurface(textSurface);
	TTF_CloseFont(font);

	//decide on position and size of name rect for hero
	nameRect.x = 90;
	nameRect.y = 180;
	SDL_QueryTexture(nameTexture, NULL, NULL, &nameRect.w, &nameRect.h);

	// load animations for hero and enemy
	heroAnimSet.setup(renderer, 47, 181, heroType);
	enemyAnimSet.setup(renderer, 246, 114, _enemyType);

	//set enemy class
	if (_enemyType == globEnemyType)
	{
		enemy = new Glob_Enemy();
	}
	else if(_enemyType == mimicEnemyType)
	{
		enemy = new Mimic_Enemy();
	}

	// setup the hp rect initial value - renderer, posX and posY
	heroHPBar.setup(renderer, 90, 194);
	enemyHPBar.setup(renderer, 190, 10);

	//set up the player actipn buttons - you can set a rect directly using {} - it's a cool trick I found!
	fightButton.setup(renderer, { 0,180,80,30 }, "Fight");
	fightButton.isSelected = true;
	itemButton.setup(renderer, { 0,210,80,30 }, "Item");

	// check who takes action first
	if (hero->getAGI() > enemy->getAGI())
	{
		isHeroesTurn = true;
	}
	else
	{
		isHeroesTurn = false;
	}

	// set up the battle effect animations - renderer and position X and position Y
	// we use the enemy position just as a default value - this changes
	battleEffects.setup(renderer, enemyAnimSet.x, enemyAnimSet.y);

	// play battle music
	soundManager->playMusicTrack(1);
}


BattleManager::~BattleManager()
{
	//SDL_DestroyTexture(backgroundTexture);
	//SDL_DestroyTexture(nameTexture);
}

void BattleManager::useItem(int _itemNum)
{
	//get item num to use then call specific animation and action
	switch (_itemNum)
	{
	case 1:
		//set the position of the animation
		battleEffects.setXY(heroAnimSet.x, heroAnimSet.y);
		// do the action
		battleEffects.doHeal();
		// update the values
		hero->healAction(10);
		break;
	case 2:
		battleEffects.setXY(enemyAnimSet.x, enemyAnimSet.y);
		battleEffects.doExplode();

		// change the damage to recieve.
		// later in the code check if enemy damage to recieve is grater then 0 and then damage.
		enemyRecieveDMG = 20;
		break;
	case 3:
		battleEffects.setXY(heroAnimSet.x, heroAnimSet.y);
		battleEffects.doAtkBoost();
		hero->atkBooseAction(3);
		break;
	case 4:
		battleEffects.setXY(heroAnimSet.x, heroAnimSet.y);
		battleEffects.doDefBoost();
		hero->defBooseAction(3);
		break;
	default:
		cout << "Something went wrong" << endl;
		break;
	}

	// remove item used from list of items!
	itemMenu->getItemList()[itemMenu->selectedItemIndex] = 0;

	// change turn
	isHeroesTurn = false;
}

bool BattleManager::areAnimationsPlaying()
{
	//check if there in ANY ANIMATION running - if there is, return true
	bool isAnimating = heroAnimSet.isDoingAction || enemyAnimSet.isDoingAction || battleEffects.isDoingEffect;
	return isAnimating;
}

void BattleManager::update()
{
	// delta time calculation for smoother animations of seperate machines and seperate fps
	float deltaTime = 0;

	Uint32 lastUpdate = SDL_GetTicks();

	while (!isBattleDone)
	{
		Uint32 timeDiff = SDL_GetTicks() - lastUpdate;
		deltaTime = timeDiff / 1000.0f;
		lastUpdate = SDL_GetTicks();

		SDL_Event inputEvent;
		while (SDL_PollEvent(&inputEvent))
		{
			if (inputEvent.type == SDL_QUIT)
			{
				quitBattle = true;
			}

			if (inputEvent.type == SDL_KEYDOWN)
			{
				if (inputEvent.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				{
					quitBattle = true;
				}
				else if (inputEvent.key.keysym.scancode == SDL_SCANCODE_UP)
				{
					if (isHeroesTurn)
					{
						if (itemMenu->isVisible)
						{
							itemMenu->moveUp();
						}
						else
						{
							fightButton.isSelected = true;
							itemButton.isSelected = false;
						}
					}
				}
				else if (inputEvent.key.keysym.scancode == SDL_SCANCODE_DOWN)
				{
					if (isHeroesTurn)
					{
						if (itemMenu->isVisible)
						{
							itemMenu->moveDown();
						}
						else
						{
							fightButton.isSelected = false;
							itemButton.isSelected = true;
						}
					}
				}
				else if (inputEvent.key.keysym.scancode == SDL_SCANCODE_SPACE && inputEvent.key.repeat == 0)
				{
					if (isHeroesTurn && !areAnimationsPlaying())
					{
						if (itemMenu->isVisible)
						{
							// if selected 'cancel' or an empty slot
							if(itemMenu->selectedItemIndex == 10 || itemMenu->getItemList()[itemMenu->selectedItemIndex] == 0)
							{
								// just do nothing
							}
							else
							{
								useItem(itemMenu->getItemList()[itemMenu->selectedItemIndex]);
							}

							itemMenu->isVisible = false;
						}
						else if (fightButton.isSelected)
						{
							heroAnimSet.doAttack();
							enemyRecieveDMG = hero->getSTR();
							isHeroesTurn = false;
						}
						else if (itemButton.isSelected)
						{
							itemMenu->isVisible = true;
						}
					}

				}
			}
		}

		if (quitBattle)
		{
			isBattleDone = true;
		}

		if (!areAnimationsPlaying())
		{
			// lost condition player is dead
			if (hero->getHP() <= 0 || enemy->getHP() <= 0)
			{
				isBattleDone = true;
			}
			else if (enemyRecieveDMG > 0)
			{
				// enemy recieve damage
				enemy->takeDamage(enemyRecieveDMG);
				enemyAnimSet.doHit();
				battleEffects.setXY(enemyAnimSet.x, enemyAnimSet.y);
				battleEffects.doHit();

				//reset damage
				enemyRecieveDMG = 0;
			}
			else if (heroRecieveDMG > 0)
			{
				// hero recieve damage
				hero->takeDamage(heroRecieveDMG);
				heroAnimSet.doHit();
				battleEffects.setXY(heroAnimSet.x, heroAnimSet.y);
				battleEffects.doHit();

				//reset damage
				heroRecieveDMG = 0;
			}
			else if (!isHeroesTurn)
			{
				enemyAnimSet.doAttack();
				heroRecieveDMG = enemy->getSTR();
				isHeroesTurn = true;
			}
		}


		//update hp values for health Bars
		heroHPBar.hp = hero->getHP();
		heroHPBar.hpMax = hero->getHPMax();
		enemyHPBar.hp = enemy->getHP();
		enemyHPBar.hpMax = enemy->getHPMax();

		// update the character animations if there are any
		heroAnimSet.update(deltaTime);
		enemyAnimSet.update(deltaTime);

		// update the battle effects animations if there are any
		battleEffects.update(deltaTime);

		// draw battle screen
		draw();
	}
}

void BattleManager::draw()
{
	SDL_SetRenderDrawColor(renderer, 21, 209, 249, 255);
	SDL_RenderClear(renderer);

	SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

	// draw the chatacter animations
	enemyAnimSet.draw();
	heroAnimSet.draw();

	// white bottom ui
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_Rect bottomUI = { 0,180, 320, 60 };
	SDL_RenderFillRect(renderer, &bottomUI);

	//boarder for button ui
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(renderer, &bottomUI);


	SDL_RenderCopy(renderer, nameTexture, NULL, &nameRect);

	// draw health bars
	heroHPBar.draw();
	enemyHPBar.draw();

	// draw fight and item buttons
	fightButton.draw();
	itemButton.draw();

	// draw item menu
	itemMenu->draw();

	// draw the battle animation effects
	battleEffects.draw();

	SDL_RenderPresent(renderer);
}
