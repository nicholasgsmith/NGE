#include "NGE_Render.h"
using namespace std;

int NGE_RenderQuad(int centerX, int centerY, int width, int height, int rotation, int red, int green, int blue, int alpha)
{
	glDisable(GL_TEXTURE_2D);

	glTranslatef(centerX, centerY, 0);
	glRotatef(rotation, 0, 0, 1);

	glColor4f(1.0f*(red / 1.0 / 255), 1.0f*(green / 1.0 / 255), 1.0f*(blue / 1.0 / 255), 1.0f*(alpha / 1.0 / 255));

	glBegin(GL_QUADS);
	glVertex2f(-(width / 2), -(height / 2));
	glVertex2f(-(width / 2), (height / 2));
	glVertex2f((width / 2), (height / 2));
	glVertex2f((width / 2), -(height / 2));
	glEnd();

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	glRotatef(-rotation, 0, 0, 1);
	glTranslatef(-centerX, -centerY, 0);

	glEnable(GL_TEXTURE_2D);
	return 0;
}

int NGE_RenderTexture(GLuint texture, int centerX, int centerY, int width, int height, int rotation, bool flipTexture)
{
	if (texture != NULL)
	{
		glTranslatef(centerX, centerY, 0);
		glRotatef(rotation, 0, 0, 1);

		glBindTexture(GL_TEXTURE_2D, texture);

		if (flipTexture)
		{
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

		glRotatef(-rotation, 0, 0, 1);
		glTranslatef(-centerX, -centerY, 0);
	}
	else
	{
		return -1;
	}
}