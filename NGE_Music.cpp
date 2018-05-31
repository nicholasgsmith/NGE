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

	//Confirms that a music track hasn't been loaded and that the file we are loading from exists
	if (!musicLoaded && canOpen)
	{
		canOpen.close();
		//Loads the music from the file
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

	//Sets repeat, which will be used as a parameter later to cause the music to loop or not
	if (loopMusic)
	{
		repeat = -1;
	}
	else
	{
		repeat = 0;
	}

	//Only play music if music has been loaded
	if (musicLoaded)
	{
		//Since we can onyl play 1 music at a time, we need to stop any music already playing
		if (Mix_PlayingMusic())
		{
			Mix_HaltMusic();
		}

		//Play the music
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
		//If the music is paused and we dont want it paused resume
		if (Mix_PausedMusic() && !pause)
		{
			Mix_ResumeMusic();
		}
		else if (!Mix_PausedMusic() && pause) //If the music is not paused and we want it paused pause it
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
	//Frees memory allocated to the music file
	Mix_FreeMusic(music);
	musicLoaded = false;
	return 0;
}