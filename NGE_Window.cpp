#include "NGE_Window.h"
using namespace std;

NGE_Window::NGE_Window(int xResolution, int yResolution, int matrixWidth, int matrixHeight, int matrixLength)
{
	//Create a new window context
	Window = SDL_CreateWindow("NGE_Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, xResolution, yResolution, SDL_WINDOW_OPENGL);

	//Store window size information
	xResolution = xResolution;
	yResolution = yResolution;
	matrixWidth = matrixWidth;
	matrixLength = matrixLength;
	matrixHeight = matrixHeight;

	//Allow OpenGL to edit the SDL Window
	SDL_GLContext glcontext = SDL_GL_CreateContext(Window);

	//Set up the view
	glViewport(0, 0, xResolution, yResolution);
	GLfloat gProjectionScale = 1.f;

	//Set up the matrix OpenGL will render to
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, matrixWidth, matrixHeight, 0, -matrixLength, matrixLength);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Enable blending, transparency/translucency and 2D textures
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
}

int NGE_Window::setWindowPosition(int x, int y)
{
	SDL_SetWindowPosition(Window, x, y);
	return 0;
}

int NGE_Window::setWindowFullScreen(bool fullscreen)
{
	if (fullscreen)
	{
		SDL_SetWindowFullscreen(Window, SDL_WINDOW_FULLSCREEN);
	}
	else
	{
		SDL_SetWindowFullscreen(Window, 0);
	}
	return 0;
}

int NGE_Window::resiveWindow(int xResolution, int yResolution)
{
	SDL_SetWindowSize(Window, xResolution, yResolution);
	glViewport(0, 0, xResolution, yResolution);
	glLoadIdentity();

	xResolution = xResolution;
	yResolution = yResolution;

	return 0;
}

int NGE_Window::getWindowXResolution()
{
	int yResolution, xResolution;
	SDL_GetWindowSize(Window, &xResolution, &yResolution);
	return xResolution;
}

int NGE_Window::getWindowYResolution()
{
	int yResolution, xResolution;
	SDL_GetWindowSize(Window, &xResolution, &yResolution);
	return yResolution;
}

int NGE_Window::updateViewpointSize()
{
	int yResolution, xResolution;
	SDL_GetWindowSize(Window, &xResolution, &yResolution);
	glViewport(0, 0, xResolution, yResolution);
	glLoadIdentity();

	xResolution = xResolution;
	yResolution = yResolution;
	return 0;
}

int NGE_Window::setWindowBorder(bool border)
{
	if (border)
	{
		SDL_SetWindowBordered(Window, SDL_TRUE);
	}
	else
	{
		SDL_SetWindowBordered(Window, SDL_FALSE);
	}
	return 0;
}

int NGE_Window::renderPresent()
{
	SDL_GL_SwapWindow(Window);
	//After rendering, clear the gl buffer to the windows background color
	glClearColor(backgroundRed / 255.0f, backgroundGreen / 255.0f, backgroundBlue / 255.0f, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	return 0;
}

int NGE_Window::getCursorXPosition()
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	x = x / 1.0 / xResolution*matrixWidth;
	return x;
}

int NGE_Window::getCursorYPosition()
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	y = y / 1.0 / yResolution*matrixHeight;
	return y;
}

int NGE_Window::showCursor(bool cursor)
{
	if (cursor)
	{
		SDL_ShowCursor(SDL_ENABLE);
	}
	else
	{
		SDL_ShowCursor(SDL_DISABLE);
	}
	return 0;
}

int NGE_Window::setViewPoint(int xPosition, int yPosition, int width, int height)
{
	glViewport(xPosition, yPosition, width, height);
	return 0;
}

int NGE_Window::setBackground(int red, int green, int blue)
{
	backgroundBlue = blue;
	backgroundGreen = green;
	backgroundRed = red;
	return 0;
}



