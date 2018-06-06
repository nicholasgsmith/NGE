#ifndef NGE_ENTITY_H
#define NGE_ENTITY_H

using namespace std;
#include "NGE_Master.h"
#include "NGE_Texture.h"

enum class Side { width, height };
enum class Direction { left, right, up, down };

class NGE_Entity
{
protected:
	int width, height, centerX, centerY, rotation, cornerCordinates[8], positions[4], rotated[8];
	bool changeInPosition, flipped;

	void calculatePositionData();
	float positionData[17];
	float sideEquations[8];

	GLuint textureID;
	int canvasAlpha, canvasBlue, canvasGreen, canvasRed;
	int borderRed, borderGreen, borderBlue, borderAlpha, borderWidth;

public:
	NGE_Entity();
	int setBorder(int borderWidth, int red, int green, int blue, int alpha);
	int assignTexture(NGE_Texture texture, bool setToTextureSize);
	int render();
	int setFlip(bool flipped);
	bool getFlip();
	int swapFlip();
	int setWidth(int width);
	int setHeight(int height);
	int getWidth();
	int getHeight();
	int setCenterX(int centerX);
	int getCenterX();
	int setCenterY(int centerY);
	int getCenterY();
	int setCenter(int centerX, int centerY);
	int setPosition(int centerX, int centerY, int width, int height, int rotation);
	int setSides(int width, int height);
	int setRotation(int rotation);
	int translate(Direction direction, int amount);
	int setSide(Side side, int amount);
	int getRotation();
	int touch(int x, int y);
	int changeRotation(int amount);
	int staticCollision(float* positionData);
	float* getPositionData();
	int setCanvas(int red, int green, int blue, int alpha);
};

#endif