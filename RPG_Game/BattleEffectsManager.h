#pragma once
#include "AnimationManager.h"
class BattleEffectsManager
{
public:
	int x, y;
	SDL_Renderer* renderer;
	AnimationData hit, heal, explode, atkBoost, defBoost;
	AnimationManager animationManager;

	bool isDoingEffect;

	BattleEffectsManager();
	~BattleEffectsManager();

	void setup(SDL_Renderer* _renderer, int _x, int _y);
	void setXY(int _x, int _y);
	void doHit();
	void doHeal();
	void doExplode();
	void doAtkBoost();
	void doDefBoost();

	void update(float deltaTime);
	void draw();
};

