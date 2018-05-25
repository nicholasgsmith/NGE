#include "NGE_Window.h"
using namespace std;

int NGE_Setup()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Init(SDL_INIT_VIDEO);

	char fakeParam[] = "";
	char *fakeargv[] = { fakeParam, NULL };
	int fakeargc = 1;
	glutInit(&fakeargc, fakeargv);

	ilInit();

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	srand((int)time(0));

	return 0;
}

