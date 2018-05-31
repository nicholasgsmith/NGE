#include "NGE_SoundBite.h"
using namespace std;

#include "NGE.h"

using namespace std;

NGE_SoundBite::NGE_SoundBite()
{
	soundLoaded = false;
}

NGE_SoundBite::NGE_SoundBite(string file)
{
	loadSoundBite(file);
}

NGE_SoundBite::~NGE_SoundBite()
{
	deleteSoundBite();
}

bool NGE_SoundBite::isSoundLoaded()
{
	return soundLoaded;
}

int NGE_SoundBite::loadSoundBite(string file)
{
	ifstream canOpen(file);

	//Confirms that a soundbite hasn't been loaded and that the file we are loading from exists
	if (!soundLoaded && canOpen)
	{
		canOpen.close();
		//Loads the soundbite from the file
		soundBite = Mix_LoadWAV(file.c_str());
		soundLoaded = true;
		return 0;
	}
	else
	{
		canOpen.close();
		return -1;
	}
}

int NGE_SoundBite::deleteSoundBite()
{
	if (soundLoaded)
	{
		//Clears the memory assigned to the soundbite
		Mix_FreeChunk(soundBite);
		soundLoaded = false;
		return 0;
	}
	else
	{
		return -1;
	}

}

int NGE_SoundBite::playSound(int channel)
{
	if (soundLoaded)
	{
		//Plays the soundbite on the provided channel
		Mix_PlayChannel(channel, soundBite, 0);
		return 0;
	}
	else
	{
		return -1;
	}
}