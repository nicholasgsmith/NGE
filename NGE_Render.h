#ifndef NGE_RENDER_H
#define NGE_RENDER_H

using namespace std;
#include "NGE_Master.h"

int NGE_RenderQuad(int width, int height, int red, int green, int blue, int alpha);

int NGE_RenderTexture(GLuint texture, int centerX, int centerY, bool flipTexture);

int NGE_AdjustAxis(int centerX, int centerY, int rotation);

#endif