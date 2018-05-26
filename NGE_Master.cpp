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

