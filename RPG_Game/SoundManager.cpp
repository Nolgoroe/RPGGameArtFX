#include "SoundManager.h"



SoundManager::SoundManager()
{
}


SoundManager::~SoundManager()
{
}

void SoundManager::setup()
{
	//load sound effects
	/// add lots of SFX

	//load music
	addMusicTrack("assets/DungeonLevel.mp3");
	addMusicTrack("assets/BattleMusic.mp3");

	playMusicTrack(0);
}

void SoundManager::addSoundEffect(string pathToSound)
{
	Mix_Chunk* tempChunk = Mix_LoadWAV(pathToSound.c_str());

	if (tempChunk != nullptr)
	{
		allSoundEffects.push_back(tempChunk);
	}
	else
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Coulden't load audio file: %s", Mix_GetError());
	}
}

void SoundManager::playSoundEffect(int soundIndex)
{
	if (soundIndex > allSoundEffects.size() - 1)
	{
		cout << "Sound outside of range!" << endl;
		return;
	}

	Mix_PlayChannel(-1, allSoundEffects[soundIndex], 0);
}

void SoundManager::addMusicTrack(string pathToSound)
{
	Mix_Music* tempMusic = Mix_LoadMUS(pathToSound.c_str());

	if(tempMusic != nullptr)
	{
		allMusic.push_back(tempMusic);
	}
	else
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Can't load music!: %s", Mix_GetError());
	}
}

void SoundManager::playMusicTrack(int soundIndex)
{
	if(soundIndex > allMusic.size())
	{
		return;
	}
	else
	{
		Mix_PlayMusic(allMusic[soundIndex], -1);
		isPlayingMusic = true;
	}
}

void SoundManager::playPause()
{
	if(isPlayingMusic && !pauseMusic)
	{
		Mix_PauseMusic();
		pauseMusic = true;
	}
	else if(isPlayingMusic && pauseMusic)
	{
		Mix_ResumeMusic();
		pauseMusic = false;
	}
	else
	{
		return;
	}
}
