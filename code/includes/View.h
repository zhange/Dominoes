//includes
#include <iostream>

#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/gl.h>


#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

using namespace std;

//function prototype
void setDualPorts(int w, int h);


int vMain()
{

	// int w = glutGet(GLUT_WINDOW_WIDTH);
	// int h = glutGet(GLUT_WINDOW_HEIGHT);

	//setDualPorts(w,h);

	return 0;
}




void setDualPorts(int width, int height)
{
	   // Begin left viewport.
   glViewport (0, 0, width/2.0,  height); 
   glLoadIdentity();

   // Write text in isolated (i.e., before gluLookAt) translate block.
   glPushMatrix();
   if (true) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,'l');
   glPopMatrix();

   // Fixed camera.
   gluLookAt(0.0, 10.0, 20.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
 
   // End left viewport.


   // Begin right viewport.
   glViewport(width/2.0, 0, width/2.0, height);
   glLoadIdentity();

   // Write text in isolated (i.e., before gluLookAt) translate block.
   glPushMatrix();
   if (true) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'r');
   glPopMatrix();

   // Draw a vertical line on the left of the viewport to separate the two viewports
   glColor3f(1.0, 1.0, 1.0);
   glLineWidth(2.0);
   glBegin(GL_LINES);
   glVertex3f(-5.0, -5.0, -5.0);
   glVertex3f(-5.0, 5.0, -5.0);
   glEnd();
   glLineWidth(1.0);

   // End right viewport.
   glutSwapBuffers();
}