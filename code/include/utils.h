#include <iostream>

using namespace std;

#include "button.h"
#include "drawMode.h"
#include "runMode.h"

///global variables
string MODE = "DRAW";
int HEIGHT = 500;
int WIDTH = 900;
vector<Button> demButtons;

//writes bitmap string to screen
void writeString(int x, int y, void *font, const char *str)
{
	const char *cs;
	glRasterPos2i(x, y);
	for(cs = str; *cs != '\0'; cs++)
	{
		glutBitmapCharacter(font, *cs);
	}
	glutPostRedisplay();
}

//button drawing function
void drawButton(string name, int row, int column)
{
	int left, right, top, bottom;

	left = WIDTH - 385 + 190*(column - 1);
	right = left + 180;
	top = HEIGHT - 15 - 40*(row - 1);
	bottom = top - 30;	

	glColor3f(37.0/255.0, 213.0/255.0, 0.0/255.0);
	glBegin(GL_QUADS);
	glVertex2f(left, top);
	glVertex2f(left, bottom);
	glVertex2f(right, bottom);
	glVertex2f(right, top);
	glEnd();

	glColor3f(255.0/255.0, 255.0/255.0, 255.0/255.0);
	writeString(left + 5 + (180 - 10*name.length())/2, bottom + 8, GLUT_BITMAP_HELVETICA_18, name.c_str());
}

//menu drawing function
void drawMenu()
{
	glColor3f(0.0/255.0, 160.0/255.0, 138.0/255.0);
	glBegin(GL_QUADS);
	glVertex2f(WIDTH - 400, 0);
	glVertex2f(WIDTH, 0);
	glVertex2f(WIDTH, HEIGHT);
	glVertex2f(WIDTH - 400, HEIGHT);
	glEnd();

	glColor3f(16.0/255.0, 73.0/255.0, 169.0/255.0);
	glBegin(GL_QUADS);
	glVertex2f(WIDTH - 390, 10);
	glVertex2f(WIDTH - 10, 10);
	glVertex2f(WIDTH - 10, HEIGHT - 10);
	glVertex2f(WIDTH - 390, HEIGHT - 10);
	glEnd();

	for(int i = 0; i < demButtons.size(); i++)
	{
		drawButton(demButtons[i].getName(), demButtons[i].getRow(), demButtons[i].getCol());
	}
}
