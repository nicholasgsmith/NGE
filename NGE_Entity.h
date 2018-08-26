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
enum class PerformMovement { none, to_collision, full };

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

	double rightVelocity, downVelocity, excessDown, excessRight, rightAcceleration, downAcceleration;

public:

	vector<NGE_Entity*> subShapes;

	//Creates a new, empty instance
	NGE_Entity();

	//Adds a new sub-shape to the shape
	//New shape is added to the end of the sub-shape vector
	int pushSubShape();

	//Deletes a sub-shape from the end of the sub-shape vector
	int popSubShape();

	//Deletes a given sub-shape
	//Bear in mind this will adjust the position of other sub-shapes within the vector
	int deleteSubShape(unsigned int index);

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
	bool staticCollision(NGE_Entity& collider, bool includeHostSubShapes, bool includeColliderSubShapes);

	//Sets the velocity of the entity in the x-axis (right is positive)
	int setVelocityX(double velocity);

	//Gets the velocity of the entity in the x-axis (right is positive)
	double getVelocityX();

	//Sets the velocity of the entity in the y-axis (down is positive)
	int setVelocityY(double velocity);

	//Gets the velocity of the entity in the y-axis (down is positive)
	double getVelocityY();

	//Sets the acceleration of the entity in the x-axis (right is positive)
	int setAccelerationX(float acceleration);

	//Gets the acceleration of the entity in the x-axis (right is positive)
	double getAccelerationX();

	//Sets the acceleration of the entity in the y-axis (down is positive)
	int setAccelerationY(float acceleration);

	//Gets the acceleration of the entity in the y-axis (down is positive)
	double getAccelerationY();

	//Calculates the X and Y velocities based off a resultant velocity in a provided direction (up is 0 degrees)
	int setVelocity(int bearing, double velocity);

	//Calculates the X and Y accelerations based off a resultant acceleration in a provided direction (up is 0 degrees)
	int setAcceleration(int bearing, double acceleration);

	//Given the amount of passed time (in milliseconds) calculates and updates the entities position and velocity given its velocity and acceleration
	int calculateMovement(int timePassed);

	//Given a linear line and an amount of time that has passed, calculates whether or not the entity will collide with the line
	//timeLeft is set to however much of timePassed has not passed yet after a collision occurs. Is equal time passed if they were already colliding, and 0 if no collision happens, or only right at the end of the time
	//Note that timeLeft is the time left after a collision occurs, regardless of wheteher you actually moved the entity or rebounded it with the movement parameter.
	//movement sets how the entity will be adjusted in the event of a collsion. When set of none, this function does not change the entity, it just predicts if a collision will happened. 
	//If movement is set to to_collison, the entity will be moved frward in time and updated until the collsion, and then stopped. full moved the entity forward to the line, and then rebounds it off, recalculting its movement angle and moving it forward with any time left. Does not effect acceleration.
	//Two co-ordinates of the line are provided, which are used to calculate the equation of the line
	//If a collision occurs in in the provided timeframe, the velocity of the entity is multiplied by velocityMultipler
	//Returns true if a collision happens in the given timeframe
	bool calculateLineCollision(int timePassed, int& timeLeft, PerformMovement movement, bool changeAccelerationAngle, int xCoordinateOne, int yCoordinateOne, int xCoordinateTwo, int yCoordinateTwo, double velocityMultiplier);

};

#endif