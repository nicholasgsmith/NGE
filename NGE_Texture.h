#ifndef NGE_TEXTURE_H
#define NGE_TEXTURE_H

using namespace std;

#include "NGE_Master.h"

class NGE_Texture
{
private:
	int width, height;
	GLuint textureID;

public:
	NGE_Texture();
	~NGE_Texture();

	int setWidth(int width);
	int getWidth();
	int setHeight(int height);
	int getHeight();
	GLuint* getTextureIDAddress();
};

#endif