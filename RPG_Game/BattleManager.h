#pragma once
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <list>

#include "Hero.h"
#include "Glob_Enemy.h"
#include "Mimic_Enemy.h"
#include "CharacterTypes.h"
#include "CharactersAnimationSet.h"
#include "HealthBar.h"
#include "ButtonManager.h"
#include "BattleEffectsManager.h"
#include "ItemMenu.h"
#include "SoundManager.h"
	
using namespace std;

class BattleManager
{
public:

	SDL_Renderer* renderer;
	SDL_Texture* backgroundTexture;

	Hero* hero;
	HealthBar heroHPBar;
	HealthBar enemyHPBar;

	ButtonManager fightButton;
	ButtonManager itemButton;

	int heroRecieveDMG = 0;
	int enemyRecieveDMG = 0;

	BattleEffectsManager battleEffects;

	Character* enemy;

	bool isBattleDone = false;
	bool quitBattle = false;
	bool isHeroesTurn;

	SDL_Texture* nameTexture;
	SDL_Rect nameRect;

	CharactersAnimationSet heroAnimSet;
	CharactersAnimationSet enemyAnimSet;

	ItemMenu* itemMenu;

	BattleManager();
	BattleManager(SDL_Renderer* _renderer, Hero* _hero, ItemMenu* _itemMenu, CharacterTypes _enemyType, SoundManager* soundManager);
	~BattleManager();

	void useItem(int _itemNum);

	bool areAnimationsPlaying();
	void update();
	void draw();
};

