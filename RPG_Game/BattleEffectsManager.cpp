#include "BattleEffectsManager.h"



BattleEffectsManager::BattleEffectsManager()
{
}


BattleEffectsManager::~BattleEffectsManager()
{
}

void BattleEffectsManager::setup(SDL_Renderer * _renderer, int _x, int _y)
{
	renderer = _renderer;
	x = _x;
	y = _y;

	// load all battle effects - path, renderer, num of frames, duration, offsetX, offsetY
	hit.setup("assets/hit.png", renderer, 4, 0.083f, 54, 107);
	heal.setup("assets/heal.png", renderer, 4, 0.083f, 54, 107);
	explode.setup("assets/explode.png", renderer, 4, 0.083f, 54, 107);
	atkBoost.setup("assets/atkBoost.png", renderer, 4, 0.083f, 31, 134);
	defBoost.setup("assets/defBoost.png", renderer, 4, 0.083f, 31, 134);
}

void BattleEffectsManager::setXY(int _x, int _y)
{
	x = _x;
	y = _y;
}

void BattleEffectsManager::doHit()
{
	// change animation object data
	animationManager.changeAnim(&hit);
	// set animation to looping (true/false)
	animationManager.setAnimToLoop(false);
	// set isDoingEffect bool
	isDoingEffect = true;
}

void BattleEffectsManager::doHeal()
{
	animationManager.changeAnim(&heal);
	animationManager.setAnimToLoop(false);
	isDoingEffect = true;

}

void BattleEffectsManager::doExplode()
{
	animationManager.changeAnim(&explode);
	animationManager.setAnimToLoop(false);
	isDoingEffect = true;

}

void BattleEffectsManager::doAtkBoost()
{
	animationManager.changeAnim(&atkBoost);
	animationManager.setAnimToLoop(false);
	isDoingEffect = true;

}

void BattleEffectsManager::doDefBoost()
{
	animationManager.changeAnim(&defBoost);
	animationManager.setAnimToLoop(false);
	isDoingEffect = true;

}

void BattleEffectsManager::update(float deltaTime)
{
	// if isDoingEffect is running - meaning we went through all the frames change isDoingEffect to false
	if (isDoingEffect)
	{
		animationManager.update(deltaTime);

		if(animationManager.isAnimDone)
		{
			isDoingEffect = false;
		}
	}
}

void BattleEffectsManager::draw()
{
	if(isDoingEffect)
	{
		animationManager.draw(x, y);
	}
}
