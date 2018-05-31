#include "NGE_Font.h"
using namespace std;

#include "NGE.h"

using namespace std;

NGE_Font::NGE_Font()
{
	textSize = 0;
	largestHeight = 0;
	largestWidth = 0;
	largestYBearing = 0;
	largestDownYBearing = 0;
	fontLoaded = false;
}

NGE_Font::NGE_Font(string file, int textSize)
{
	NGE_Font();
	loadFont(file, textSize);
}

NGE_Font::~NGE_Font()
{
	deleteFont();
}

int NGE_Font::deleteFont()
{
	for (int i = 0; i < 256; i++)
	{
		delete[] characterData[i];
	}
	FT_Done_Face(face);
	fontLoaded = false;
	return 0;
}

int NGE_Font::loadFont(string file, int textSize)
{
	ifstream canOpen(file);
	if (!canOpen)
	{
		return -1;
	}
	canOpen.close();

	this->textSize = textSize;

	FT_Init_FreeType(&libary);

	//here it loops through the font and removes the data for each character
	FT_New_Face(libary, file.c_str(), 0, &face);
	FT_Set_Pixel_Sizes(face, 0, textSize);

	for (int i = 0; i < 256; ++i)
	{
		FT_Load_Char(face, i, FT_LOAD_RENDER);
		metrics[i] = face->glyph->metrics;
		int width = face->glyph->bitmap.width;
		int height = face->glyph->bitmap.rows;
		characterData[i] = new GLubyte[width*height];
		memcpy(characterData[i], face->glyph->bitmap.buffer, width*height);
		int Ybearing = metrics[i].horiBearingY / 64;
		int downYbearing = face->glyph->bitmap.rows - metrics[i].horiBearingY / 64; //
		charWidth[i] = width;
		charHeight[i] = height;
		charYBearing[i] = Ybearing;
		charDownYBearing[i] = downYbearing;
		if (width > largestWidth)
		{
			largestWidth = width;
		}
		if (Ybearing > largestYBearing)
		{
			largestYBearing = Ybearing;
		}
		if (downYbearing > largestDownYBearing)
		{
			largestDownYBearing = downYbearing;
		}
		if (largestDownYBearing + largestYBearing > largestHeight)
		{
			largestHeight = largestDownYBearing + largestYBearing;
		}
	}
	metrics[32].width = metrics[106].width;
	charWidth[32] = charWidth[106];
	fontLoaded = true;
	return 0;
}