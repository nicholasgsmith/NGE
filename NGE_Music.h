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

	//Creates a blank music instance
	NGE_Music();

	//Creates a new music instance and loads music from the given file into it
	NGE_Music(string file);

	////Deletes a music instance and unallocates memory assigned to it
	~NGE_Music();

	//Loads a music track from a given file
	int loadMusic(string file);

	//Plays the given music
	//This will cause any other music playing to stop
	int playMusic(bool loopMusic);

	//Pauses or unpauses the music based off the parameter
	int pauseMusic(bool pause);

	//Stops playing the music
	int stopMusic();

	//Unallocates any memory assigned to this instance
	int deleteMusic();
};

#endif