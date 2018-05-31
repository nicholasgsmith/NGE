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

	NGE_Font();
	NGE_Font(string file, int textSize);
	~NGE_Font();
	int deleteFont();
	int loadFont(string file, int textSize);
};

#endif