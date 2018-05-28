#include "NGE_Texture.h"
using namespace std;

NGE_Texture::NGE_Texture()
{
	width = 0;
	height = 0;
	textureID = 0;
}

NGE_Texture::~NGE_Texture()
{
	//Frees up the memory allocated to the texture by DevIL
	glDeleteTextures(1, getTextureIDAddress());
}

int NGE_Texture::setWidth(int width)
{
	this->width = width;
	return 0;
}

int NGE_Texture::getWidth()
{
	return width;
}

int NGE_Texture::setHeight(int height)
{
	this->height = height;
	return 0;
}

int NGE_Texture::getHeight()
{
	return height;
}

GLuint* NGE_Texture::getTextureIDAddress()
{
	return &textureID;
}