#include "NGE_SoundChannel.h"
using namespace std;

#include "NGE.h"

using namespace std;

int pauseChannel(bool pause, int channel)
{
	if (!pause)
	{
		Mix_Resume(channel);
	}
	else
	{
		Mix_Pause(channel);
	}
	return 0;
}

int stopChannel(int channel)
{
	Mix_HaltChannel(channel);
	return 0;
}