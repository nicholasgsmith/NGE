#include "NGE_Event.h"
using namespace std;

NGE_Event::NGE_Event()
{
	source = EventSource::none;
	keyboardInput = KeyboardInput::none;
	mouseButton = MouseButton::none;
	mouseEventType = MouseEvent::none;
	windowEventType = WindowEvent::none;
	keyboardEventType = KeyboardEvent::none;
	keyboardCharacter = '_';
	timeStamp = 0;
	cursor_x = 0;
}

void loadWindowEvent(NGE_Event& event, SDL_Event& SDLevent)
{
	//Records the window as source and the time of the event
	event.timeStamp = SDLevent.window.timestamp;
	event.source = EventSource::window;

	//Figures out and records what happened to the window to trigger the event
	switch (SDLevent.window.event)
	{
	case SDL_WINDOWEVENT_RESIZED:
		event.windowEventType = WindowEvent::resize;
		break;
	case SDL_WINDOWEVENT_MAXIMIZED:
		event.windowEventType = WindowEvent::maximise;
		break;
	case SDL_WINDOWEVENT_MINIMIZED:
		event.windowEventType = WindowEvent::minimise;
		break;
	}
}

void loadMouseMotionEvent(NGE_Event& event, SDL_Event& SDLevent)
{
	//Records the mouse as source and the time of the event
	event.source = EventSource::mouse;
	event.timeStamp = SDLevent.motion.timestamp;

	//Records the position of the cursor at the point of the event and that the event was caused by the cursor moving
	event.cursor_x = SDLevent.motion.x;
	event.cursor_y = SDLevent.motion.y;
	event.mouseEventType = MouseEvent::motion;
}

void loadMousePressEvent(NGE_Event& event, SDL_Event& SDLevent)
{
	//Records the mouse as source and the time of the event
	event.source = EventSource::mouse;
	event.timeStamp = SDLevent.button.timestamp;

	//Records the position of the cursor at the point of the event
	event.cursor_x = SDLevent.button.x;
	event.cursor_y = SDLevent.button.y;

	//Records which mouse button was used to trigger the event
	switch (SDLevent.button.button)
	{
	case SDL_BUTTON_LEFT:
		event.mouseButton = MouseButton::left;
		break;
	case SDL_BUTTON_RIGHT:
		event.mouseButton = MouseButton::right;
		break;
	}

	//Records whether the button was pressed or released
	switch (SDLevent.button.state)
	{
	case SDL_RELEASED:
		event.mouseEventType = MouseEvent::release;
		break;
	case SDL_PRESSED:
		event.mouseEventType = MouseEvent::press;
		break;
	}
}

bool loadKeyboardEvent(NGE_Event& event, SDL_Event& SDLevent)
{
	//Confirms that the event was handled by a keyboard button being pressed or released
	//Other possible keybaord events are ignored, most notably a button being continually held
	if (SDLevent.type == SDL_KEYUP)
	{
		event.keyboardEventType = KeyboardEvent::release;
	}
	else if (SDLevent.type == SDL_KEYDOWN && SDLevent.key.repeat != 0)
	{
		event.keyboardEventType = KeyboardEvent::press;
	}
	else
	{
		return false;
	}

	//Records the keyboard as source and the time of the event
	event.source = EventSource::keyboard;
	event.timeStamp = SDLevent.key.timestamp;

	//Records which key was pressed to trigger the event
	//If it was a text key, the character that was pressed is also recorded
	switch (SDLevent.key.keysym.sym)
	{
	case SDLK_BACKSPACE:
		event.keyboardInput = KeyboardInput::backspace;
		break;
	case SDLK_RETURN:
		event.keyboardInput = KeyboardInput::enter;
		break;
	case SDLK_DOWN:
		event.keyboardInput = KeyboardInput::down;
		break;
	case SDLK_LEFT:
		event.keyboardInput = KeyboardInput::left;
		break;
	case SDLK_RIGHT:
		event.keyboardInput = KeyboardInput::right;
		break;
	case SDLK_UP:
		event.keyboardInput = KeyboardInput::up;
		break;
	case SDLK_a:
		event.keyboardInput = KeyboardInput::text;
		event.keyboardCharacter = 'a';
		break;
	case SDLK_b:
		event.keyboardInput = KeyboardInput::text;
		event.keyboardCharacter = 'b';
		break;
	case SDLK_c:
		event.keyboardInput = KeyboardInput::text;
		event.keyboardCharacter = 'c';
		break;
	case SDLK_d:
		event.keyboardInput = KeyboardInput::text;
		event.keyboardCharacter = 'd';
		break;
	case SDLK_e:
		event.keyboardInput = KeyboardInput::text;
		event.keyboardCharacter = 'e';
		break;
	case SDLK_f:
		event.keyboardInput = KeyboardInput::text;
		event.keyboardCharacter = 'f';
		break;
	case SDLK_g:
		event.keyboardInput = KeyboardInput::text;
		event.keyboardCharacter = 'g';
		break;
	case SDLK_h:
		event.keyboardInput = KeyboardInput::text;
		event.keyboardCharacter = 'h';
		break;
	case SDLK_i:
		event.keyboardInput = KeyboardInput::text;
		event.keyboardCharacter = 'i';
		break;
	case SDLK_j:
		event.keyboardInput = KeyboardInput::text;
		event.keyboardCharacter = 'j';
		break;
	case SDLK_k:
		event.keyboardInput = KeyboardInput::text;
		event.keyboardCharacter = 'k';
		break;
	case SDLK_l:
		event.keyboardInput = KeyboardInput::text;
		event.keyboardCharacter = 'l';
		break;
	case SDLK_m:
		event.keyboardInput = KeyboardInput::text;
		event.keyboardCharacter = 'm';
		break;
	case SDLK_n:
		event.keyboardInput = KeyboardInput::text;
		event.keyboardCharacter = 'n';
		break;
	case SDLK_o:
		event.keyboardInput = KeyboardInput::text;
		event.keyboardCharacter = 'o';
		break;
	case SDLK_p:
		event.keyboardInput = KeyboardInput::text;
		event.keyboardCharacter = 'p';
		break;
	case SDLK_q:
		event.keyboardInput = KeyboardInput::text;
		event.keyboardCharacter = 'q';
		break;
	case SDLK_r:
		event.keyboardInput = KeyboardInput::text;
		event.keyboardCharacter = 'r';
		break;
	case SDLK_s:
		event.keyboardInput = KeyboardInput::text;
		event.keyboardCharacter = 's';
		break;
	case SDLK_t:
		event.keyboardInput = KeyboardInput::text;
		event.keyboardCharacter = 't';
		break;
	case SDLK_u:
		event.keyboardInput = KeyboardInput::text;
		event.keyboardCharacter = 'u';
		break;
	case SDLK_v:
		event.keyboardInput = KeyboardInput::text;
		event.keyboardCharacter = 'v';
		break;
	case SDLK_w:
		event.keyboardInput = KeyboardInput::text;
		event.keyboardCharacter = 'w';
		break;
	case SDLK_x:
		event.keyboardInput = KeyboardInput::text;
		event.keyboardCharacter = 'x';
		break;
	case SDLK_y:
		event.keyboardInput = KeyboardInput::text;
		event.keyboardCharacter = 'y';
		break;
	case SDLK_z:
		event.keyboardInput = KeyboardInput::text;
		event.keyboardCharacter = 'z';
		break;
	default:
		event.keyboardInput = KeyboardInput::none;
		break;
	}
	return true;
}

bool NGE_PollEvent(NGE_Event& event)
{
	SDL_Event SDLevent;

	//Check if an event happened
	if (SDL_PollEvent(&SDLevent) == 1)
	{
		//Load the details for the event based off its source
		switch (SDLevent.type)
		{
		case SDL_WINDOWEVENT:
			loadWindowEvent(event, SDLevent);
			break;

		case SDL_MOUSEMOTION:
			loadMouseMotionEvent(event, SDLevent);
			break;

		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
			loadMousePressEvent(event, SDLevent);
			break;

		case SDL_KEYDOWN:
		case SDL_KEYUP:
			if (!loadKeyboardEvent(event, SDLevent))
			{
				return false;
			}
			break;
		}
		return true;
	}

	return false;
}