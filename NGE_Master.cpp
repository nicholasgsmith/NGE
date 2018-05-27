#include "NGE_Master.h"
using namespace std;

int NGE_Setup()
{
	//Intialise SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Init(SDL_INIT_VIDEO);

	//Intialise GLut
	char fakeParam[] = "";
	char *fakeargv[] = { fakeParam, NULL };
	int fakeargc = 1;
	glutInit(&fakeargc, fakeargv);

	//Intialise DevIL
	ilInit();

	//Intialise SDL_Mixer
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	//Setup seed for random number generation
	srand((int)time(0));

	return 0;
}

int NGE_RegulateFrameRate(int rate)
{
	//Stores the time the function was last called
	static int previousTime;

	//Works out if the time difference between this and the previous function call was too small
	int waitTime;
	waitTime = (1000 / rate) - (SDL_GetTicks() - previousTime);

	//Delays if needed
	if (waitTime > 0)
	{
		SDL_Delay(waitTime);
	}

	//Updates this to be the last time the function was called
	previousTime = SDL_GetTicks();

	return waitTime;
}

