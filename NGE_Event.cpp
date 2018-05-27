#include "NGE_Event.h"
using namespace std;

//Constucts a blank new SDLevent
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

void loadWindowEvent(NGE_Event& event, SDL_Event& SDLevent)
{
	event.timeStamp = SDLevent.window.timestamp;
	event.source = NGE_SOURCE_WINDOW;

	switch (SDLevent.window.event)
	{
	case SDL_WINDOWEVENT_RESIZED:
		event.windowEventType = NGE_WINDOWEVENTTYPE_RESIZE;
		break;
	case SDL_WINDOWEVENT_MAXIMIZED:
		event.windowEventType = NGE_WINDOWEVENTTYPE_MAXIMISE;
		break;
	case SDL_WINDOWEVENT_MINIMIZED:
		event.windowEventType = NGE_WINDOWEVENTTYPE_MINIMISE;
		break;
	}
}

void loadMouseMotionEvent(NGE_Event& event, SDL_Event& SDLevent)
{
	event.source = NGE_SOURCE_MOUSE;
	event.timeStamp = SDLevent.motion.timestamp;
	event.cursor_x = SDLevent.motion.x;
	event.cursor_y = SDLevent.motion.y;
	event.mouseEventType = NGE_MOUSEEVENTTYPE_MOTION;
}

void loadMousePressEvent(NGE_Event& event, SDL_Event& SDLevent)
{
	event.source = NGE_SOURCE_MOUSE;
	event.timeStamp = SDLevent.button.timestamp;
	event.cursor_x = SDLevent.button.x;
	event.cursor_y = SDLevent.button.y;

	switch (SDLevent.button.button)
	{
	case SDL_BUTTON_LEFT:
		event.mouseButton = NGE_MOUSEBUTTON_LEFT;
		break;
	case SDL_BUTTON_RIGHT:
		event.mouseButton = NGE_MOUSEBUTTON_RIGHT;
		break;
	}

	switch (SDLevent.button.state)
	{
	case SDL_RELEASED:
		event.mouseEventType = NGE_MOUSEEVENTTYPE_RELEASE;
		break;
	case SDL_PRESSED:
		event.mouseEventType = NGE_MOUSEEVENTTYPE_PRESS;
		break;
	}
}

bool loadKeyboardEvent(NGE_Event& event, SDL_Event& SDLevent)
{
	if (SDLevent.type == SDL_KEYUP)
	{
		event.keyboardEventType = NGE_KEYBOARDEVENTTYPE_RELEASE;
	}
	else if (SDLevent.type == SDL_KEYDOWN && SDLevent.key.repeat != 0)
	{
		event.keyboardEventType = NGE_KEYBOARDEVENTTYPE_PRESS;
	}
	else
	{
		return false;
	}

	event.source = NGE_SOURCE_KEYBOARD;
	event.timeStamp = SDLevent.key.timestamp;

	switch (SDLevent.key.keysym.sym)
	{
	case SDLK_BACKSPACE:
		event.keyboardInput = NGE_KEYBOARDINPUT_BACKSPACE;
		break;
	case SDLK_RETURN:
		event.keyboardInput = NGE_KEYBOARDINPUT_ENTER;
		break;
	case SDLK_DOWN:
		event.keyboardInput = NGE_KEYBOARDINPUT_DOWN;
		break;
	case SDLK_LEFT:
		event.keyboardInput = NGE_KEYBOARDINPUT_LEFT;
		break;
	case SDLK_RIGHT:
		event.keyboardInput = NGE_KEYBOARDINPUT_RIGHT;
		break;
	case SDLK_UP:
		event.keyboardInput = NGE_KEYBOARDINPUT_UP;
		break;
	case SDLK_a:
		event.keyboardInput = NGE_KEYBOARDINPUT_TEXT;
		event.keyboardCharacter = 'a';
		break;
	case SDLK_b:
		event.keyboardInput = NGE_KEYBOARDINPUT_TEXT;
		event.keyboardCharacter = 'b';
		break;
	case SDLK_c:
		event.keyboardInput = NGE_KEYBOARDINPUT_TEXT;
		event.keyboardCharacter = 'c';
		break;
	case SDLK_d:
		event.keyboardInput = NGE_KEYBOARDINPUT_TEXT;
		event.keyboardCharacter = 'd';
		break;
	case SDLK_e:
		event.keyboardInput = NGE_KEYBOARDINPUT_TEXT;
		event.keyboardCharacter = 'e';
		break;
	case SDLK_f:
		event.keyboardInput = NGE_KEYBOARDINPUT_TEXT;
		event.keyboardCharacter = 'f';
		break;
	case SDLK_g:
		event.keyboardInput = NGE_KEYBOARDINPUT_TEXT;
		event.keyboardCharacter = 'g';
		break;
	case SDLK_h:
		event.keyboardInput = NGE_KEYBOARDINPUT_TEXT;
		event.keyboardCharacter = 'h';
		break;
	case SDLK_i:
		event.keyboardInput = NGE_KEYBOARDINPUT_TEXT;
		event.keyboardCharacter = 'i';
		break;
	case SDLK_j:
		event.keyboardInput = NGE_KEYBOARDINPUT_TEXT;
		event.keyboardCharacter = 'j';
		break;
	case SDLK_k:
		event.keyboardInput = NGE_KEYBOARDINPUT_TEXT;
		event.keyboardCharacter = 'k';
		break;
	case SDLK_l:
		event.keyboardInput = NGE_KEYBOARDINPUT_TEXT;
		event.keyboardCharacter = 'l';
		break;
	case SDLK_m:
		event.keyboardInput = NGE_KEYBOARDINPUT_TEXT;
		event.keyboardCharacter = 'm';
		break;
	case SDLK_n:
		event.keyboardInput = NGE_KEYBOARDINPUT_TEXT;
		event.keyboardCharacter = 'n';
		break;
	case SDLK_o:
		event.keyboardInput = NGE_KEYBOARDINPUT_TEXT;
		event.keyboardCharacter = 'o';
		break;
	case SDLK_p:
		event.keyboardInput = NGE_KEYBOARDINPUT_TEXT;
		event.keyboardCharacter = 'p';
		break;
	case SDLK_q:
		event.keyboardInput = NGE_KEYBOARDINPUT_TEXT;
		event.keyboardCharacter = 'q';
		break;
	case SDLK_r:
		event.keyboardInput = NGE_KEYBOARDINPUT_TEXT;
		event.keyboardCharacter = 'r';
		break;
	case SDLK_s:
		event.keyboardInput = NGE_KEYBOARDINPUT_TEXT;
		event.keyboardCharacter = 's';
		break;
	case SDLK_t:
		event.keyboardInput = NGE_KEYBOARDINPUT_TEXT;
		event.keyboardCharacter = 't';
		break;
	case SDLK_u:
		event.keyboardInput = NGE_KEYBOARDINPUT_TEXT;
		event.keyboardCharacter = 'u';
		break;
	case SDLK_v:
		event.keyboardInput = NGE_KEYBOARDINPUT_TEXT;
		event.keyboardCharacter = 'v';
		break;
	case SDLK_w:
		event.keyboardInput = NGE_KEYBOARDINPUT_TEXT;
		event.keyboardCharacter = 'w';
		break;
	case SDLK_x:
		event.keyboardInput = NGE_KEYBOARDINPUT_TEXT;
		event.keyboardCharacter = 'x';
		break;
	case SDLK_y:
		event.keyboardInput = NGE_KEYBOARDINPUT_TEXT;
		event.keyboardCharacter = 'y';
		break;
	case SDLK_z:
		event.keyboardInput = NGE_KEYBOARDINPUT_TEXT;
		event.keyboardCharacter = 'z';
		break;
	}
}

bool NGE_PollEvent(NGE_Event& event)
{
	SDL_Event SDLevent;

	//Check if an ecent happened
	if (SDL_PollEvent(&SDLevent) == 1)
	{
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