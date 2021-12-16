#pragma once
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

class AnimationFrame
{
public:
	int numberOfFrames;
	int frameWidth, frameHeight;
	int offsetX, offsetY; // pivot point per frame
	float frameDuration;

	SDL_Texture* spriteSheet;
	SDL_Renderer* renderer;

	void setup(string spriteSheetFile, SDL_Renderer* _renderer, int _numOfFrames, float _frameDuration, int _offsetX, int _offsetY);

	void draw(int _frame, int _x, int _y);
	AnimationFrame();
	~AnimationFrame();
};

