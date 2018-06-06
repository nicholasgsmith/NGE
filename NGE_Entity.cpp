#include "NGE_Entity.h"
using namespace std;

NGE_Entity::NGE_Entity()
{
	texture = 0;
	width = 0;
	height = 0;
	centerX = 0;
	centerY = 0;
	rotation = 0;
	changeInPosition = true;
	flipped = false;

	canvasAlpha = 0;
	canvasBlue = 0;
	canvasGreen = 0;
	canvasRed = 0;

	borderWidth = 0;
	borderGreen = 0;
	borderBlue = 0;
	borderRed = 0;

	positions[0] = 0;
	positions[1] = 0;
	positions[2] = 0;
	positions[3] = 0;

	for (int i = 0; i != 8; i++)
	{
		cornerCordinates[i] = 0;
		sideEquations[i] = 0.0;
		rotated[8] = 0;
		positionData[i] = 0.0;
		positionData[i + 8] = 0.0;
	}
	positionData[16] = 0;
}

int NGE_Entity::setCanvas(int red, int green, int blue, int alpha)
{
	canvasRed = red;
	canvasGreen = green;
	canvasBlue = blue;
	canvasAlpha = alpha;
	return 0;
}

int NGE_Entity::assignTexture(NGE_Texture texture, bool setToTextureSize)
{
	//Assigns the internal entity texture to the provided texture
	//This allows us to use the texture without the texture instance
	this->texture = *texture.getTextureIDAddress();

	if (setToTextureSize)
	{
		changeInPosition = true;
		width = texture.getWidth();
		height = texture.getHeight();
	}
	return 0;
}

int NGE_Entity::setBorder(int borderWidth, int red, int green, int blue, int alpha)
{
	if (borderWidth < 0)
	{
		return -1;
	}

	borderWidth = borderWidth;
	borderRed = red;
	borderGreen = green;
	borderBlue = blue;
	borderAlpha = alpha;
	return 0;
}

int NGE_Entity::render()
{
	//If a canvas, a colored background for the entity, is set render it first so it is behind the texture
	if (canvasAlpha != 0)
	{
		NGE_RenderQuad(centerX, centerY, width, height, rotation, canvasRed, canvasGreen, canvasBlue, canvasAlpha);
	}

	//Render the texture
	if (!NGE_RenderTexture(texture, centerX, centerY, width, height, rotation, flipped) == 0)
	{
		return -1;
	}

	//If a border was set render it as 4 rectangles around the entity
	if (borderWidth != 0)
	{
		NGE_RenderQuad(centerX, centerY - (height / 2) - ((borderWidth + 1) / 2), width + (2 * borderWidth), rotation, borderWidth, borderRed, borderGreen, borderBlue, borderAlpha);
		NGE_RenderQuad(centerX, centerY + (height / 2) + ((borderWidth + 1) / 2), width + (2 * borderWidth), rotation, borderWidth, borderRed, borderGreen, borderBlue, borderAlpha);
		NGE_RenderQuad(centerX - (width / 2) - ((borderWidth + 1) / 2), centerY, borderWidth, height + (2 * borderWidth), rotation, borderRed, borderGreen, borderBlue, borderAlpha);
		NGE_RenderQuad(centerX + (width / 2) + ((borderWidth + 1) / 2), centerY, borderWidth, height + (2 * borderWidth), rotation, borderRed, borderGreen, borderBlue, borderAlpha);
	}

	return 0;
}