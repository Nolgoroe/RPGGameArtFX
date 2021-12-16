#pragma once
#include <SDL.h>

#include <iostream>
#include <string>

using namespace std;

#define WINDOW_SIZE_W 640
#define WINDOW_SIZE_H 480
#define RENDERER_LOGICAL_SIZE_W WINDOW_SIZE_W/2
#define RENDERER_LOGICAL_SIZE_H WINDOW_SIZE_H/2

class DrawManager
{
public:
	SDL_Window* window;

	SDL_Renderer* renderer;
	DrawManager();
	~DrawManager();

	int setupDrawManager();

	SDL_Window* getWindow();
	SDL_Renderer* getRenderer();
};

