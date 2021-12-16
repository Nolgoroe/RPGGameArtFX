#include "GameManager.h"

//SDL Libs
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

int main(int argc, char** argv) 
{
	//start game
	GameManager gameManager;
	int isOK = gameManager.initGameSystems();

	//check if something somewhere went wrong
	if(isOK != 0)
	{
		cout << "Something went wrong when initting the game systems! qutting system" << endl;
		return 1;
	}
	
	return 0;
}