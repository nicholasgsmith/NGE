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

	unrotatedCorners[0] = 0;
	unrotatedCorners[1] = 0;
	unrotatedCorners[2] = 0;
	unrotatedCorners[3] = 0;

	for (int i = 0; i != 8; i++)
	{
		cornerCoordinates[i] = 0;
		sideEquations[i] = 0.0;
		positionData[i] = 0.0;
		positionData[i + 8] = 0.0;
	}
	positionData[16] = 0;

	subShapes.clear();
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

	//Adjusts the center co-ordinate accordingly based off which direction to move in
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

	//Mod by 360 to ensure value is always between 0-359
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

	//Mod by 360 to ensure value is always between 0-359
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
	//If the entity has moved, we need to calculate the new corner co-ordinates 
	//We only need two corners, as if we calculate opposite corners ,(x,y) and (p,q), then the other corners will be (x,q) and (p,y)
	//We ignore rotation at this stage
	if (changeInPosition)
	{
		unrotatedCorners[0] = centerX - (width / 2);
		unrotatedCorners[1] = centerY - (height / 2);
		unrotatedCorners[2] = centerX + (width / 2);
		unrotatedCorners[3] = centerY + (height / 2);
	}

	//If the entity has been moved or rotated, then the co-ordinates of the corners will have changed and must be recalculated
	if (changeInPosition || changeInRotation)
	{
		//If the rotation is 0, then the rotated corner co-ordinates can be directly determined from the unrotated corner co-ordinates
		if (rotation == 0)
		{
			cornerCoordinates[0] = unrotatedCorners[0];
			cornerCoordinates[1] = unrotatedCorners[1];
			cornerCoordinates[2] = unrotatedCorners[0];
			cornerCoordinates[3] = unrotatedCorners[3];
			cornerCoordinates[4] = unrotatedCorners[2];
			cornerCoordinates[5] = unrotatedCorners[3];
			cornerCoordinates[6] = unrotatedCorners[2];
			cornerCoordinates[7] = unrotatedCorners[1];
		}
		else
		{
			//We work out what sin and cos out for our entities rotation
			double cosValue = cos(RADIANS(rotation));
			double sinValue = sin(RADIANS(rotation));

			//For a co-ordinate (x,y), when rotated by d degrees around a point (p,q) its new value is (((x-p)*cos(d) - (y-q)*sin(d)) + p, ((x-p)*sin(d) - (y-q)*cose(d)) + q)
			cornerCoordinates[0] = (int)((unrotatedCorners[0] - centerX)*cosValue - ((unrotatedCorners[1] - centerY)*sinValue)) + centerX;
			cornerCoordinates[1] = (int)((unrotatedCorners[0] - centerX)*sinValue + ((unrotatedCorners[1] - centerY)*cosValue)) + centerY;
			cornerCoordinates[2] = (int)((unrotatedCorners[0] - centerX)*cosValue - ((unrotatedCorners[3] - centerY)*sinValue)) + centerX;
			cornerCoordinates[3] = (int)((unrotatedCorners[0] - centerX)*sinValue + ((unrotatedCorners[3] - centerY)*cosValue)) + centerY;
			cornerCoordinates[4] = (int)((unrotatedCorners[2] - centerX)*cosValue - ((unrotatedCorners[3] - centerY)*sinValue)) + centerX;
			cornerCoordinates[5] = (int)((unrotatedCorners[2] - centerX)*sinValue + ((unrotatedCorners[3] - centerY)*cosValue)) + centerY;
			cornerCoordinates[6] = (int)((unrotatedCorners[2] - centerX)*cosValue - ((unrotatedCorners[1] - centerY)*sinValue)) + centerX;
			cornerCoordinates[7] = (int)((unrotatedCorners[2] - centerX)*sinValue + ((unrotatedCorners[1] - centerY)*cosValue)) + centerY;
		}

		//If the entity's rotation % 90 == 0 then some sides are fully vertical, meaning they have no gradient and cannot be represented by y = mx + c
		//In this case we do not change the side equations as some do not exist, you can check the rotation to see if the side equations exist
		if (rotation % 90 != 0)
		{
			//We work of the gradient between 2 corners (x,y) and (x',y') by (x-x')/(y-y')
			//Opposite sides have equal gradients, so we only need to calculate 1
			sideEquations[0] = ((float) cornerCoordinates[1] - cornerCoordinates[7]) / (cornerCoordinates[0] - cornerCoordinates[6]);
			sideEquations[4] = sideEquations[0];
			sideEquations[2] = ((float) cornerCoordinates[1] - cornerCoordinates[3]) / (cornerCoordinates[0] - cornerCoordinates[2]);
			sideEquations[6] = sideEquations[2];

			//We work out the y-intercept by rearraging y = mx + c to c = y - mx
			sideEquations[1] = cornerCoordinates[1] - (sideEquations[0] * cornerCoordinates[0]);
			sideEquations[3] = cornerCoordinates[1] - (sideEquations[2] * cornerCoordinates[0]);
			sideEquations[5] = cornerCoordinates[5] - (sideEquations[4] * cornerCoordinates[4]);
			sideEquations[7] = cornerCoordinates[5] - (sideEquations[6] * cornerCoordinates[4]);
		}
	}

	//Since we have recaluted the position data of the entity, we can set the position changes to be false so that we dont need to calculate it again unless the entity moves
	changeInRotation = false;
	changeInPosition = false;
}

float* NGE_Entity::getPositionData()
{
	//Ensure entity data is up-to-date
	calculatePositionData();

	int i = 0;

	//Add the corner co-ordinates
	for (i = 0; i != 8; i++)
	{
		positionData[i] = (float)cornerCoordinates[i];
	}

	//Add the side equations
	for (i = 8; i != 16; i++)
	{
		positionData[i] = sideEquations[i - 8];
	}

	//Add the rotation
	positionData[16] = (float)rotation;

	return positionData;
}

bool NGE_Entity::touch(int x, int y)
{
	//Ensure entity data is up-to-date
	calculatePositionData();

	switch (rotation)
	{
		//If the rotation % 90 == 0 then we can simply check if the point falls within the simple linear boundaries given by its co-ordinates
		//The rotation of the entity determines when the point needs to be greater or less than the corners of the entity
		case 0:
			if (((x > cornerCoordinates[0]) && (x < cornerCoordinates[4]) && (y > cornerCoordinates[1]) && (y < cornerCoordinates[5])))
			{
				return true;
			}
			break;
		case 180:
			if (((x > cornerCoordinates[4]) && (x < cornerCoordinates[0]) && (y > cornerCoordinates[5]) && (y < cornerCoordinates[1])))
			{
				return true;
			}
			break;
		case 90:
			if (((x > cornerCoordinates[4]) && (x < cornerCoordinates[0]) && (y > cornerCoordinates[1]) && (y < cornerCoordinates[5])))
			{
				return 1;
			}
			break;
		case 270:
			if (((x > cornerCoordinates[0]) && (x < cornerCoordinates[4]) && (y > cornerCoordinates[5]) && (y < cornerCoordinates[1])))
			{
				return true;
			}
			break;
		default:
			//If the rotation % 90 != 0 then we need to check whether the point falls within the equations of the lines representing the sides of the entity
			//The rotation of the entity determines when mx + c must be greater than or less then y, for the point (x,y)
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
	//Obtain the poisition data of the other entity
	float* colliderData = collider.getPositionData();
	
	//Ensure entity data is up-to-date
	calculatePositionData();

	//We perform touch 8 times to check if the two are touching
	//4 times we check if the corner co-ordinates of the second entity are on the first, and 4 times vice-versa
	//This is all we do, as since they are both rectangles, they are touching if at least 1 of their corners is inside or touching the other
	//The exception of the above is if 1 is streched through the other, but we do not test for this as it adds too much overhead and is too niche a senario
	//If we ever hit a corner, we dont care about the other corners and just return true, as we dont care how much they are touching by
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