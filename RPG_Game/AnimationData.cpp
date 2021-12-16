#include "AnimationData.h"




void AnimationData::setup(string spriteSheetFile, SDL_Renderer * _renderer, int _numOfFrames, float _frameDuration, int _offsetX, int _offsetY)
{
	renderer = _renderer;

	// load sprite sheet as file
	spriteSheet = IMG_LoadTexture(renderer, spriteSheetFile.c_str());

	//get width and height of sprite sheet from the texture we loaded
	int w, h;
	SDL_QueryTexture(spriteSheet, NULL, NULL, &w, &h);

	// get the size of each frame in the animation by deviding the width by number of frames.
	frameWidth = w / _numOfFrames;
	frameHeight = h;

	numberOfFrames = _numOfFrames;
	frameDuration = _frameDuration;
	offsetX = _offsetX;
	offsetY = _offsetY;


}

void AnimationData::draw(int _frame, int _x, int _y)
{
	//srcrect is the source rect - where in the texture do we want to start reading the texture
	// NULL = all texture
	// x,y,w,h set like a small window, like a "mask" for the texture - to read part of it
	// I split the animation frames using this system

	// set rect for position and size of animation
	SDL_Rect clip;
	clip.x = _frame * frameWidth; // the position of the frame in the texture which holds all the frames
	clip.y = 0; // no more than 1 rows per animation
	clip.w = frameWidth;
	clip.h = frameHeight;

	// destination rect - the place where we want to show our animation
	// I use the offsetX and offsetY to read the file from bottom center so all the animations are centered and it's easier to work with
	SDL_Rect destRect = { _x - offsetX, _y - offsetY, frameWidth, frameHeight };

	SDL_RenderCopy(renderer, spriteSheet, &clip, &destRect);
}

AnimationData::AnimationData()
{

}


AnimationData::~AnimationData()
{
	if (spriteSheet != NULL) 
	{
		SDL_DestroyTexture(spriteSheet);
	}
}