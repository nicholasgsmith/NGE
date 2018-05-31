#ifndef NGE_SOUNDCHANNEL_H
#define NGE_SOUNDCHANNEL_H

using namespace std;

#include "NGE_Master.h"

//Pauses or unpauses a given channel based off the pause parameter
//Pausing stops any sounds playing on the channel
int pauseChannel(bool pause, int channel);

//Stops a given channel, stopping all sounds playing on it
int stopChannel(int channel);

#endif