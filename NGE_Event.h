#ifndef NGE_EVENT_H
#define NGE_EVENT_H

using namespace std;
#include "NGE_Master.h"

//Records which external source caused the event
enum class EventSource { none, mouse, keyboard, window };

//Records for keyboards and mice which input of them was used
enum class KeyboardInput { none, enter, backspace, text, left, right, down, up };
enum class MouseButton { none, right, left };

//Records for each source exactly what the event was
enum class MouseEvent { none, release, press, motion };
enum class WindowEvent { none, resize, maximise, minimise };
enum class KeyboardEvent { none, release, press };

//Stores details of an event e.g. external input
class NGE_Event
{
public:
	//Constucts a new, blank Event
	NGE_Event();

	//Records the source of the event
	EventSource source;

	//Records specifically what part of the source caused the event
	KeyboardInput keyboardInput;
	MouseButton mouseButton;

	//Records was the event
	MouseEvent mouseEventType;
	WindowEvent windowEventType;
	KeyboardEvent keyboardEventType;

	//For keyboard input, what character key was pressed
	char keyboardCharacter;

	//For mouse input, where was the cursor at the time
	int cursor_x;
	int cursor_y;

	//When did the event happen
	int timeStamp;
};

//Returns true if an external source has caused an event e.g. mouse button press, keyboard input, window resize
//Records the details of the event in the event parameter
bool NGE_PollEvent(NGE_Event& event);


#endif