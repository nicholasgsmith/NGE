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
	changeInRotation = true;
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

int NGE_Entity::setWidth(int width)
{
	width = width;
	changeInPosition = true;
	return 0;
}

int NGE_Entity::getWidth()
{
	return width;
}

int NGE_Entity::setHeight(int height)
{
	height = height;
	changeInPosition = true;
	return 0;
}

int NGE_Entity::getHeight()
{
	return height;
}

int NGE_Entity::setSides(int width, int height)
{
	setHeight(height);
	setWidth(width);
	return 0;
}

int NGE_Entity::adjustWidth(int amount)
{
	changeInPosition = true;
	width = amount;
	return 0;
}

int NGE_Entity::adjustHeight(int amount)
{
	changeInPosition = true;
	height = amount;
	return 0;
}

int NGE_Entity::setCenterX(int centerX)
{
	changeInPosition = true;
	centerX = centerX;
	return 0;
}

int NGE_Entity::getCenterX()
{
	return centerX;
}

int NGE_Entity::setCenterY(int centerY)
{
	changeInPosition = true;
	centerY = centerY;
	return 0;
}

int NGE_Entity::getCenterY()
{
	return centerY;
}

int NGE_Entity::setCenter(int centerX, int centerY)
{
	setCenterX(centerX);
	setCenterY(centerY);
	return 0;
}

int NGE_Entity::translate(Direction direction, int amount)
{
	changeInPosition = true;
	if (direction == Direction::left)
	{
		centerX -= amount;
	}
	else if (direction == Direction::right)
	{
		centerX += amount;
	}
	else if (direction == Direction::up)
	{
		centerY -= amount;
	}
	else if (direction == Direction::down)
	{
		centerY += amount;
	}
	return 0;
}

int NGE_Entity::setRotation(int rotation)
{
	changeInRotation = true;
	rotation = rotation;
	rotation %= 360;
	return 0;
}

int NGE_Entity::getRotation()
{
	return rotation;
}

int NGE_Entity::rotate(int amount)
{
	changeInRotation = true;
	rotation += amount;
	rotation %= 360;
	return 0;
}

int NGE_Entity::setPosition(int centerX, int centerY, int width, int height, int rotation)
{
	setCenterX(centerX);
	setCenterY(centerY);
	setRotation(rotation);
	setHeight(height);
	setWidth(width);
	return 0;
}

int NGE_Entity::setFlip(bool flipped)
{
	flipped = flipped;
	return 0;
}

bool NGE_Entity::getFlip()
{
	return flipped;
}

int NGE_Entity::swapFlip()
{
	if (flipped)
	{
		flipped = false;
	}
	else
	{
		flipped = true;
	}
	return 0;
}

void NGE_Entity::calculatePositionData()
{
	if (changeInPosition)
	{
		positions[0] = centerX - (width / 2);
		positions[1] = centerY - (height / 2);
		positions[2] = centerX + (width / 2);
		positions[3] = centerY + (height / 2);
	}

	if (changeInPosition || changeInRotation)
	{
		if (rotation == 0)
		{
			rotated[0] = positions[0];
			rotated[1] = positions[1];
			rotated[2] = positions[0];
			rotated[3] = positions[3];
			rotated[4] = positions[2];
			rotated[5] = positions[3];
			rotated[6] = positions[2];
			rotated[7] = positions[1];
		}
		else
		{
			double cosValue = cos(RADIANS(rotation));
			double sinValue = sin(RADIANS(rotation));
			rotated[0] = (int)((positions[0] - centerX)*cosValue - ((positions[1] - centerY)*sinValue)) + centerX;
			rotated[1] = (int)((positions[0] - centerX)*sinValue + ((positions[1] - centerY)*cosValue)) + centerY;
			rotated[2] = (int)((positions[0] - centerX)*cosValue - ((positions[3] - centerY)*sinValue)) + centerX;
			rotated[3] = (int)((positions[0] - centerX)*sinValue + ((positions[3] - centerY)*cosValue)) + centerY;
			rotated[4] = (int)((positions[2] - centerX)*cosValue - ((positions[3] - centerY)*sinValue)) + centerX;
			rotated[5] = (int)((positions[2] - centerX)*sinValue + ((positions[3] - centerY)*cosValue)) + centerY;
			rotated[6] = (int)((positions[2] - centerX)*cosValue - ((positions[1] - centerY)*sinValue)) + centerX;
			rotated[7] = (int)((positions[2] - centerX)*sinValue + ((positions[1] - centerY)*cosValue)) + centerY;
		}

		if (rotation % 90 != 0)
		{
			sideEquations[0] = ((float) rotated[1] - rotated[7]) / (rotated[0] - rotated[6]);
			sideEquations[4] = sideEquations[0];
			sideEquations[2] = ((float) rotated[1] - rotated[3]) / (rotated[0] - rotated[2]);
			sideEquations[6] = sideEquations[2];
			sideEquations[1] = rotated[1] - (sideEquations[0] * rotated[0]);
			sideEquations[3] = rotated[1] - (sideEquations[2] * rotated[0]);
			sideEquations[5] = rotated[5] - (sideEquations[4] * rotated[4]);
			sideEquations[7] = rotated[5] - (sideEquations[6] * rotated[4]);
		}
	}

	changeInRotation = false;
	changeInPosition = false;
}

float* NGE_Entity::getPositionData()
{
	calculatePositionData();

	int i = 0;

	for (i = 0; i != 8; i++)
	{
		positionData[i] = (float)rotated[i];
	}

	for (i = 8; i != 16; i++)
	{
		positionData[i] = sideEquations[i - 8];
	}

	positionData[16] = (float)rotation;

	return positionData;
}

bool NGE_Entity::touch(int x, int y)
{
	calculatePositionData();

	switch (rotation)
	{
		case 0:
			if (((x > rotated[0]) && (x < rotated[4]) && (y > rotated[1]) && (y < rotated[5])))
			{
				return true;
			}
			break;
		case 180:
			if (((x > rotated[4]) && (x < rotated[0]) && (y > rotated[5]) && (y < rotated[1])))
			{
				return true;
			}
			break;
		case 90:
			if (((x > rotated[4]) && (x < rotated[0]) && (y > rotated[1]) && (y < rotated[5])))
			{
				return 1;
			}
			break;
		case 270:
			if (((x > rotated[0]) && (x < rotated[4]) && (y > rotated[5]) && (y < rotated[1])))
			{
				return true;
			}
			break;
		default:
			if (rotation > 0 && rotation < 90)
			{
				if ((sideEquations[0] * x) + sideEquations[1] < y && (sideEquations[2] * x) + sideEquations[3] < y && (sideEquations[4] * x) + sideEquations[5] > y && (sideEquations[6] * x) + sideEquations[7] > y)
				{
					return true;
				}
			}
			else if (rotation > 90 && rotation < 180)
			{
				if ((sideEquations[0] * x) + sideEquations[1] > y && (sideEquations[2] * x) + sideEquations[3] < y && (sideEquations[4] * x) + sideEquations[5] < y && (sideEquations[6] * x) + sideEquations[7] > y)
				{
					return true;
				}
			}
			else if (rotation > 180 && rotation < 270)
			{
				if ((sideEquations[0] * x) + sideEquations[1] > y && (sideEquations[2] * x) + sideEquations[3] > y && (sideEquations[4] * x) + sideEquations[5] < y && (sideEquations[6] * x) + sideEquations[7] < y)
				{
					return true;
				}
			}
			else if (rotation > 270 && rotation < 360)
			{
				if ((sideEquations[0] * x) + sideEquations[1] < y && (sideEquations[2] * x) + sideEquations[3] > y && (sideEquations[4] * x) + sideEquations[5] > y && (sideEquations[6] * x) + sideEquations[7] < y)
				{
					return true;
				}
			}
			break;
	}

	return false;
}

bool NGE_Entity::staticCollision(NGE_Entity& collider)
{
	float* colliderData = collider.getPositionData();
	
	calculatePositionData();

	if (touch((int)colliderData[0], (int)colliderData[1]))
	{
		return true;
	}
	else if (touch((int)colliderData[2], (int)colliderData[3]))
	{
		return true;
	}
	else if (touch((int)colliderData[4], (int)colliderData[5]))
	{
		return true;
	}
	else if (touch((int)colliderData[6], (int)colliderData[7]))
	{
		return true;
	}
	else if (collider.touch((int)positionData[0], (int)positionData[1]))
	{
		return true;
	}
	else if (collider.touch((int)positionData[2], (int)positionData[3]))
	{
		return true;
	}
	else if (collider.touch((int)positionData[4], (int)positionData[5]))
	{
		return true;
	}
	else if (collider.touch((int)positionData[6], (int)positionData[7]))
	{
		return true;
	}
	else
	{
		return false;
	}
}