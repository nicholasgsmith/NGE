#ifndef NGE_WIDOW_H
#define NGE_WIDOW_H

using namespace std;

#include "NGE_Master.h"
#include <string>

//Allows for the management of a Window
class NGE_Window
{

private:
	SDL_Window* Window;
	string textureID;
	int matrixWidth, matrixHeight, matrixLength;
	int backgroundRed, backgroundGreen, backgroundBlue;
	int xResolution, yResolution;

public:
	//Creates a new window
	//The resolution is the resolution/size of the window
	//The matrix is what you render things to, it is auto-scaled to match the size of the window 
	NGE_Window(int xResolution, int yResolution, int matrixWidth, int matrixHeight, int matrixLength);
	
	//Sets the positon of the window 
	int setWindowPosition(int x, int y);

	//Sets the window to be fullscren or not
	int setWindowFullScreen(bool fullscreen);

	//Changes the size of the window
	int resiveWindow(int xResolution, int yResolution);

	//Returns the X resolution of the window
	int getWindowXResolution();

	//Returns the Y resolution of the window
	int getWindowYResolution();
	
	//Updates the viewpoint, how much of the window content you can see, to match the current size of the window
	int updateViewpointSize();

	//Sets the window to be bordered or not
	int setWindowBorder(bool border);

	//Renders to the window the current gl context and then resets the context to whatever the windows background color is
	int renderPresent();

	//Gets the X position of the cursor
	int getCursorXPosition();

	//Gets the Y position of the cursor
	int getCursorYPosition();

	//Sets the cursor to be visible or not
	int showCursor(bool cursor);

	//Sets whch part of the windows content users can currently see
	int setViewPoint(int xPosition, int yPosition, int width, int height);

	//Sets the background color of the window
	int setBackground(int red, int green, int blue);

};

#endif