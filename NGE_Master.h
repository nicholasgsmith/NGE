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

#endif