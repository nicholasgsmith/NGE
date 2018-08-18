#ifndef NGE_RENDER_H
#define NGE_RENDER_H

using namespace std;
#include "NGE_Master.h"

//Renders a quad of the given size and color
int NGE_RenderQuad(int width, int height, int red, int green, int blue, int alpha);

//Renders a texture of the given size and color
int NGE_RenderTexture(GLuint texture, int centerX, int centerY, bool flipTexture);

//Moves the OpenGL model matrix to have a new origin and rotation
//The origin is based off the current axis, not off the orginal
//This causes things that you render to appear at different locations, as they are all rendered at the origin
int NGE_AdjustAxis(int centerX, int centerY, int rotation);

#endif