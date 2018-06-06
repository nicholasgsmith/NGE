#ifndef NGE_TEXTURE_H
#define NGE_TEXTURE_H

using namespace std;

#include "NGE_Master.h"
#include "NGE_Font.h"

#include <string>
#include <fstream>

enum class Alignment { right, left, center };

class NGE_Texture
{
private:
	bool textureLoaded;
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

	//Returns true if a texture has been loaded
	bool isTextureLoaded();

	//Returns the ID of the texture
	GLuint* getTextureIDAddress();

	//Loads a texture from a file
	int loadTextureFromFile(string file, string textureID, bool removeSpace);

	//Sets the texture to a be a singular color image of the given size
	int setTextureCanvas(int canvasWidth, int canvasHeight, GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha);

	//If a texture has been loaded, it is deleted and the memory freed
	int deleteTexture();

	//Creates a new texture which is the given text in the given font, alignment and color
	//The font is not changed by this method and can be reused
	//Any previously loaded texture will be deleted by this method
	//Set the width to 0 for the width to be set to the minimum value for the text to fit on a single line
	//Returns -1 if no font has been loaded into the font
	//Returns -2 if the provided width is too small for some characters or words in the given text
	int createText(NGE_Font& font, string text, int textureWidth, int lineSpacing, Alignment alignment, GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha);

private:
	//Renders a line of text onto a texture
	int renderTextLine(string text, Alignment alignment, int lineStartCharacter, int lineEndCharacter, int textureWidth, int textureHeight, int lineWidth, int currentLine, int lineSpacing, int letterSpacing, int wordLength, NGE_Font& font, GLubyte* alphaTexture);

};

#endif