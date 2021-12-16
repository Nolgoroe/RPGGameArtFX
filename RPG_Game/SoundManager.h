#pragma once
#include <vector>
#include <iostream>
#include <SDL_mixer.h>
#include <string>
#include <SDL.h>

using namespace std;

class SoundManager
{
public:
	vector<Mix_Chunk*> allSoundEffects;
	vector<Mix_Music*> allMusic;

	SoundManager();
	~SoundManager();
	
	bool pauseMusic;
	bool isPlayingMusic;

	void setup();

	void addSoundEffect(string pathToSound);
	void playSoundEffect(int soundIndex);

	void addMusicTrack(string pathToSound);
	void playMusicTrack(int soundIndex);
	void playPause();
};

