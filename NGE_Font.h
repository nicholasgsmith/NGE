#ifndef NGE_FONT_H
#define NGE_FONT_H

using namespace std;

#include "NGE_Master.h"

#include <string>

class NGE_Font
{
private:
	FT_Face face;
	FT_Glyph_Metrics metrics[256];
	GLubyte* characterData[255];
	GLuint charHeight[255], charWidth[255], charYBearing[255], charDownYBearing[255];
	FT_Library libary;
	int textSize, largestWidth, largestHeight, largestYBearing, largestDownYBearing;
	bool fontLoaded;

public:

	//Creates a blank font instance
	NGE_Font();

	//Creates a fonr instance and loads into it a font with the given textsize from the provided file
	NGE_Font(string file, int textSize);

	//Deletes the font and frees up any memory allocated to it
	~NGE_Font();

	//Deletes a font from the instance, freeing up any memory allocated to it
	int deleteFont();

	//Loads a font with the given textsize from the provided file
	int loadFont(string file, int textSize);
};

#endif