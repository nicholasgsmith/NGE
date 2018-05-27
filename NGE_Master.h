#ifndef NGE_MASTER_H
#define NGE_MASTER_H

//SDL Libaries
#include "SDL.h"
#include <SDL_opengl.h>
#include <SDL_mixer.h>

//Glut Libary
#include "GL/freeglut.h"

//DevIL Libary
#include <IL/il.h>

//Free-Type Fonts Libaries
#include <ft2build.h> 
#include FT_FREETYPE_H
#include FT_BITMAP_H

//Standard Libaries
#include <ctime>
#include <cstdlib>

//Intialises SDL, GLut, DevIL and SDL_Mixer
//Should be run once, at the start of any program
int NGE_Setup();

//When this function is called, it works out the time difference between now and the previous time this function was called
//If this difference is too small to acheive the desired frame rate, it delays to increase the size of this gap
//e.g. if you called this function 60ms after itself, with a desired framerate of 10, it would delay 40ms, and 1s/10 = 100ms and 60ms+40ms=100ms
int NGE_RegulateFrameRate(int rate);

#endif