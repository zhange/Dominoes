//includes
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

using namespace std;

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
	//glutInitDisplayMode(GLUT_SINGLE | GLUT_DOUBLE);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Dominoes");
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
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	
	if(MODE == "DRAW")
	{
		glDisable(GL_LIGHTING);
		glDepthMask(GL_FALSE);
		glDisable(GL_DEPTH_TEST);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0,WIDTH,0,HEIGHT); //left,right,bottom,top

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
		
		//draw mode display function
	}
	else if(MODE == "RUN")
	{
		glEnable(GL_LIGHTING);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		//Set up projection matrix
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		//Using gluPerspective. It's pretty easy and looks nice.
		gluPerspective(0, 1, 0, 10);

		//Set up modelview matrix
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		//run mode display function
	}
		
	glDisable(GL_LIGHTING);
	glDepthMask(GL_FALSE);
	glDisable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,WIDTH,0,HEIGHT); //left,right,bottom,top

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	
	drawMenu();
	
	//glDepthMask(GL_TRUE);

	glutSwapBuffers();
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
	WIDTH = w;
	HEIGHT = h;
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
	if(MODE == "DRAW")
	{
		//draw mode mouse function
	}
	else if(MODE == "RUN")
	{
		//run mode mouse function
	}

	glutPostRedisplay();
}


