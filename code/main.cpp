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
vector<domino> dominoes;
vector<Point> points;
domino *lead;
int leadInd;
bool touchFlag = false;
float testThingX = 0; 
float testThingY = 0;
bool up = true;
bool STARTED = false;

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
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Dominoes");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);
	glutMouseFunc(mouseControl);
	//glutTimerFunc(5, animate, 1);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	Initialize();
	
	cout << "d = draw" << endl << "r = run" << endl << "l = load" << endl << "s = save" << endl << "g = go" << endl << "c = clear" << endl;
	
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
	
	// new stuff //
	// Material property vectors.
   float matSpec[] = { 0.0, 1.0, 1.0, 1.0 };
   float matShine[] = { 50.0 };
   float matAmbAndDif[] = {0.0, 0.1, 1.0, 1.0};

   // Light property vectors.
   float lightAmb[] = { 1.0, 1.0, 1.0, 1.0 };
   float lightDifAndSpec[] = { 1.0, 1.0, 1.0, 1.0 };
   float lightPos[] = { 250.0, 250.0, 250.0, 1.0 };
   float globAmb[] = { 0.2, 0.2, 0.2, 1.0 };

   // Material properties of the objects.
   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpec);
   glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matShine);
   glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matAmbAndDif);

   // Light0 properties.
   glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDifAndSpec);
   glLightfv(GL_LIGHT0, GL_SPECULAR, lightDifAndSpec);
   glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    
   // Poperties of the ambient light.
   glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb); // Global ambient light.

   glEnable(GL_LIGHTING); // Enable lighting calculations.
   glEnable(GL_LIGHT0); // Enable particular light source.
   glEnable(GL_DEPTH_TEST); // Enable depth testing.

   glEnable(GL_NORMALIZE); // Enable automatic normalization of normals.

   glClearColor(1.0, 1.0, 1.0, 0.0);
	
}

//display function
void drawScene()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	//glClear(GL_COLOR_BUFFER_BIT);
	
	glColor3f(255.0/255.0, 255.0/255.0, 255.0/255.0);
	glBegin(GL_QUADS);
		glVertex2f(WIDTH - 400, 0);
		glVertex2f(0, 0);
		glVertex2f(0, HEIGHT);
		glVertex2f(WIDTH - 400, HEIGHT);
	glEnd();
	
	glColor3f(1.0, 1.0, 1.0);
	
	if(MODE == "DRAW")
	{
		//turn to 2D mode
		mode2D();
		
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
		
		if(STARTED)
		{
			fullStep();
			colDet();
		}
		
		//run mode display function
		r_display(); 
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
	
	glDepthMask(GL_TRUE);
	

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
	if(key == 'd')
	{
		//draw
		MODE = "DRAW";
	}
	else if(key == 'r')
	{
		//run
		MODE = "RUN";
	}
	else if(key == 'l')
	{
		//load
		readFile();
	}
	else if(key == 's')
	{
		//save
		saveFile();
	}
	else if(key == 'g')
	{
		//go
		
	}
	else if(key == 'c')
	{
		//clear
		reset();		
	}
	else if(key == 'z')
	    testThingY++;
	else if(key == 'x')
	    testThingY--;
	else if(key == 'v')
	    testThingX++;
	else if(key == 'b')
	    testThingX--;
	    
	glutPostRedisplay();
}


//mouse function
void mouseControl(int button, int state, int x, int y)
{

	if(x < WIDTH - 400 && x >= 0 && y <= HEIGHT && y >= 0)
	{
		if(MODE == "DRAW")
		{
			y = HEIGHT - y; // Correct from mouse to OpenGL co-ordinates.
			if ((button == GLUT_LEFT_BUTTON || button == GLUT_RIGHT_BUTTON )&& state == GLUT_DOWN)
    		{
    			up = false;
    			ptslines = 0;
    			points.clear();
    			points.push_back( Point(x,y) );
				glutMotionFunc(mousemove);
			}
			else
			{
				up = true;
				if(points.size() > 0)
				{
					points = removedups(points);
					points = choosepts(points, 10);
					points = calcforward(points);
					dominoes = pointtodomino(points);
					ptslines = 1;
				}
			}

			//draw mode mouse function

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
					reset();
					MODE = "DRAW";
				}
				else if(demButtons[i].getName() == "Run Mode")
				{
					MODE = "RUN";
				}
				else if(demButtons[i].getName() == "Load Setup")
				{
					readFile();
					drawLines();
				}
				else if(demButtons[i].getName() == "Save Setup")
				{
					saveFile();
				}
				else if(demButtons[i].getName() == "Play Sequence")
				{
					start();
				}
				else if(demButtons[i].getName() == "Reset Dominoes")
				{
					reset();
				}
			}
		}
	}
	

	glutPostRedisplay();
}




