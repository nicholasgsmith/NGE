#include "NGE_Event.h"
using namespace std;

//Constucts a blank new event
NGE_Event::NGE_Event()
{
	source = NGE_SOURCE_NONE;
	keyboardInput = NGE_KEYBOARDINPUT_NONE;
	mouseButton = NGE_MOUSEBUTTON_NONE;
	mouseEventType = NGE_MOUSEEVENTTYPE_NONE;
	windowEventType = NGE_WINDOWEVENTTYPE_NONE;
	keyboardEventType = NGE_KEYBOARDEVENTTYPE_NONE;
	keyboardCharacter = '_';
	timeStamp = 0;
	cursor_x = 0;
}
