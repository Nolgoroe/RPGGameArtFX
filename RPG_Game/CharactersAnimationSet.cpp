#include "CharactersAnimationSet.h"



CharactersAnimationSet::CharactersAnimationSet()
{

}


CharactersAnimationSet::~CharactersAnimationSet()
{

}

void CharactersAnimationSet::setup(SDL_Renderer * _renderer, int _x, int _y, CharacterTypes _type)
{
	renderer = _renderer;
	x = _x;
	y = _y;

	// Load all animation files into system (path, renderer, num of frames, duration, offsetX, offsetY
	// offsetX and offsetY are offsets in the IMAGE ITSELF!
	// instead of reading the image from top left I want to read it from middle bottom since then it's less messy to set the Destination Rect later
	switch (_type)
	{
		case heroType:
			idle.setup("assets/girlIdle.png", renderer, 1, 1, 40, 132);
			attack.setup("assets/girlPunch.png", renderer, 3, 0.1f, 69, 155);
			hit.setup("assets/girlHit.png", renderer, 2, 0.1f, 47, 145);
			break;
		case globEnemyType:
			idle.setup("assets/globIdle.png", renderer, 1, 1, 36, 105);
			attack.setup("assets/globBite.png", renderer, 3, 0.1f, 93, 123);
			hit.setup("assets/globHit.png", renderer, 2, 0.1f, 62, 115);
			break;
		case mimicEnemyType:
			idle.setup("assets/mimicIdle.png", renderer, 1, 1, 53, 65);
			attack.setup("assets/mimicAttack.png", renderer, 4, 0.1f, 151, 113);
			hit.setup("assets/mimicHit.png", renderer, 2, 0.1f, 45, 69);
			break;
		default:
			break;
	}

	doIdle();
}

void CharactersAnimationSet::doIdle()
{
	animationManager.changeAnim(&idle);
	animationManager.isAnimLoop = true;
	isDoingAction = false;
}

void CharactersAnimationSet::doAttack()
{
	animationManager.changeAnim(&attack);
	animationManager.isAnimLoop = false;
	isDoingAction = true;

}

void CharactersAnimationSet::doHit()
{
	animationManager.changeAnim(&hit);
	animationManager.isAnimLoop = false;
	isDoingAction = true;

}

void CharactersAnimationSet::update(float deltaTime)
{
	animationManager.update(deltaTime);

	if (animationManager.isAnimDone && isDoingAction)
	{
		doIdle();
	}
}

void CharactersAnimationSet::draw()
{
	animationManager.draw(x, y);
}
