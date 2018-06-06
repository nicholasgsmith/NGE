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

int NGE_Entity::assignTexture(NGE_Texture texture, bool setToTextureSize)
{
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
	if (canvasAlpha != 0)
	{
		NGE_RenderQuad(centerX, centerY, width, height, rotation, canvasRed, canvasGreen, canvasBlue, canvasAlpha);
	}

	if (!NGE_RenderTexture(texture, centerX, centerY, width, height, rotation, flipped) == 0)
	{
		return -1;
	}

	if (borderWidth != 0)
	{
		NGE_RenderQuad(centerX, centerY - (height / 2) - ((borderWidth + 1) / 2), width + (2 * borderWidth), rotation, borderWidth, borderRed, borderGreen, borderBlue, borderAlpha);
		NGE_RenderQuad(centerX, centerY + (height / 2) + ((borderWidth + 1) / 2), width + (2 * borderWidth), rotation, borderWidth, borderRed, borderGreen, borderBlue, borderAlpha);
		NGE_RenderQuad(centerX - (width / 2) - ((borderWidth + 1) / 2), centerY, borderWidth, height + (2 * borderWidth), rotation, borderRed, borderGreen, borderBlue, borderAlpha);
		NGE_RenderQuad(centerX + (width / 2) + ((borderWidth + 1) / 2), centerY, borderWidth, height + (2 * borderWidth), rotation, borderRed, borderGreen, borderBlue, borderAlpha);
	}

	return 0;
}