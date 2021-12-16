#include "AnimationFrame.h"




void AnimationFrame::setup(string spriteSheetFile, SDL_Renderer * _renderer, int _numOfFrames, float _frameDuration, int _offsetX, int _offsetY)
{
	renderer = _renderer;
	spriteSheet = IMG_LoadTexture(renderer, spriteSheetFile.c_str());
	int w, h;
	SDL_QueryTexture(spriteSheet, NULL, NULL, &w, &h);

	frameWidth = w / _numOfFrames;
	frameHeight = h;

	numberOfFrames = _numOfFrames;
	frameDuration = _frameDuration;
	offsetX = _offsetX;
	offsetY = _offsetY;


}

void AnimationFrame::draw(int _frame, int _x, int _y)
{
	SDL_Rect clip;
	clip.x = _frame * frameWidth;
	clip.y = 0; // no more than 1 rows per animation
	clip.w = frameWidth;
	clip.h = frameHeight;

	SDL_Rect destRect = { _x - offsetX, _y - offsetY, frameWidth, frameHeight };

	SDL_RenderCopy(renderer, spriteSheet, &clip, &destRect);
}

AnimationFrame::AnimationFrame()
{

}


AnimationFrame::~AnimationFrame()
{
	if (spriteSheet != NULL) 
	{
		SDL_DestroyTexture(spriteSheet);
	}
}