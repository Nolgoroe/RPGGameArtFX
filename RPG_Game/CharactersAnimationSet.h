#pragma once
#include "AnimationManager.h"
#include "CharacterTypes.h"

class CharactersAnimationSet
{
public:

	int x, y;
	SDL_Renderer* renderer;
	AnimationFrame idle, attack, hit;
	AnimationManager animationManager;

	bool isDoingAction;

	CharactersAnimationSet();
	~CharactersAnimationSet();

	void setup(SDL_Renderer* _renderer, int _x, int _y, CharacterTypes _type);
	void doIdle();
	void doAttack();
	void doHit();

	void update(float deltaTime);
	void draw();
};

