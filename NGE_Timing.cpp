#include "NGE_Timing.h"
using namespace std;

using namespace std;

NGE_Timer::NGE_Timer()
{
	startTime = SDL_GetTicks();
	timePaused = 0;
	pauseTime = 0;
	paused = false;
}

int NGE_Timer::resetTimer()
{
	startTime = SDL_GetTicks();
	timePaused = 0;
	pauseTime = 0;
	paused = false;
	return 0;
}

int NGE_Timer::rollForwardTimer(int rollForwardAmount)
{
	//Adjust the timers start time accordingly
	startTime += rollForwardAmount;
	return 0;
}

int NGE_Timer::timePassed()
{
	//The time passed since the timer was turned on is the current time minus the time it was turned on minus any time it was paused for
	return SDL_GetTicks() - startTime - getTimePaused();
}

int NGE_Timer::pauseTimer(bool pause)
{
	//If we want to pause, pause the timer and set the time it was paused to be now
	if (pause && !paused)
	{
		pauseTime = SDL_GetTicks();
		paused = true;
	}
	else if (!pause && paused) //If we want to unpause, unpause the timer and adjust the amount of time it was paused for accordingly
	{
		timePaused += (SDL_GetTicks() - pauseTime);
		paused = false;
	}

	return 0;
}

int NGE_Timer::getTimePaused()
{
	//If the timer is currently paused, we need to include the current strecht of time it has been paused for
	if (paused)
	{
		return timePaused + (SDL_GetTicks() - pauseTime);
	}
	
	return timePaused;
}