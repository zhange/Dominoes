//includes
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>

//added includes
#include "includes/View.h"

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

using namespace std;

//global variables
string MODE;

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
	//glutInitDisplayMode(GLUT_SINGLE | GLUT_DOUBLE);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Dominos Pizza");
	glutDisplayFunc(drawScene);
	Initialize();
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);
	glutMouseFunc(mouseControl);

	glutMainLoop();

	return 0;
}

//display function
void drawScene()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);;
	glutSwapBuffers();
	// Added function to control viewport
	vMain();

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

//window resize function
void resize(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(0.0, 100.0, 0.0, 100.0, -1.0, 1.0);
	glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 250.0);
	glMatrixMode(GL_MODELVIEW);
}

//keyboard function
void keyInput(unsigned char key, int x, int y)
{
	switch(key) 
	{
		case 27:
			exit(0);
			break;
		default:
			break;
	}
}

//mouse function
void mouseControl(int button, int state, int x, int y)
{
	// Store the clicked point in the currentPoint variable when left button is pressed.
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
	}

	// Store the currentPoint in the points vector when left button is released.
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
	}

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		exit(0);
	}

	glutPostRedisplay();
}


