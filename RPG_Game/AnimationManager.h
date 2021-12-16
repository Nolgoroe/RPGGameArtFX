#pragma once

#include "AnimationData.h"
class AnimationManager
{
public:
	AnimationData* currentAnim;
	int currentFrame;
	float frameTimer;
	bool isAnimDone;
	bool isAnimLoop;

	AnimationManager();
	~AnimationManager();

	void changeAnim(AnimationData* _Anim);
	void setAnimToLoop(bool _isLoop);
	void resetAnim();
	void update(float _deltaTime);
	void draw(int _x, int _y);

};

