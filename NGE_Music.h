#ifndef NGE_MUSIC_H
#define NGE_MUSIC_H

using namespace std;

#include "NGE_Master.h"

#include <string>

class NGE_Music
{
private:
	bool musicPlaying;
	bool musicLoaded;
	Mix_Music *music;

public:
	NGE_Music();
	NGE_Music(string file);
	~NGE_Music();
	int loadMusic(string filename, string ID);
	int playMusic(string ID, bool loopMusic);
	int pauseMusic(bool pause);
	int stopMusic();
	int deleteMusic(string ID);
};

#endif