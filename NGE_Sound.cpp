#include "NGE_Sound.h"
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

bool NGE_SoundBite::isSoundLoaded()
{
	return soundLoaded;
}

int NGE_SoundBite::loadSoundBite(string file)
{
	ifstream canOpen(file);

	if (!soundLoaded && canOpen)
	{
		canOpen.close();
		soundBite = Mix_LoadWAV(file.c_str());
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
		Mix_PlayChannel(channel, soundBite, 0);
		return 0;
	}
	else
	{
		return -1;
	}
}