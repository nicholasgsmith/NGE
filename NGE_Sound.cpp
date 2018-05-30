#include "NGE_Sound.h"
using namespace std;

#include "NGE.h"

using namespace std;

class NGE_SoundBite
{
private:
	bool soundLoaded;
	Mix_Chunk *soundBite;

public:
	NGE_SoundBite();
	NGE_SoundBite(string file);
	bool isSoundLoaded();
	int loadSoundBite(string file);
	int deleteSoundBite();
	int playSound(int channel);
};
