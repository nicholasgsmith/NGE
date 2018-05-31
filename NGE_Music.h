#ifndef NGE_MUSIC_H
#define NGE_MUSIC_H

using namespace std;

#include "NGE_Master.h"

#include <string>

class NGE_Music
{
private:
	bool musicLoaded;
	Mix_Music *music;

public:
	NGE_Music();
	NGE_Music(string file);
	~NGE_Music();
	int loadMusic(string file);
	int playMusic(bool loopMusic);
	int pauseMusic(bool pause);
	int stopMusic();
	int deleteMusic();
};

#endif