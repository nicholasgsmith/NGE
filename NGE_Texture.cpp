#include "NGE_Texture.h"
using namespace std;

NGE_Texture::NGE_Texture()
{
	textureLoaded = false;
	width = 0;
	height = 0;
	textureID = 0;
}

NGE_Texture::~NGE_Texture()
{
	//Frees up the memory allocated to the texture by DevIL
	deleteTexture();
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

bool NGE_Texture::isTextureLoaded()
{
	return textureLoaded;
}

GLuint* NGE_Texture::getTextureIDAddress()
{
	return &textureID;
}

int NGE_Texture::deleteTexture()
{
	if (textureLoaded)
	{
		glDeleteTextures(1, getTextureIDAddress());
		textureLoaded = false;
	}
	return 0;
}

int NGE_Texture::loadTextureFromFile(string file, string textureID, bool removeSpace)
{
	//Confirms that the file you are loading from exists
	ifstream canOpen(file);
	if (!canOpen)
	{
		return -1;
	}
	canOpen.close();

	//If a texture has already been loaded, it is deleteed before we continue
	deleteTexture();

	ILuint textureLoadedData;
	GLuint* temporaryTexturePixelsStorage;
	GLuint* texturePixels;

	//Here the image data is loaded using DevIL into a DevIL image
	glDisable(GL_DEPTH_TEST);
	ilGenImages(1, &textureLoadedData);
	ilBindImage(textureLoadedData);
	if (ilLoadImage((const ILstring)file.c_str()) == IL_FALSE)
	{
		return -1;
	}

	//We convert the image to RGBA format and obtain and width and height
	ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
	width = (GLuint)ilGetInteger(IL_IMAGE_WIDTH);
	height = (GLuint)ilGetInteger(IL_IMAGE_HEIGHT);

	//The image data is stored in an array and then the DevIL image is deleted
	int totalPixelsInTexture = width * height;
	temporaryTexturePixelsStorage = new GLuint[totalPixelsInTexture];
	memcpy(temporaryTexturePixelsStorage, ilGetData(), totalPixelsInTexture * 4);
	ilDeleteImages(1, &textureLoadedData);

	if (removeSpace)
	{
		//Here the top, bottom, left and right of the image is found so that any blank space on the image can be removed. 
		int firstRowOfTexture = 0, lastRowOfTexture = 0, firstColumnOfTexture = width, lastColumnOfTexture = 0;
		for (int i = 0; i < totalPixelsInTexture; ++i)
		{
			GLubyte* coloredVersionOfTexture = (GLubyte*)&temporaryTexturePixelsStorage[i];
			if (coloredVersionOfTexture[3] != 000)
			{
				if (firstRowOfTexture == 0)
				{
					firstRowOfTexture = (i / width) + 1;
				}

				lastRowOfTexture = (i / width) + 1;

				if (firstColumnOfTexture > (i%width) + 1)
				{
					firstColumnOfTexture = (i%width) + 1;
				}
				if (lastColumnOfTexture < (i%width) + 1)
				{
					lastColumnOfTexture = (i%width) + 1;
				}
			}
		}

		//If there is at least some pixel data then firstRowOfTexture will have been given a value. If it is still 0 then there is no pixel data.
		//If there is data then all of the relavant data is created into a texture and the texture data is stored.
		if (firstRowOfTexture != 0)
		{
			width = (lastColumnOfTexture - firstColumnOfTexture) + 1;
			height = (lastRowOfTexture - firstRowOfTexture) + 1;
			totalPixelsInTexture = width*height;
			texturePixels = new GLuint[totalPixelsInTexture];
			int i = 0;
			while (i < (lastRowOfTexture - firstRowOfTexture) + 1)
			{
				memcpy(&texturePixels[(i*((lastColumnOfTexture - firstColumnOfTexture) + 1))], &temporaryTexturePixelsStorage[((((firstRowOfTexture - 1) + i)*width) + (firstColumnOfTexture - 1))], ((lastColumnOfTexture - firstColumnOfTexture) + 1) * 4);
				i++;
			}
		}
		else
		{
			delete[] temporaryTexturePixelsStorage;
			return -1;
		}
	}
	else
	{
		texturePixels = new GLuint[totalPixelsInTexture];
	}

	//The texture data is moved from the array to be assigned to our textureID
	glBindTexture(GL_TEXTURE_2D, NULL);
	glGenTextures(1, getTextureIDAddress());
	glBindTexture(GL_TEXTURE_2D, *getTextureIDAddress());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texturePixels);
	textureLoaded = true;

	delete[] temporaryTexturePixelsStorage;
	delete[] texturePixels;
	return 0;
}

int NGE_Texture::setTextureCanvas(int canvasWidth, int canvasHeight, GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha)
{
	//If a texture has already been loaded, it is deleteed before we continue
	deleteTexture();

	//We create an array to store the canvas information
	GLuint* texturePixelData;
	texturePixelData = new GLuint[canvasWidth*canvasHeight];

	//We loop through the array and changes the color values to be what was inputted
	for (int i = 0; i < canvasWidth * canvasHeight; ++i)
	{
		GLubyte* coloredPixelData = (GLubyte*)&texturePixelData[i];
		coloredPixelData[0] = red;
		coloredPixelData[1] = green;
		coloredPixelData[2] = blue;
		coloredPixelData[3] = alpha;
	}

	//Save this array as a new texturePixelData
	glBindTexture(GL_TEXTURE_2D, NULL);
	glGenTextures(1, getTextureIDAddress());
	glBindTexture(GL_TEXTURE_2D, *getTextureIDAddress());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, canvasWidth, canvasHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, texturePixelData);
	textureLoaded = true;

	//The width and height of the texture are stored
	width = canvasWidth;
	height = canvasHeight;

	delete[] texturePixelData;
	return 0;
}