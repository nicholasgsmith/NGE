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
	//Frees up any memory allocated to the instance
	deleteFont();
}

int NGE_Font::deleteFont()
{
	if (fontLoaded)
	{
		//Deletes all of the data for each loaded character
		for (int i = 0; i < 256; i++)
		{
			delete[] characterData[i];
		}

		//Frees up memory allocated to the FTT face
		FT_Done_Face(face);

		fontLoaded = false;
		return 0;
	}
	else
	{
		return -1;
	}
}

int NGE_Font::loadFont(string file, int textSize)
{
	//Confirms the file we are trying to load from is accesable
	ifstream canOpen(file);
	if (!canOpen)
	{
		return -1;
	}
	canOpen.close();

	//Confirms a font hasnt already been loaded
	if (fontLoaded)
	{
		return -1;
	}

	//Intialises the libary that will store this font
	FT_Init_FreeType(&libary);

	//Loops through the instance and clears any residual data that could be left from a previous font
	FT_New_Face(libary, file.c_str(), 0, &face);
	FT_Set_Pixel_Sizes(face, 0, textSize);

	//Loops through each character (ASCII)
	for (int i = 0; i < 256; ++i)
	{
		//Loads the character data into out FTT face
		FT_Load_Char(face, i, FT_LOAD_RENDER);

		//Loads the characters metrics and 
		metrics[i] = face->glyph->metrics;
		//Loads the characters width and height
		int width = face->glyph->bitmap.width;
		int height = face->glyph->bitmap.rows;
		//Loads the characters data
		characterData[i] = new GLubyte[width*height];
		memcpy(characterData[i], face->glyph->bitmap.buffer, width*height);
		//Gets the vertical bearings of the character
		int Ybearing = metrics[i].horiBearingY / 64;
		int downYbearing = face->glyph->bitmap.rows - metrics[i].horiBearingY / 64; 
		//Stores all the bearings, width and height of the character
		charWidth[i] = width;
		charHeight[i] = height;
		charYBearing[i] = Ybearing;
		charDownYBearing[i] = downYbearing;

		//Checks if this character has the largest width, height or bearings of any character checked so far
		//We need this information when generating text to know how much space must be provided per charcter to ensure that every character fits
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
	//32 corresponds to a space
	//By default it contains no information so we can interpret a space to be as large as we want
	//We just assign it to be the width of the letter j in this case
	metrics[32].width = metrics[106].width;
	charWidth[32] = charWidth[106];

	//We store the textsize for this font
	this->textSize = textSize;

	fontLoaded = true;
	return 0;
}