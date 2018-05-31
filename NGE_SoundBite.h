#ifndef NGE_SOUNDBITE_H
#define NGE_SOUNDBITE_H

using namespace std;

#include "NGE_Master.h"

#include <string>
#include <fstream>

class NGE_SoundBite
{
private:
	bool soundLoaded;
	Mix_Chunk *soundBite;

public:
	//Creates a new, blank soundbite instance
	NGE_SoundBite();

	//Creates a new soundbite instance and attempts to load a soundbite from the provided file into it
	NGE_SoundBite(string file);

	//Deletes a soundbite and unallocates memory assigned to it
	~NGE_SoundBite();

	//Returns whether the instance has had a soundbite loaded into it
	bool isSoundLoaded();

	//Loads a soundbite from a file into the instance
	int loadSoundBite(string file);

	//Deletes a loaded soundbite data from the instance
	//The instance will still exists after, but contain no data
	int deleteSoundBite();

	//Plays a soundbite if one has been loaded
	int playSound(int channel);
};


#endif