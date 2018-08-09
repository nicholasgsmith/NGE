#ifndef NGE_ENTITY_H
#define NGE_ENTITY_H

using namespace std;
#include "NGE_Master.h"
#include "NGE_Texture.h"
#include "NGE_Render.h"
#include "NGE_Maths.h"
#include <vector>

enum class Side { width, height };
enum class Direction { left, right, up, down };

class NGE_Entity
{
protected:
	int width, height, centerX, centerY, rotation, unrotatedCorners[4], cornerCoordinates[8];
	bool changeInPosition, changeInRotation, flipped;

	void calculatePositionData();
	float positionData[17];
	float sideEquations[8];

	GLuint texture;
	int canvasAlpha, canvasBlue, canvasGreen, canvasRed;
	int borderRed, borderGreen, borderBlue, borderAlpha, borderWidth;

	vector<NGE_Entity*> subShapes;

public:

	//Creates a new, empty instance
	NGE_Entity();

	//Assigns the canvas of the entity
	//This is rendered whenever the entity is rendered
	//If the entity also has a texture assigned to it, the canvas will be rendered below the texture
	int setCanvas(int red, int green, int blue, int alpha, bool adjustSubShapes);

	//Assigns a texture to the entity that will be rendered when you render the entity
	int assignTexture(NGE_Texture texture, bool setToTextureSize, bool adjustSubShapes);

	//Sets a border around the entity of the given width and color
	int setBorder(int borderWidth, int red, int green, int blue, int alpha, bool adjustSubShapes);

	//Renders the entity onto the openGL model matrix, allowing you to render it to a window
	int render(bool applyToSubShapes);

	//Sets the width
	int setWidth(int width, bool adjustSubShapes);

	//Returns the width
	int getWidth();

	//Sets the height
	int setHeight(int height, bool adjustSubShapes);

	//Returns the height
	int getHeight();

	//Returns the width and height
	int setSides(int width, int height, bool adjustSubShapes);

	//Increases the width by the given amount
	int adjustWidth(int amount, bool adjustSubShapes);

	//Increases the height by the given amount
	int adjustHeight(int amount, bool adjustSubShapes);

	//Sets the x value of the center co-ordinate
	int setCenterX(int centerX, bool adjustSubShapes);

	//Returns the x value of the center co-ordinate
	int getCenterX();

	//Sets the y value of the center co-ordinate
	int setCenterY(int centerY, bool adjustSubShapes);

	//Returns the y value of the center co-ordinate
	int getCenterY();

	//Sets the center co-ordinate 
	int setCenter(int centerX, int centerY, bool adjustSubShapes);

	//Moves the center co-ordinate in the given direction by the given amount
	int translate(Direction direction, int amount, bool adjustSubShapes);

	//Sets the rotation
	int setRotation(int rotation, bool adjustSubShapes);

	//Returns the rotation
	int getRotation();

	//Increases the rotation by the given amount
	int rotate(int amount, bool adjustSubShapes);

	//Sets the center co-ordinate, width, height and rotation 
	int setPosition(int centerX, int centerY, int width, int height, int rotation, bool adjustSubShapes);

	//Sets whether the entities texture should be flipped before being rendered
	//Is not reset each time the entity is rendered
	int setFlip(bool flipped, bool adjustSubShapes);

	//Returns whether the entities texture is set to be flipped before rendering
	bool getFlip();

	//Swaps whether the entities texture should be flipped before being rendered to whatever it wasn't
	int swapFlip(bool adjustSubShapes);

	//Returns information about the position of the entity for use in other functions
	//First 8 elements are the rotated co-ordinates of the corners, 2 adjacent elements are x and y co-ordnates respectivly
	//The next 8 elements are the gradients and y-intercepts of the equations that would run through 2 adjacent corners (the sides of the entity)
	//2 adjacent elemnets are the gradient and y-intercept respectivly
	//If the rotation of the entity % 90 == 0 then some gradients will not exist, and so these values may be anything and should not be used, see he final element for the rotation
	//The final element is the rotation of the entity
	float* getPositionData();

	//Returns true if the co-ordinate provided would fall inside the entity, false otherwise
	//This only returns true if the point is strictly within the entity, on the edge of the entity ,e.g. directly on one of its sides, is not accepted
	bool touch(int x, int y, bool includeSubShapes);

	//Returns true if the entity given is touching the host entity, false otherwise
	//This only returns true if the entites are strictly touching, on the edge of touching ,e.g. one entites corner is on the others side, is not accepted
	bool staticCollision(NGE_Entity& collider, bool includeSubShapes);
};

#endif