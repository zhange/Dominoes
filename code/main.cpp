//standard includes
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <vector>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

using namespace std;

//object includes
#include "include/button.h"
#include "include/domino.h"
#include "include/point.h"

//global variables
string MODE = "RUN";
int HEIGHT = 500;
int WIDTH = 900;
int ptslines = 0;
vector<button> demButtons;
vector<domino> dominos;
vector<Point> points;

//helper includes
#include "include/drawMode.h"
#include "include/runMode.h"
#include "include/view.h"
#include "include/utils.h"

//function prototypes
void Initialize();
void drawScene();
void resize(int w, int h);
void keyInput(unsigned char key, int x, int y);
void mouseControl(int button, int state, int x, int y);

// main function
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Dominoes");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);
	glutMouseFunc(mouseControl);
	//glutTimerFunc(5, animate, 1);
	
	Initialize();
	
	glutMainLoop();

	return 0;
}

// init func
void Initialize()
{
	glClearColor(1.0,1.0,1.0,.5);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0,1.0,-1.0,1.0,-1.0,1.0);
	// Lighting Set Up
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	// Set lighting intensity and color
	GLfloat qaAmbientLigh[] = {0.2,0.2,0.2,1.0};
	GLfloat qaDiffuseLight[] = {.8,.8,.8,1.0};
	GLfloat qaSpecularLight[] = {1.0,1.0,1.0,1.0};
	glLightfv(GL_LIGHT0, GL_AMBIENT,qaAmbientLigh);
	glLightfv(GL_LIGHT0, GL_DIFFUSE,qaDiffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR,qaSpecularLight);
	// set the light position
	GLfloat qaLightPosition[] = {.5,.5,0.0,1.0};
	glLightfv(GL_LIGHT0, GL_POSITION, qaLightPosition);
}

//display function
void drawScene()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	
	if(MODE == "DRAW")
	{
		//turn to 2D mode
		//mode2D();
		
		//draw mode display function
		glColor3f(0.0, 0.0, 0.0);
		if(ptslines==0)
		{
			drawPoints();
		}
		else
		{
			drawLines();
		}
		glutSwapBuffers();
	}
	else if(MODE == "RUN")
	{
		//turn to 3D mode
		mode3D();
		
		//run mode display function
		
	}
		
	//turn to 2D mode
	mode2D();
	
	//menu buttons
	demButtons.clear();
	demButtons.push_back(button(1,1,"Draw Mode"));
	demButtons.push_back(button(1,2,"Run Mode"));
	demButtons.push_back(button(2,1,"Load Setup"));
	demButtons.push_back(button(2,2,"Save Setup"));
	
	if(MODE == "DRAW")
	{
		//draw buttons
	}
	else if(MODE == "RUN")
	{
		demButtons.push_back(button(3,1,"Play Sequence"));
		demButtons.push_back(button(3,2,"Reset Dominoes"));
	}
	
	drawMenu();
	
	//glDepthMask(GL_TRUE);

	glutSwapBuffers();
}

//window resize function
void resize(int w, int h)
{
	WIDTH = w;
	HEIGHT = h;
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 250.0);
	glMatrixMode(GL_MODELVIEW);
}

//keyboard function
void keyInput(unsigned char key, int x, int y)
{
	if(MODE == "DRAW")
	{
		//draw mode keyboard function
	}
	else if(MODE == "RUN")
	{
		//run mode keyboard function
	}
	
	glutPostRedisplay();
}

//mouse function
void mouseControl(int button, int state, int x, int y)
{
	if(x < WIDTH - 400)
	{
		if(MODE == "DRAW")
		{
			y = HEIGHT - y; // Correct from mouse to OpenGL co-ordinates.
			if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    		{
    			cout << x << endl;
    			ptslines = 0;
    			points.clear();
    			points.push_back(Point(x,y));
				glutMotionFunc(mousemove);
			}
			else
			{
				points = removedups(points);
				points = choosepts(points, 10);
				points = calcforward(points);
				dominos = pointtodomino(points);
				ptslines = 1;
			}
		}
		else if(MODE == "RUN")
		{
			//run mode mouse function
		}
	}
	else if(state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)//menu button handling
	{
		int left, right, top, bottom;
		for(int i = 0; i < demButtons.size(); i++)
		{
			left = WIDTH - 385 + 190*(demButtons[i].getCol() - 1);
			right = left + 180;
			top = HEIGHT - 15 - 40*(demButtons[i].getRow() - 1);
			bottom = top - 30;	

			if(x < right && x > left && HEIGHT - y < top && HEIGHT - y > bottom)
			{
				if(demButtons[i].getName() == "Draw Mode")
				{
					MODE = "DRAW";
				}
				else if(demButtons[i].getName() == "Run Mode")
				{
					MODE = "RUN";
				}
				else if(demButtons[i].getName() == "Load Setup")
				{
					readFile();
				}
				else if(demButtons[i].getName() == "Save Setup")
				{
					saveFile();
				}
				else if(demButtons[i].getName() == "Play Sequence")
				{
					
				}
				else if(demButtons[i].getName() == "Reset Dominoes")
				{
					
				}
			}
		}
	}

	glutPostRedisplay();
}


