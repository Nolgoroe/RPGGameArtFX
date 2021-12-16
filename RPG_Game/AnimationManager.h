#pragma once

#include "AnimationFrame.h"
class AnimationManager
{
public:
	AnimationFrame* currentAnim;
	int currentFrame;
	float frameTimer;
	bool isAnimDone;
	bool isAnimLoop;

	AnimationManager();
	~AnimationManager();

	void changeAnim(AnimationFrame* _Anim);
	void setAnimToLoop(bool _isLoop);
	void resetAnim();
	void update(float _deltaTime);
	void draw(int _x, int _y);

};

