#include <cstdlib>
#include <vector>
#include <iostream>
#include <cmath>
#include <fstream>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

using namespace std;

#define INACTIVE 0
#define POINT 1

// Use the STL extension of C++.
using namespace std;

// Globals.
static GLsizei width, height; // OpenGL window size.
static float pointSize = 3.0; // Size of point
static int primitive = INACTIVE; // Current drawing primitive.
static int pointCount = 0; // Number of  specified points.
static int tempX, tempY; // Co-ordinates of clicked point.
static int isGrid = 1; // Is there grid?

bool constantline;

// Point class.
class Point
{
public:
   Point(int xVal, int yVal)
   {
	  x = xVal; y = yVal;
   }
   void drawPoint(void); // Function to draw a point.
   
   int x, y; // x and y co-ordinates of point.
   static float size; // Size of point.
};

float Point::size = pointSize; // Set point size.

// Function to draw a point.
void Point::drawPoint()
{  
   glPointSize(size);
   glBegin(GL_POINTS);
      glVertex3f(x, y, 0.0);
   glEnd();   
}

vector<Point> interp (float x1, float y1, float x2, float y2, float interval)
{
	vector<Point>temp;
	float temp1, temp2;
	float t3, t4;
	for(int i =0; i<interval; i++)
	{
		t3 = ((interval-i)/interval);
		t4 = (i/interval);
		temp1 = (t3*x1) + t4*x2;
		temp2 = (t3*y1) + t4*y2;
		temp.push_back(Point(temp1, temp2));
	}
	return temp;
}

vector<Point> removedups(vector<Point>pts)
{
	int temp = 0;
	int i = 1;
	while(i < pts.size())
	{
		if(pts[temp].x == pts[i].x && pts[temp].y == pts[i].y)
		{
			pts.erase(pts.begin()+i);
		}
		else
		{
			i++;
			temp++;
		}
	}
	return pts;
}

vector<Point> choosenth(vector<Point>pts, int n)
{
	int i = 0;
	vector<Point>temp;
	while(i < pts.size())
	{
		temp.push_back(pts[i]);
		i = i+n;
	}
	return temp;
}

// Vector of points.
vector<Point> points;

// Iterator to traverse a Point array.
vector<Point>::iterator pointsIterator; 

// Function to draw all points in the points array.
void drawPoints(void)
{
   // Loop through the points array drawing each point.
   pointsIterator = points.begin();
   while(pointsIterator != points.end() )
   {
      pointsIterator->drawPoint();
	  pointsIterator++;
   }
}

// Drawing routine.
void drawScene(void)
{
   glClear(GL_COLOR_BUFFER_BIT);
   glColor3f(0.0, 0.0, 0.0); 

   drawPoints();

   glutSwapBuffers();
}

// Function to pick primitive if click is in left selection area.
void pickPrimitive(int y)
{
	primitive = POINT;
}

void mousemove( int x, int y)
{
	vector<Point>temp;
	y = height - y;
	cout << points.size() << endl;

	if(points.size() > 1)
		temp = interp(points[points.size()-1].x, points[points.size()-1].y, x, y, 12);
	for(int i = 0; i<temp.size(); i++)
	{
		points.push_back(temp[i]);
		cout << points[points.size()-1].x << " " << points[points.size()-1].y << endl;
	}	
	points.push_back( Point(x,y) );
	
	glutPostRedisplay();
}

// The mouse callback routine.
void mouseControl(int button, int state, int x, int y)
{
	primitive = POINT;
	y = height - y; // Correct from mouse to OpenGL co-ordinates.
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
    	points.push_back( Point(x,y) );
		glutMotionFunc(mousemove);
	}
    glutPostRedisplay();
}

void saveout(vector<Point>pts)
{
	ofstream file;
	file.open("setup.dsx");
	cout << "hai" << endl;
	
	for(int i=0; i<pts.size(); i++)
	{
		file << "<domino>" << "<xpos>"<< pts[i].x << "</xpos><ypos>" << pts[i].y << "</ypos></domino>" << endl;
	}
	
	file.close();
}

// Initialization routine.
void setup(void) 
{
   glClearColor(1.0, 1.0, 1.0, 0.0); 
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
   glViewport(0, 0, (GLsizei)w, (GLsizei)h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   // Set viewing box dimensions equal to window dimensions.
   glOrtho(0.0, (float)w, 0.0, (float)h, -1.0, 1.0);
   
   // Pass the size of the OpenGL window to globals.
   width = w; 
   height = h;  

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
   switch (key) 
   {
      case 27:
         exit(0);
         break;
      case 32:
      {
      	 points = removedups(points);
      	 points = choosenth(points, 10);
         saveout(points);
         break;
      }
      default:
         break;
   }
}

// Clear the canvas and reset for fresh drawing.
void clearAll(void)
{
   points.clear();
   primitive = INACTIVE;
   pointCount = 0;
}

// The right button menu callback function.
void rightMenu(int id)
{
   if (id==1) 
   {
	  clearAll();
	  glutPostRedisplay();
   }
   if (id==2) exit(0);
}

// Function to create menu.
void makeMenu(void)
{
   int sub_menu;
   glutAddMenuEntry("On", 3);
   glutAddMenuEntry("Off",4);

   glutCreateMenu(rightMenu);
   glutAddMenuEntry("Clear",1);
   glutAddMenuEntry("Quit",2);
   glutAttachMenu(GLUT_RIGHT_BUTTON);
}

// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
   cout << "This does stuff " << endl;
}

// Main routine.
int main(int argc, char **argv) 
{
   printInteraction();
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_DOUBLE); 
   glutInitWindowSize(700, 700);
   glutInitWindowPosition(100, 100); 
   glutCreateWindow("drawingstuff.cpp");
   setup(); 
   glutDisplayFunc(drawScene); 
   glutReshapeFunc(resize);  
   glutKeyboardFunc(keyInput);
   glutMouseFunc(mouseControl); 

   makeMenu(); // Create menu.

   glutMainLoop();

   return 0;  
}
