#ifndef NGE_TIMING_H
#define NGE_TIMING_H

using namespace std;

#include "NGE_Master.h"

//Creates a Timer which can be used to determine how much time has passed between events
//All values are in milli-seconds
class NGE_Timer
{
private:
	int timePaused;
	int pauseTime;
	int startTime;
	bool paused;

public:
	//Creates a new timer. Its default start time is whatever time it is now
	NGE_Timer();

	//Sets the timers start time to now, unpauses the timer and clears all pause-time logs
	int resetTimer();

	//Moves the time the timer was started forward by a certain amount
	//You can pass a negative integer to move the start time backwards instead
	int rollForwardTimer(int rollForwardAmount);

	//Gets the amount of time since the start time of the timer that it hasnt been paused
	//It can return a negative value if the start time was in the future, if set via rollForwardTimer
	//Addtionally, since any time paused is deducted from the timer, if the time paused > (current time - start time) then it can also be negative
	//Again, you would need to use rollForwardTimer to make this happen
	int timePassed();

	//Sets the timer to be paused or not
	//While paused, the amount of time the timer records as having passed does not increase
	int pauseTimer(bool paused);

	//Returns the amount of time the timer has been paused
	//This is deducted from the time amount when using timePassed
	//It is reset by resetTimer
	int getTimePaused();
};

#endif