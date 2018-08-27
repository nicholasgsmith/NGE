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

int NGE_Entity::pushSubShape()
{
	//Create and store new entity
	NGE_Entity* entity = new NGE_Entity;
	subShapes.push_back(entity);
	return 0;
}

int NGE_Entity::popSubShape()
{
	//Get last subshape
	int lastSubShape = subShapes.size() - 1;

	//Deallocate its memory and remove it
	delete subShapes[lastSubShape];
	subShapes.pop_back();
	return 0;
}

int NGE_Entity::deleteSubShape(unsigned int index)
{
	//Confirm index exists
	if (index >= subShapes.size() || index < 0)
	{
		return -1;
	}

	//Deallocate entity's memory and remove it
	delete subShapes[index];
	subShapes.erase(subShapes.begin()+index+1);
	return 0;
}

int NGE_Entity::setCanvas(int red, int green, int blue, int alpha, bool adjustSubShapes)
{
	canvasRed = red;
	canvasGreen = green;
	canvasBlue = blue;
	canvasAlpha = alpha;

	if (adjustSubShapes)
	{
		for (int i = 0; i != subShapes.size(); i++)
		{
			subShapes[i]->setCanvas(red, green, blue, alpha, adjustSubShapes);
		}
	}

	return 0;
}

int NGE_Entity::assignTexture(NGE_Texture texture, bool setToTextureSize, bool adjustSubShapes)
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

	if (adjustSubShapes)
	{
		for (int i = 0; i != subShapes.size(); i++)
		{
			subShapes[i]->assignTexture(texture, setToTextureSize, adjustSubShapes);
		}
	}

	return 0;
}

int NGE_Entity::setBorder(int borderWidth, int red, int green, int blue, int alpha, bool adjustSubShapes)
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

	if (adjustSubShapes)
	{
		for (int i = 0; i != subShapes.size(); i++)
		{
			subShapes[i]->setBorder(borderWidth, red, green, blue, alpha, adjustSubShapes);
		}
	}

	return 0;
}

int NGE_Entity::render(bool applyToSubShapes)
{
	//If a canvas, a colored background for the entity, is set render it first so it is behind the texture
	if (canvasAlpha != 0)
	{
		NGE_AdjustAxis(centerX, centerY, rotation);
		NGE_RenderQuad(width, height, canvasRed, canvasGreen, canvasBlue, canvasAlpha);
		NGE_AdjustAxis(-centerX, -centerY, -rotation);
	}

	//Render the texture
	//Only revser the axis change before exiting the method so that subshapes are also effected by it
	NGE_AdjustAxis(centerX, centerY, rotation);
	int result = NGE_RenderTexture(texture, width, height, flipped);
	if (result == 0)
	{
		NGE_AdjustAxis(-centerX, -centerY, -rotation);
		return -1;
	}

	//If a border was set render it as 4 rectangles around the entity
	if (borderWidth != 0)
	{
		NGE_AdjustAxis(centerX, centerY - (height / 2) - ((borderWidth + 1) / 2), rotation);
		NGE_RenderQuad(width + (2 * borderWidth), borderWidth, borderRed, borderGreen, borderBlue, borderAlpha);
		NGE_AdjustAxis(-centerX, -(centerY - (height / 2) - ((borderWidth + 1) / 2)), -rotation);

		NGE_AdjustAxis(centerX, centerY + (height / 2) + ((borderWidth + 1) / 2), rotation);
		NGE_RenderQuad(width + (2 * borderWidth), borderWidth, borderRed, borderGreen, borderBlue, borderAlpha);
		NGE_AdjustAxis(-centerX, -(centerY + (height / 2) + ((borderWidth + 1) / 2)), -rotation);

		NGE_AdjustAxis(centerX - (width / 2) - ((borderWidth + 1) / 2), centerY, rotation);
		NGE_RenderQuad(borderWidth, height + (2 * borderWidth), borderRed, borderGreen, borderBlue, borderAlpha);
		NGE_AdjustAxis(centerX - (width / 2) - ((borderWidth + 1) / 2), -centerY, -rotation);

		NGE_AdjustAxis(centerX + (width / 2) + ((borderWidth + 1) / 2), centerY, rotation);
		NGE_RenderQuad(borderWidth, height + (2 * borderWidth), borderRed, borderGreen, borderBlue, borderAlpha);
		NGE_AdjustAxis(centerX + (width / 2) + ((borderWidth + 1) / 2), -centerY, -rotation);
	}

	if (applyToSubShapes)
	{
		for (int i = 0; i != subShapes.size(); i++)
		{
			subShapes[i]->render(applyToSubShapes);
		}
	}

	//Reverse axis adjustment
	NGE_AdjustAxis(-centerX, -centerY, -rotation);

	return 0;
}

int NGE_Entity::setWidth(int width, bool adjustSubShapes)
{
	width = width;
	changeInPosition = true;

	if (adjustSubShapes)
	{
		for (int i = 0; i != subShapes.size(); i++)
		{
			subShapes[i]->setWidth(width, adjustSubShapes);
		}
	}

	return 0;
}

int NGE_Entity::getWidth()
{
	return width;
}

int NGE_Entity::setHeight(int height, bool adjustSubShapes)
{
	height = height;
	changeInPosition = true;

	if (adjustSubShapes)
	{
		for (int i = 0; i != subShapes.size(); i++)
		{
			subShapes[i]->setHeight(height, adjustSubShapes);
		}
	}

	return 0;
}

int NGE_Entity::getHeight()
{
	return height;
}

int NGE_Entity::setSides(int width, int height, bool adjustSubShapes)
{
	setHeight(height, adjustSubShapes);
	setWidth(width, adjustSubShapes);

	if (adjustSubShapes)
	{
		for (int i = 0; i != subShapes.size(); i++)
		{
			subShapes[i]->setSides(width, height, adjustSubShapes);
		}
	}

	return 0;
}

int NGE_Entity::adjustWidth(int amount, bool adjustSubShapes)
{
	changeInPosition = true;
	width = amount;

	if (adjustSubShapes)
	{
		for (int i = 0; i != subShapes.size(); i++)
		{
			subShapes[i]->adjustWidth(amount, adjustSubShapes);
		}
	}

	return 0;
}

int NGE_Entity::adjustHeight(int amount, bool adjustSubShapes)
{
	changeInPosition = true;
	height = amount;

	if (adjustSubShapes)
	{
		for (int i = 0; i != subShapes.size(); i++)
		{
			subShapes[i]->adjustHeight(amount, adjustSubShapes);
		}
	}

	return 0;
}

int NGE_Entity::setCenterX(int centerX, bool adjustSubShapes)
{
	changeInPosition = true;
	centerX = centerX;

	if (adjustSubShapes)
	{
		for (int i = 0; i != subShapes.size(); i++)
		{
			subShapes[i]->setCenterX(centerX, adjustSubShapes);
		}
	}

	return 0;
}

int NGE_Entity::getCenterX()
{
	return centerX;
}

int NGE_Entity::setCenterY(int centerY, bool adjustSubShapes)
{
	changeInPosition = true;
	centerY = centerY;

	if (adjustSubShapes)
	{
		for (int i = 0; i != subShapes.size(); i++)
		{
			subShapes[i]->setCenterY(centerY, adjustSubShapes);
		}
	}

	return 0;
}

int NGE_Entity::getCenterY()
{
	return centerY;
}

int NGE_Entity::setCenter(int centerX, int centerY, bool adjustSubShapes)
{
	setCenterX(centerX, adjustSubShapes);
	setCenterY(centerY, adjustSubShapes);

	if (adjustSubShapes)
	{
		for (int i = 0; i != subShapes.size(); i++)
		{
			subShapes[i]->setCenter(centerX, centerY, adjustSubShapes);
		}
	}

	return 0;
}

int NGE_Entity::translate(Direction direction, int amount, bool adjustSubShapes)
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

	if (adjustSubShapes)
	{
		for (int i = 0; i != subShapes.size(); i++)
		{
			subShapes[i]->translate(direction, amount, adjustSubShapes);
		}
	}

	return 0;
}

int NGE_Entity::setRotation(int rotation, bool adjustSubShapes)
{
	changeInRotation = true;
	rotation = rotation;

	//Mod by 360 to ensure value is always between 0-359
	rotation %= 360;

	if (adjustSubShapes)
	{
		for (int i = 0; i != subShapes.size(); i++)
		{
			subShapes[i]->setRotation(rotation, adjustSubShapes);
		}
	}

	return 0;
}

int NGE_Entity::getRotation()
{
	return rotation;
}

int NGE_Entity::rotate(int amount, bool adjustSubShapes)
{
	changeInRotation = true;
	rotation += amount;

	//Mod by 360 to ensure value is always between 0-359
	rotation %= 360;

	if (adjustSubShapes)
	{
		for (int i = 0; i != subShapes.size(); i++)
		{
			subShapes[i]->rotate(amount, adjustSubShapes);
		}
	}

	return 0;
}

int NGE_Entity::setPosition(int centerX, int centerY, int width, int height, int rotation, bool adjustSubShapes)
{
	setCenterX(centerX, adjustSubShapes);
	setCenterY(centerY, adjustSubShapes);
	setRotation(rotation, adjustSubShapes);
	setHeight(height, adjustSubShapes);
	setWidth(width, adjustSubShapes);

	if (adjustSubShapes)
	{
		for (int i = 0; i != subShapes.size(); i++)
		{
			subShapes[i]->setPosition(centerX, centerY, width, height, rotation, adjustSubShapes);
		}
	}

	return 0;
}

int NGE_Entity::setFlip(bool flipped, bool adjustSubShapes)
{
	flipped = flipped;

	if (adjustSubShapes)
	{
		for (int i = 0; i != subShapes.size(); i++)
		{
			subShapes[i]->setFlip(flipped, adjustSubShapes);
		}
	}

	return 0;
}

bool NGE_Entity::getFlip()
{
	return flipped;
}

int NGE_Entity::swapFlip(bool adjustSubShapes)
{
	if (flipped)
	{
		flipped = false;
	}
	else
	{
		flipped = true;
	}

	if (adjustSubShapes)
	{
		for (int i = 0; i != subShapes.size(); i++)
		{
			subShapes[i]->swapFlip(adjustSubShapes);
		}
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

bool NGE_Entity::touch(int x, int y, bool includeSubShapes)
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

	for (int i = 0; i != subShapes.size(); i++)
	{
		if (includeSubShapes)
		{
			if (subShapes[i]->touch(x, y, includeSubShapes))
			{
				return true;
			}
		}
	}

	return false;
}

bool NGE_Entity::staticCollision(NGE_Entity& collider, bool includeHostSubShapes, bool includeColliderSubShapes)
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
	if (touch((int)colliderData[0], (int)colliderData[1], includeHostSubShapes))
	{
		return true;
	}
	else if (touch((int)colliderData[2], (int)colliderData[3], includeHostSubShapes))
	{
		return true;
	}
	else if (touch((int)colliderData[4], (int)colliderData[5], includeHostSubShapes))
	{
		return true;
	}
	else if (touch((int)colliderData[6], (int)colliderData[7], includeHostSubShapes))
	{
		return true;
	}
	else if (collider.touch((int)positionData[0], (int)positionData[1], includeHostSubShapes))
	{
		return true;
	}
	else if (collider.touch((int)positionData[2], (int)positionData[3], includeHostSubShapes))
	{
		return true;
	}
	else if (collider.touch((int)positionData[4], (int)positionData[5], includeHostSubShapes))
	{
		return true;
	}
	else if (collider.touch((int)positionData[6], (int)positionData[7], includeHostSubShapes))
	{
		return true;
	}
	else
	{
		if (includeColliderSubShapes)
		{
			for (int i = 0; i != collider.subShapes.size(); i++)
			{
				if (this->staticCollision(*(collider.subShapes[i]), includeHostSubShapes, includeColliderSubShapes))
				{
					return true;
				}
			}
		}

		return false;
	}
}

int NGE_Entity::setVelocityX(double velocity, bool adjustSubShapes)
{
	rightVelocity = velocity;

	if (adjustSubShapes)
	{
		for (int i = 0; i != subShapes.size(); i++)
		{
			subShapes[i]->setVelocityX(velocity, adjustSubShapes);
		}
	}

	return 0;
}

double NGE_Entity::getVelocityX()
{
	return rightVelocity;
}

int NGE_Entity::setVelocityY(double velocity, bool adjustSubShapes)
{
	downVelocity = velocity;

	if (adjustSubShapes)
	{
		for (int i = 0; i != subShapes.size(); i++)
		{
			subShapes[i]->setVelocityY(velocity, adjustSubShapes);
		}
	}

	return 0;
}

double NGE_Entity::getVelocityY()
{
	return downVelocity;
}

int NGE_Entity::setAccelerationX(double acceleration, bool adjustSubShapes)
{
	rightAcceleration = acceleration;

	if (adjustSubShapes)
	{
		for (int i = 0; i != subShapes.size(); i++)
		{
			subShapes[i]->setAccelerationX(acceleration, adjustSubShapes);
		}
	}

	return 0;
}

double NGE_Entity::getAccelerationX()
{
	return rightAcceleration;
}

int NGE_Entity::setAccelerationY(double acceleration, bool adjustSubShapes)
{
	downAcceleration = acceleration;

	if (adjustSubShapes)
	{
		for (int i = 0; i != subShapes.size(); i++)
		{
			subShapes[i]->setAccelerationY(acceleration, adjustSubShapes);
		}
	}

	return 0;
}

double NGE_Entity::getAccelerationY()
{
	return downAcceleration;
}

int NGE_Entity::setVelocity(int bearing, double velocity, bool adjustSubShapes)
{
	rightVelocity = NGE_CalcualteRightValue(bearing, velocity);
	downVelocity = NGE_CalcualteDownValue(bearing, velocity);

	if (adjustSubShapes)
	{
		for (int i = 0; i != subShapes.size(); i++)
		{
			subShapes[i]->setVelocity(bearing, velocity, adjustSubShapes);
		}
	}

	return 0;
}

int NGE_Entity::setAcceleration(int bearing, double acceleration, bool adjustSubShapes)
{
	rightAcceleration = NGE_CalcualteRightValue(bearing, acceleration);
	downAcceleration = NGE_CalcualteDownValue(bearing, acceleration);

	if (adjustSubShapes)
	{
		for (int i = 0; i != subShapes.size(); i++)
		{
			subShapes[i]->setAcceleration(bearing, acceleration, adjustSubShapes);
		}
	}

	return 0;
}

int NGE_Entity::calculateMovement(int timePassed, bool moveSubShapes)
{
	changeInPosition = true;

	float timePassedSeconds = timePassed / 1000.0;
	float amountToMove = (timePassedSeconds*rightVelocity) + (pow(timePassedSeconds, 2)*0.5*rightAcceleration) + excessRight;
	rightVelocity += rightAcceleration*timePassedSeconds;
	excessRight = amountToMove - int(amountToMove);
	translate(Direction::right, int(amountToMove), false);

	timePassedSeconds = timePassed / 1000.0;
	amountToMove = (timePassedSeconds*downVelocity) + (pow(timePassedSeconds, 2)*0.5*downAcceleration) + excessDown;
	downVelocity += downAcceleration*timePassedSeconds;
	excessDown = amountToMove - int(amountToMove);
	translate(Direction::down, int(amountToMove), false);

	if (moveSubShapes)
	{
		for (int i = 0; i != subShapes.size(); i++)
		{
			subShapes[i]->calculateMovement(timePassed, moveSubShapes);
		}
	}

	return 0;
}