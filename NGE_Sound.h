#ifndef NGE_SOUND_H
#define NGE_SOUND_H

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
	NGE_SoundBite();
	NGE_SoundBite(string file);
	bool isSoundLoaded();
	int loadSoundBite(string file);
	int deleteSoundBite();
	int playSound(int channel);
};


#endif