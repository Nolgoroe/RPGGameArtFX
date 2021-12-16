#include "AnimationManager.h"


AnimationManager::AnimationManager()
{
	// set default data...
	currentAnim = NULL;
	currentFrame = 0;
	frameTimer = 0;
	isAnimDone = false;
	isAnimLoop = false;
}


AnimationManager::~AnimationManager()
{

}

void AnimationManager::changeAnim(AnimationData * _Anim)
{
	// change animation 
	currentAnim = _Anim;
	//reset data to make sure we start anim from scratch
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
	// if has animation the count time
	if (currentAnim != NULL) 
	{
		frameTimer += _deltaTime;

		// if time passed greater than duration needed, move to next frame
		if (frameTimer >= currentAnim->frameDuration)
		{
			currentFrame++;
			frameTimer = 0;

			// if reached max frame and not looping then done.
			// if looping set frame back to 0 and continue
			if (currentFrame >= currentAnim->numberOfFrames)
			{
				if (isAnimLoop)
				{
					currentFrame = 0;
				}
				else
				{
					isAnimDone = true;

					// set frame to last frame to make sure we finish the animation and display the end
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