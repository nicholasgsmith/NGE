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

int NGE_Texture::createText(NGE_Font font, string text, int textureWidth, int lineSpacing, Alignment alignment, GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha)
{
	//Confirms that a font was loaded into the font instance
	if (font.isFontLoaded())
	{
		return -1;
	}

	//If a texture has already been loaded, it is deleted before we continue
	deleteTexture();

	//If the width is less than 0 nothing can fit in it
	//0 is ok, as this signals that we want the program to calulate the width for us
	if (font.largestWidth > textureWidth + 1 && textureWidth != 0)
	{
		return -2;
	}

	//We add a space at the end so that every word ends in a space for simplicity of later algorithims
	text.append(" ");
	
	//The spacing between the letters is set to a 4th of a space
	int letterSpacing = font.metrics[32].width / 256;

	//If the width was set to 0 the width is calculated such that the entire text fits on one line
	//By default we have at least 1 line
	int numberOfLines = 1;
	if (textureWidth == 0)
	{
		char character = ' ';
		int characterASCIIValue = 0;

		//The required width will just be the sum of the widths of all the letters + letter spacing
		//We do size()-1 so we dont include the space at the end
		for (unsigned int i = 0; i < text.size()-1; i++)
		{
			character = text.at(i);
			characterASCIIValue = static_cast <int> (character);
			textureWidth += font.metrics[characterASCIIValue].width / 64 + letterSpacing;
		}
	}
	else
	{
		//If the textureWidth is not 0 it must work out how many lines are needed
		char character = ' ';
		int characterASCIIValue = 0;
		int lineWidth = 0, wordLength = 0;

		for (unsigned int i = 0; i < text.size(); i++)
		{
			//It keeps adding on the length of the word it is currently going through
			character = text.at(i);
			characterASCIIValue = static_cast <int> (character);
			wordLength += font.metrics[characterASCIIValue].width / 64 + letterSpacing;

			//When there is a space is when that word has ended
			if (character == ' ')
			{
				//It checks if the word is smaller than the desired width, else it wont fit
				if (wordLength - (font.metrics[characterASCIIValue].width / 64 + letterSpacing) >= textureWidth)
				{
					return -3;
				}
				else
				{
					//It then works out whether:
					//a) it doesn't fit on that line so a new line must be started
					//b) it will fit on the same line as the previous word
					//Since we dont render spaces at the end of a line, we remove it when working out if a word will fit
					if (lineWidth + wordLength - (font.metrics[characterASCIIValue].width / 64 + letterSpacing) > textureWidth)
					{
						numberOfLines++;
						lineWidth = wordLength;
						wordLength = 0;
					}
					else
					{
						lineWidth += wordLength;
						wordLength = 0;
					}
				}
			}
		}
	}

	//Here the space is allocated to store the texture data. it is given a default value of zero.
	int textureHeight = font.largestHeight;
	int numberOfPixels = textureWidth * (numberOfLines*(lineSpacing + textureHeight));

	//We only create the text in black and white, stored in Glubytes
	//We switch this to Gluints whn we add color
	GLuint* coloredTexture = new GLuint[numberOfPixels];
	GLubyte* alphaTexture = new GLubyte[numberOfPixels];

	for (int i = 0; i < numberOfPixels; i++)
	{
		alphaTexture[i] = 000;
		coloredTexture[i] = 000;
	}

	char character = ' ';
	int characterASCIIValue = 0;
	int lineWidth = 0, wordLength = 0, lineEndCharacter = 0, lineStartCharacter = 0, oldLineEndCharacter = 0, currentLine = 0, characterWidth = 0, charStart = 0;
	bool carried = false;

	for (unsigned int i = 0; i < text.size(); i++)
	{
		//It keeps adding on the length of the word it is currently going through
		character = text.at(i);
		characterASCIIValue = static_cast <int> (character);
		wordLength += font.metrics[characterASCIIValue].width / 64 + letterSpacing;

		//When we reach a space we know the word has ended
		if (character == ' ')
		{
			//Check if we need to render the oldline (if the new word wont fir or we are at the end of the text)
			if (lineWidth + wordLength - (font.metrics[characterASCIIValue].width / 64 + letterSpacing) > textureWidth || i + 1 == text.size())
			{
				//If the word doesnt fit on the current line then the line needs to be rendered so a new line can be started

				//If the line is being rendered because we are at the end of the text, then we dont need to record anything as carried
				if (lineWidth + wordLength > textureWidth)
				{
					//We flag that a word (the one that wouldn't fit) was carried over
					lineEndCharacter = oldLineEndCharacter;
					carried = true;
				}
				else
				{
					lineEndCharacter = i;
					carried = false;
				}

				renderTextLine(text, alignment, lineStartCharacter, lineEndCharacter, textureWidth, textureHeight, lineWidth, currentLine, lineSpacing, letterSpacing, wordLength, font, alphaTexture);

				//If text was carried over then it needs to record the starting width
				if (carried == true)
				{
					lineWidth = wordLength;
				}
				else
				{
					lineWidth = 0;
				}

				lineStartCharacter = lineEndCharacter + 1;
				wordLength = 0;
				currentLine++;
			}
			else
			{
				//Nothing is done until the current line cannot store any more words or we are at the end
				lineWidth += wordLength;
				wordLength = 0;
			}

			//We record the end of a most recent word so if the next word doesnt fit we know where to start rendering from
			oldLineEndCharacter = i;

			//We render a line when it is full or when we reach the end of the text
			//If however, the final word caused the line to be full, then it will not be rendered, as only the full line will be rendered
			//In this case we render it now
			if (carried == true && i + 1 == text.size())
			{
				renderTextLine(text, alignment, lineStartCharacter, i, textureWidth, textureHeight, lineWidth, currentLine, lineSpacing, letterSpacing, wordLength, font, alphaTexture);
			}
		}
	}

	//The uncolored texture data is converted to have color
	for (int i = 0; i < numberOfPixels; i++)
	{
		GLubyte* coloredPixelData = (GLubyte*)&coloredTexture[i];
		coloredPixelData[0] = red;
		coloredPixelData[1] = green;
		coloredPixelData[2] = blue;
		coloredPixelData[3] = alphaTexture[i] / (255.0 / alpha);
	}

	//The texture is created the Gluint array
	glBindTexture(GL_TEXTURE_2D, NULL);
	glGenTextures(1, getTextureIDAddress());
	glBindTexture(GL_TEXTURE_2D, *getTextureIDAddress());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, numberOfPixels / textureWidth, 0, GL_RGBA, GL_UNSIGNED_BYTE, coloredTexture);

	//The textureWidth and textureHeight of the texture are stored
	width = textureWidth;
	height = numberOfPixels / textureWidth;

	//Arrays used to store data are deleted
	delete[] coloredTexture;
	delete[] alphaTexture;

	return 0;
}

int NGE_Texture::renderTextLine(string text, Alignment alignment, int lineStartCharacter, int lineEndCharacter, int textureWidth, int textureHeight, int lineWidth, int currentLine, int lineSpacing, int letterSpacing, int wordLength, NGE_Font& font, GLubyte* alphaTexture)
{
	int startOfLine = 0;

	//We set the starting position based of the alignment
	if (alignment == Alignment::left)
	{
		startOfLine = 0;
	}
	else if (alignment == Alignment::right)
	{
		startOfLine = textureWidth - lineWidth - wordLength;
	}
	else if (alignment == Alignment::center)
	{
		startOfLine = (textureWidth - lineWidth - wordLength) / 2;
	}

	//We render each character of the word
	int characterWidth = 0;
	for (int j = lineStartCharacter; j != lineEndCharacter; j++)
	{
		char character = text.at(j);
		int charNumber = static_cast <int> (character);
		int charStart = 0;

		//Each characters data is copied in
		for (int k = (font.largestYBearing - font.charYBearing[charNumber]) + ((textureHeight + lineSpacing)*currentLine); k != (font.largestYBearing - font.charYBearing[charNumber]) + ((textureHeight + lineSpacing)*currentLine) + font.charHeight[charNumber]; k++)
		{
			GLubyte* charBuffer = font.characterData[charNumber];
			memcpy(&alphaTexture[(k*textureWidth) + characterWidth + startOfLine + 1], &charBuffer[charStart * font.charWidth[charNumber]], font.charWidth[charNumber]);
			charStart++;
		}
		characterWidth += font.charWidth[charNumber] + letterSpacing;
	}
	return 0;
}