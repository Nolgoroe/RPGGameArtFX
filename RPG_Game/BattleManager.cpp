#include "BattleManager.h"



BattleManager::BattleManager()
{
}

BattleManager::BattleManager(SDL_Renderer * _renderer, Hero * _hero, int * _items, CharacterTypes _enemyType, SoundManager* soundManager)
{

	if (_enemyType != globEnemyType && _enemyType != mimicEnemyType)
	{
		_enemyType = globEnemyType;
	}

	renderer = _renderer;
	hero = _hero;
	items = _items;

	backgroundTexture = IMG_LoadTexture(renderer, "assets/bg.png");

	TTF_Font* font = TTF_OpenFont("assets/vermin_vibes_1989.ttf", 16);
	SDL_Color textColor = { 0,0,0,0 };
	SDL_Surface* textSurface = TTF_RenderText_Blended(font, _hero->getName().c_str(), textColor);
	nameTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_FreeSurface(textSurface);
	TTF_CloseFont(font);

	nameRect.x = 90;
	nameRect.y = 180;
	SDL_QueryTexture(nameTexture, NULL, NULL, &nameRect.w, &nameRect.h);

	heroAnimSet.setup(renderer, 47, 181, heroType);
	enemyAnimSet.setup(renderer, 246, 114, _enemyType);

	if (_enemyType == globEnemyType)
	{
		enemy = new Glob_Enemy();
	}
	else if(_enemyType == mimicEnemyType)
	{
		enemy = new Mimic_Enemy();
	}

	heroHP.setup(renderer, 90, 194);
	enemyHP.setup(renderer, 190, 10);


	fightButton.setup(renderer, { 0,180,80,30 }, "Fight");
	fightButton.isSelected = true;
	itemButton.setup(renderer, { 0,210,80,30 }, "Item");

	if (hero->getAGI() > enemy->getAGI())
	{
		isHeroesTurn = true;
	}
	else
	{
		isHeroesTurn = false;
	}

	battleEffects.setup(renderer, enemyAnimSet.x, enemyAnimSet.y);


	itemMenu.setup(renderer, items, 0, 0);

	soundManager->playMusicTrack(1);
}


BattleManager::~BattleManager()
{
	SDL_DestroyTexture(backgroundTexture);
	SDL_DestroyTexture(nameTexture);
}

void BattleManager::useItem()
{
	switch (items[itemMenu.selectedItemIndex])
	{
	case 1:
		battleEffects.setXY(heroAnimSet.x, heroAnimSet.y);
		battleEffects.doHeal();
		hero->healAction(10);
		break;
	case 2:
		battleEffects.setXY(enemyAnimSet.x, enemyAnimSet.y);
		battleEffects.doExplode();
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

	items[itemMenu.selectedItemIndex] = 0;

	isHeroesTurn = false;
}

bool BattleManager::areAnimationsPlaying()
{
	bool isAnimating = heroAnimSet.isDoingAction || enemyAnimSet.isDoingAction || battleEffects.isDoingEffect;
	return isAnimating;
}

void BattleManager::update()
{
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
						if (itemMenu.isVisible)
						{
							itemMenu.moveUp();
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
						if (itemMenu.isVisible)
						{
							itemMenu.moveDown();
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
						if (itemMenu.isVisible)
						{
							if(itemMenu.selectedItemIndex == 10 || items[itemMenu.selectedItemIndex] == 0)
							{
								// just do nothing
							}
							else
							{
								useItem();
							}

							itemMenu.isVisible = false;
						}
						else if (fightButton.isSelected)
						{
							heroAnimSet.doAttack();
							enemyRecieveDMG = hero->getSTR();
							isHeroesTurn = false;
						}
						else if (itemButton.isSelected)
						{
							itemMenu.isVisible = true;
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
			if (hero->getHP() <= 0 || enemy->getHP() <= 0)
			{
				isBattleDone = true;
			}
			else if (enemyRecieveDMG > 0)
			{
				enemy->takeDamage(enemyRecieveDMG);
				enemyAnimSet.doHit();
				battleEffects.setXY(enemyAnimSet.x, enemyAnimSet.y);
				battleEffects.doHit();

				enemyRecieveDMG = 0;
			}
			else if (heroRecieveDMG > 0)
			{
				hero->takeDamage(heroRecieveDMG);
				heroAnimSet.doHit();
				battleEffects.setXY(heroAnimSet.x, heroAnimSet.y);
				battleEffects.doHit();

				heroRecieveDMG = 0;
			}
			else if (!isHeroesTurn)
			{
				enemyAnimSet.doAttack();
				heroRecieveDMG = enemy->getSTR();
				isHeroesTurn = true;
			}
		}

		heroAnimSet.update(deltaTime);
		enemyAnimSet.update(deltaTime);


		heroHP.hp = hero->getHP();
		heroHP.hpMax = hero->getHPMax();

		enemyHP.hp = enemy->getHP();
		enemyHP.hpMax = enemy->getHPMax();


		battleEffects.update(deltaTime);

		draw();
	}
}

void BattleManager::draw()
{
	SDL_SetRenderDrawColor(renderer, 21, 209, 249, 255);
	SDL_RenderClear(renderer);

	SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

	enemyAnimSet.draw();
	heroAnimSet.draw();

	// white bottom ui
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_Rect bottomUI = { 0,180, 320, 60 };
	SDL_RenderFillRect(renderer, &bottomUI);

	//boarder
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(renderer, &bottomUI);


	SDL_RenderCopy(renderer, nameTexture, NULL, &nameRect);

	heroHP.draw();
	enemyHP.draw();


	fightButton.draw();
	itemButton.draw();

	itemMenu.draw();

	battleEffects.draw();

	SDL_RenderPresent(renderer);
}
