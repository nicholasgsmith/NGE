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

int NGE_Texture::NGE_CreateText(NGE_Font font, string textToTurnToTexture, int finishedTextureWidth, int lineSpacing, Alignment alignment, GLubyte redValueOfText, GLubyte greenValueOfText, GLubyte blueValueOfText, GLubyte transparencyValueOfText)
{
	//Confirms that a font was loaded into the font instance
	if (font.isFontLoaded())
	{
		return -1;
	}

	//If a texture has already been loaded, it is deleted before we continue
	deleteTexture();

	//If the width is less than  0 nothing can fit in it
	//0 is ok, as this signals that we want the program to calulate the width for us
	if (font.largestWidth > finishedTextureWidth + 1 && finishedTextureWidth != 0)
	{
		return -2;
	}

	//We add a space at the end so that every word ends in a space for simplicity
	textToTurnToTexture.append(" ");
	
	//The spacing between the letters is set to a 4th of charcter 32
	int letterSpacing = font.metrics[32].width / 256;

	//If the width was set to 0 the width is calculated such that the entire text fits on one line
	int currentNumberOfLines = 1;
	if (finishedTextureWidth == 0)
	{
		char x = ' ';
		int y = 0;

		//The required width will just be the sum of the widths of all the letters + letter spacing
		for (unsigned int i = 0; i < textToTurnToTexture.size(); i++)
		{
			x = textToTurnToTexture.at(i);
			y = static_cast <int> (x);
			finishedTextureWidth += font.metrics[y].width / 64 + letterSpacing;
		}

		//We remove the space at the end that was included earlier
		finishedTextureWidth -= font.metrics[32].width / 64;
		finishedTextureWidth -= letterSpacing;
	}
	else
	{
		//If the finishedTextureWidth is not 0 it must work out how many lines are needed
		char x = ' ';
		int y = 0;
		int currentwidth = 0, wordLength = 0;

		for (unsigned int i = 0; i < textToTurnToTexture.size(); i++)
		{
			//It keeps adding on the length of the word it is currently going through
			x = textToTurnToTexture.at(i);
			y = static_cast <int> (x);
			wordLength += font.metrics[y].width / 64 + letterSpacing;

			//When there is a space is when that word has ended
			//It checks if the word is smaller than the desired width, else it wont fit
			if (x == ' ')
			{
				if (wordLength - (font.metrics[y].width / 64 + letterSpacing) >= finishedTextureWidth)
				{
					return -3;
				}
				else
				{
					//It then works out whether:
					//a) it doesn't fit on that line so a new line must be started
					//b) it will fit on the same line as the previous word
					if (currentwidth + wordLength > finishedTextureWidth)
					{
						currentNumberOfLines++;
						currentwidth = wordLength;
						wordLength = 0;
					}
					else
					{
						currentwidth += wordLength;
						wordLength = 0;
					}
				}
			}
		}
	}

	//Here the space is allocated to store the texture data. it is given a default value of zero.
	int finishedTextureHeight = font.largestHeight;
	int numberOfPixels = finishedTextureWidth * (currentNumberOfLines*(lineSpacing + finishedTextureHeight));

	//We only create the text in black and white, stored in Glubytes
	//We switch this to Gluints whn we add color
	GLuint* coloredFinishedTexture = new GLuint[numberOfPixels];
	GLubyte* texturePixelData = new GLubyte[numberOfPixels];

	for (int i = 0; i < numberOfPixels; i++)
	{
		texturePixelData[i] = 000;
		coloredFinishedTexture[i] = 000;
	}

	char x = ' ';
	int y = 0;
	int currentwidth = 0, wordLength = 0, endDigit = 0, startDigit = 0, oldEndDigit = 0, currentLine = 0, temporaryWidth = 0, charStart = 0;
	bool carried = false;

	for (unsigned int i = 0; i < textToTurnToTexture.size(); i++)
	{
		//It keeps adding on the length of the word it is currently going through
		x = textToTurnToTexture.at(i);
		y = static_cast <int> (x);
		wordLength += font.metrics[y].width / 64 + letterSpacing;

		//When we reach a space we know the word has ended
		if (x == ' ')
		{
			//Check if we need to render the oldline (if the new word wont fir or we are at the end of the text)
			if (currentwidth + wordLength > finishedTextureWidth || i + 1 == textToTurnToTexture.size())
			{
				//If the word doesnt fit on the current line then the line needs to be rendered

				if (currentwidth + wordLength > finishedTextureWidth)
				{
					//We flag that a word (the one that wouldn't fit) was carried over
					endDigit = oldEndDigit;
					carried = true;
				}
				else
				{
					endDigit = i;
					carried = false;
				}

				//We set where to start rendering from based off the alignment of the text
				int startOfLine = 0;
				if (alignment == Alignment::left)
				{
					startOfLine = 0;
				}
				else if (alignment == Alignment::right)
				{
					startOfLine = finishedTextureWidth - currentwidth;
				}
				else if (alignment == Alignment::center)
				{
					startOfLine = (finishedTextureWidth - currentwidth) / 2;
				}

				//We render each character of the line
				temporaryWidth = 0;
				for (int j = startDigit; j != endDigit; j++)
				{
					char character = textToTurnToTexture.at(j);
					int charNumber = static_cast <int> (character);
					charStart = 0;

					//Each characters data is copied in
					for (int k = (font.largestYBearing - font.charYBearing[charNumber]) + ((finishedTextureHeight + lineSpacing)*currentLine); k != (font.largestYBearing - font.charYBearing[charNumber]) + +((finishedTextureHeight + lineSpacing)*currentLine) + font.charHeight[charNumber]; k++)
					{
						GLubyte* characterBuffer = font.characterData[charNumber];
						memcpy(&texturePixelData[(k*finishedTextureWidth) + temporaryWidth + startOfLine + 1], &characterBuffer[charStart * font.charWidth[charNumber]], font.charWidth[charNumber]);
						charStart++;
					}
					temporaryWidth += font.charWidth[charNumber] + letterSpacing;
				}

				//If text was carried over then it needs to record the starting width
				if (carried == true)
				{
					currentwidth = wordLength;
				}
				else
				{
					currentwidth = 0;
				}

				startDigit = endDigit + 1;
				wordLength = 0;
				currentLine++;
			}
			else
			{
				//Nothing is done until the current line cannot store any more words or we are at the end
				currentwidth += wordLength;
				wordLength = 0;
			}
			oldEndDigit = i;

			//We render a line when it is full or when we reach the end of the text
			//If however, the final word caused the line to be full, then it will not be rendered, as only the full line will be rendered
			//In this case we render it now
			if (carried == true && i + 1 == textToTurnToTexture.size())
			{
				endDigit = i;
				int startOfLine = 0;

				//We set the starting position based of the alignment
				if (alignment == Alignment::left)
				{
					startOfLine = 0;
				}
				else if (alignment == Alignment::right)
				{
					startOfLine = finishedTextureWidth - currentwidth - wordLength;
				}
				else if (alignment == Alignment::center)
				{
					startOfLine = (finishedTextureWidth - currentwidth - wordLength) / 2;
				}

				//We render each character of the word
				temporaryWidth = 0;
				for (int j = startDigit; j != endDigit; j++)
				{
					char character = textToTurnToTexture.at(j);
					int charNumber = static_cast <int> (character);
					charStart = 0;

					//Each characters data is copied in
					for (int k = (font.largestYBearing - font.charYBearing[charNumber]) + ((finishedTextureHeight + lineSpacing)*currentLine); k != (font.largestYBearing - font.charYBearing[charNumber]) + ((finishedTextureHeight + lineSpacing)*currentLine) + font.charHeight[charNumber]; k++)
					{
						GLubyte* characterBuffer = font.characterData[charNumber];
						memcpy(&texturePixelData[(k*finishedTextureWidth) + temporaryWidth + startOfLine + 1], &characterBuffer[charStart * font.charWidth[charNumber]], font.charWidth[charNumber]);
						charStart++;
					}
					temporaryWidth += font.charWidth[charNumber] + letterSpacing;
				}
			}
		}
	}

	//The uncolored texture data is converted to have color
	for (int i = 0; i < numberOfPixels; i++)
	{
		GLubyte* coloredPixelData = (GLubyte*)&coloredFinishedTexture[i];
		coloredPixelData[0] = redValueOfText;
		coloredPixelData[1] = greenValueOfText;
		coloredPixelData[2] = blueValueOfText;
		coloredPixelData[3] = texturePixelData[i] / (255.0 / transparencyValueOfText);
	}

	//The texture is created the Gluint array
	glBindTexture(GL_TEXTURE_2D, NULL);
	glGenTextures(1, getTextureIDAddress());
	glBindTexture(GL_TEXTURE_2D, *getTextureIDAddress());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, finishedTextureWidth, numberOfPixels / finishedTextureWidth, 0, GL_RGBA, GL_UNSIGNED_BYTE, coloredFinishedTexture);

	//The finishedTextureWidth and finishedTextureHeight of the texture are stored
	width = finishedTextureWidth;
	height = numberOfPixels / finishedTextureWidth;

	//Arrays used to store data are deleted
	delete[] coloredFinishedTexture;
	delete[] texturePixelData;

	return 0;
}