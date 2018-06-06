#ifndef NGE_ENTITY_H
#define NGE_ENTITY_H

using namespace std;
#include "NGE_Master.h"
#include "NGE_Texture.h"
#include "NGE_Render.h"

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

	GLuint texture;
	int canvasAlpha, canvasBlue, canvasGreen, canvasRed;
	int borderRed, borderGreen, borderBlue, borderAlpha, borderWidth;

public:

	//Creates a new, empty instance
	NGE_Entity();

	//Assigns the canvas of the entity
	//This is rendered whenever the entity is rendered
	//If the entity also has a texture assigned to it, the canvas will be rendered below the texture
	int setCanvas(int red, int green, int blue, int alpha);

	//Assigns a texture to the entity that will be rendered when you render the entity
	int assignTexture(NGE_Texture texture, bool setToTextureSize);

	//Sets a border around the entity of the given width and color
	int setBorder(int borderWidth, int red, int green, int blue, int alpha);

	//Renders the entity onto the openGL model matrix, allowing you to render it to a window
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
};

#endif