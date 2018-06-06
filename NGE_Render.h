#ifndef NGE_RENDER_H
#define NGE_RENDER_H

using namespace std;
#include "NGE_Master.h"

int NGE_RenderQuad(int centerX, int centerY, int width, int height, int rotation, int red, int green, int blue, int alpha);

int NGE_RenderTexture(GLuint texture, int centerX, int centerY, int width, int height, int rotation, bool flipTexture);

#endif