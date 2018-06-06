#include "NGE_Entity.h"
using namespace std;

NGE_Entity::NGE_Entity()
{
	textureID = 0;
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