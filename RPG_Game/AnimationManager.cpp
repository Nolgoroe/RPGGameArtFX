#include "AnimationManager.h"


AnimationManager::AnimationManager()
{
	currentAnim = NULL;
	currentFrame = 0;
	frameTimer = 0;
	isAnimDone = false;
	isAnimLoop = false;
}


AnimationManager::~AnimationManager()
{

}

void AnimationManager::changeAnim(AnimationFrame * _Anim)
{
	currentAnim = _Anim;
	resetAnim();
}

void AnimationManager::setAnimToLoop(bool _isLoop)
{
	isAnimLoop = _isLoop;
}

void AnimationManager::resetAnim()
{
	currentFrame = 0;
	frameTimer = 0;
	isAnimDone = false;
}

void AnimationManager::update(float _deltaTime)
{
	if (currentAnim != NULL) 
	{
		frameTimer += _deltaTime;

		if (frameTimer >= currentAnim->frameDuration)
		{
			currentFrame++;
			frameTimer = 0;
			if (currentFrame >= currentAnim->numberOfFrames)
			{
				if (isAnimLoop)
				{
					currentFrame = 0;
				}
				else
				{
					isAnimDone = true;

					currentFrame = currentAnim->numberOfFrames - 1;
				}
			}
		}
	}
}

void AnimationManager::draw(int _x, int _y)
{
	if (currentAnim != NULL)
	{
		currentAnim->draw(currentFrame, _x, _y);
	}
}