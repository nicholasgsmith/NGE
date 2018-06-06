#include "NGE_Render.h"
using namespace std;

int NGE_RenderQuad(int centerX, int centerY, int width, int height, int rotation, int red, int green, int blue, int alpha)
{
	//Disable textures while we render the plain quad
	glDisable(GL_TEXTURE_2D);

	//Translate and rotate openGL model matrix 
	glTranslatef(centerX, centerY, 0);
	glRotatef(rotation, 0, 0, 1);

	//Set the color so it will be used when rendering GL_QUADS
	glColor4f(1.0f*(red / 1.0 / 255), 1.0f*(green / 1.0 / 255), 1.0f*(blue / 1.0 / 255), 1.0f*(alpha / 1.0 / 255));

	//Render the quad
	//Since we pre-set the color we just define the corner co-ordinates of the quad
	//Since we moved the openGL matrix the quad should be rendered around (0,0)
	glBegin(GL_QUADS);
	glVertex2f(-(width / 2), -(height / 2));
	glVertex2f(-(width / 2), (height / 2));
	glVertex2f((width / 2), (height / 2));
	glVertex2f((width / 2), -(height / 2));
	glEnd();

	//Clear the color
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	//Reverse the model matrix translation and rotation
	glRotatef(-rotation, 0, 0, 1);
	glTranslatef(-centerX, -centerY, 0);

	//Re-enable textures
	glEnable(GL_TEXTURE_2D);

	return 0;
}

int NGE_RenderTexture(GLuint texture, int centerX, int centerY, int width, int height, int rotation, bool flipTexture)
{
	//Confirm that a texture was sent
	if (texture != NULL)
	{
		//Translate and rotate openGL model matrix 
		glTranslatef(centerX, centerY, 0);
		glRotatef(rotation, 0, 0, 1);

		//Bind the texture so it will be rendered when using GL_QUADS
		glBindTexture(GL_TEXTURE_2D, texture);

		if (flipTexture)
		{
			//Render the texture
			//Since we moved the openGL matrix the quad should be rendered around (0,0)
			//Before we define a corner co-ordinate of the quad we set which corner of the texture that corresponds to
			//This allows us to flip the texture here
			glBegin(GL_QUADS);
			glTexCoord2f(1.f, 0.f);
			glVertex2f(-(width / 2), -(height / 2));
			glTexCoord2f(1.f, 1.f);
			glVertex2f(-(width / 2), (height / 2));
			glTexCoord2f(0.f, 1.f);
			glVertex2f((width / 2), (height / 2));
			glTexCoord2f(0.f, 0.f);
			glVertex2f((width / 2), -(height / 2));
			glEnd();
		}
		else
		{
			//Render the texture
			//Since we moved the openGL matrix the quad should be rendered around (0,0)
			//Before we define a corner co-ordinate of the quad we set which corner of the texture that corresponds to
			glBegin(GL_QUADS);
			glTexCoord2f(0.f, 0.f);
			glVertex2f(-(width / 2), -(height / 2));
			glTexCoord2f(0.f, 1.f);
			glVertex2f(-(width / 2), (height / 2));
			glTexCoord2f(1.f, 1.f);
			glVertex2f((width / 2), (height / 2));
			glTexCoord2f(1.f, 0.f);
			glVertex2f((width / 2), -(height / 2));
			glEnd();
		}

		//Reverse the model matrix translation and rotation
		glRotatef(-rotation, 0, 0, 1);
		glTranslatef(-centerX, -centerY, 0);
	}
	else
	{
		return -1;
	}
}