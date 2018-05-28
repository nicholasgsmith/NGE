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
	//Creates a new blank texture
	NGE_Texture();

	//Deletes the texture and frees up any memory allocated to it
	~NGE_Texture();

	//Sets the width of the texture
	int setWidth(int width);

	//Returns the width of the texture
	int getWidth();

	//Sets the height of the texture
	int setHeight(int height);

	//Returns the width of the texture
	int getHeight();

	//Returns the ID of the texture
	GLuint* getTextureIDAddress();
};

#endif