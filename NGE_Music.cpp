#include "NGE_Music.h"
using namespace std;

#include "NGE.h"

using namespace std;

NGE_Music::NGE_Music()
{
	music = NULL;
	musicLoaded = false;
}

NGE_Music::NGE_Music(string file)
{
	music = NULL;
	musicLoaded = false;
	loadMusic(file);
}

NGE_Music::~NGE_Music()
{
	deleteMusic();
}

int NGE_Music::loadMusic(string file)
{
	ifstream canOpen(file);

	if (!musicLoaded && canOpen)
	{
		canOpen.close();
		music = Mix_LoadMUS(file.c_str());
		musicLoaded = true;
		return 0;
	}
	else
	{
		canOpen.close();
		return -1;
	}
}

int NGE_Music::playMusic(bool loopMusic)
{
	int repeat = 0;

	if (loopMusic)
	{
		repeat = -1;
	}
	else
	{
		repeat = 0;
	}

	if (musicLoaded)
	{
		if (Mix_PlayingMusic())
		{
			Mix_HaltMusic();
		}
		Mix_PlayMusic(music, repeat);
		return 0;
	}
	else
	{
		return -1;
	}
}

int NGE_Music::pauseMusic(bool pause)
{
	if (Mix_PlayingMusic())
	{
		if (Mix_PausedMusic() && !pause)
		{
			Mix_ResumeMusic();
		}
		else if (!Mix_PausedMusic() && pause)
		{
			Mix_PauseMusic();
		}
		return 0;
	}
	else
	{
		return -1;
	}
}

int NGE_Music::stopMusic()
{
	if (Mix_PlayingMusic())
	{
		Mix_HaltMusic();
		return 0;
	}
	else
	{
		return -1;
	}
}

int NGE_Music::deleteMusic()
{
	Mix_FreeMusic(music);
	musicLoaded = false;
	return 0;
}