#ifndef NGE_EVENT_H
#define NGE_EVENT_H

using namespace std;
#include "NGE_Master.h"

//Records which external source caused the event
enum NGE_Source { NGE_SOURCE_NONE, NGE_SOURCE_MOUSE, NGE_SOURCE_KEYBOARD, NGE_SOURCE_WINDOW };

//Records for keyboards and mice which input of them was used
enum NGE_KeyboardInput { NGE_KEYBOARDINPUT_NONE, NGE_KEYBOARDINPUT_ENTER, NGE_KEYBOARDINPUT_BACKSPACE, NGE_KEYBOARDINPUT_TEXT, NGE_KEYBOARDINPUT_LEFT, NGE_KEYBOARDINPUT_RIGHT, NGE_KEYBOARDINPUT_DOWN, NGE_KEYBOARDINPUT_UP };
enum NGE_MouseButton { NGE_MOUSEBUTTON_NONE, NGE_MOUSEBUTTON_RIGHT, NGE_MOUSEBUTTON_LEFT };

//Records for each source exactly what the event was
enum NGE_MouseEventType { NGE_MOUSEEVENTTYPE_NONE, NGE_MOUSEEVENTTYPE_RELEASE, NGE_MOUSEEVENTTYPE_PRESS, NGE_MOUSEEVENTTYPE_MOTION };
enum NGE_WindowEventType { NGE_WINDOWEVENTTYPE_NONE, NGE_WINDOWEVENTTYPE_RESIZE, NGE_WINDOWEVENTTYPE_MAXIMISE, NGE_WINDOWEVENTTYPE_MINIMISE };
enum NGE_KeyboardEventType { NGE_KEYBOARDEVENTTYPE_NONE, NGE_KEYBOARDEVENTTYPE_RELEASE, NGE_KEYBOARDEVENTTYPE_PRESS };

//Stores details of an event e.g. external input
class NGE_Event
{
public:
	NGE_Event();

	//Records the source of the event
	NGE_Source source;

	//Records specifically what part of the source caused the event
	NGE_KeyboardInput keyboardInput;
	NGE_MouseButton mouseButton;

	//Records was the event
	NGE_MouseEventType mouseEventType;
	NGE_WindowEventType windowEventType;
	NGE_KeyboardEventType keyboardEventType;

	//For keyboard input, what character key was pressed
	char keyboardCharacter;

	//For mouse input, where was the cursor at the time
	int cursor_x;
	int cursor_y;

	//When did the event happen
	int timeStamp;
};


#endif