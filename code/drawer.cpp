#include <cstdlib>
#include <vector>
#include <iostream>
#include <cmath>
#include <fstream>
#define _USE_MATH_DEFINES

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

int ptslines = 0;
bool constantline;

// Point class.
class Point
{
public:
   Point(int xVal, int yVal)
   {
	  x = xVal; y = yVal; forward = 0;
   }
   void drawPoint(void); // Function to draw a point.
   void drawline(void);
   
   int x, y; // x and y co-ordinates of point.
   float forward; //angle of the domino with respect to the horzizontal
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

void Point::drawline()
{  
   glBegin(GL_LINES);
      glVertex3f(x-5*cos(forward+(M_PI/2)), y-5*sin(forward+(M_PI/2)), 0.0);
      glVertex3f(x+5*cos(forward+(M_PI/2)), y+5*sin(forward+(M_PI/2)), 0.0);
   glEnd();
}

//interpolates the points between 2 points drawn, and inserts them into the vector
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

//remove the duplicates in the vector
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

//calculates the forward of the points in the vector
//forward is the angle of the point with repsect to the horizontal
vector<Point> calcforward(vector<Point>pts)
{
	vector<Point>temp = pts;
	for(int i=0; i<pts.size()-1; i++)
	{
		temp[i].forward = atan2((temp[i].y-temp[i+1].y),(temp[i].x-temp[i+1].x));
		//cout << temp[i].x << " " << temp[i].y << " " << temp[i+1].x << " " << temp[i+1].y << " " << temp[i].forward << endl;
	}
	temp[temp.size()-1].forward = temp[temp.size()-2].forward;
	
	return temp;
}

int dist(Point a, Point b)
{
	return(sqrt(pow(b.x-a.x,2)+pow(b.y-a.y,2)));
}

//chooses the each nth value
vector<Point> choosepts(vector<Point>pts, int n)
{
	//i keeps track in actual
	int i = 0;
	vector<Point>temp;
	temp.push_back(pts[0]);
	while(i < pts.size())
	{
		if(dist(pts[i],temp[temp.size()-1]) > n)
		{
			temp.push_back(pts[i]);
		}
		i++;
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

// Function to draw all points in the points array.
void drawlines(void)
{
   // Loop through the points array drawing each point.
   pointsIterator = points.begin();
   while(pointsIterator != points.end() )
   {
      pointsIterator->drawline();
	  pointsIterator++;
   }
}

// Drawing routine.
void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0); 
	if(ptslines==0)
	{
		drawPoints();
	}
	else
	{
		drawlines();
	}
	glutSwapBuffers();
}

// Function to pick primitive if click is in left selection area.
void pickPrimitive(int y)
{
	primitive = POINT;
}

void mousemove( int x, int y)
{
	ptslines = 0;
	vector<Point>temp;
	y = height - y;

	if(points.size() > 1)
		temp = interp(points[points.size()-1].x, points[points.size()-1].y, x, y, 12);
	for(int i = 0; i<temp.size(); i++)
	{
		points.push_back(temp[i]);
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
	
	for(int i=0; i<pts.size(); i++)
	{
		file << pts[i].x << " " << pts[i].y << " " << pts[i].forward << endl;
	}
	file.close();
}

vector<Point> readfile()
{
	fstream file;
	file.open("setup.dsx");
	
	vector<Point>temp;
	Point p(0,0);
	int a, b;
	float c;
	
	while(file >> a >> b >> c)
	{
		p.x = a;
		p.y = b;
		p.forward = c;
		temp.push_back(p);
	}
	file.close();
	return temp;
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
      //on space output skeleton of the line to a file
      case 32:
      {
      	 points = removedups(points);
      	 points = choosepts(points, 10);
      	 points = calcforward(points);
         saveout(points);
         ptslines = 1;
         glutPostRedisplay();
         break;
      }
      //on tab read in whatever is in the file
      case 9:
      {
      	points = readfile();
      	ptslines = 1;
      	glutPostRedisplay();
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
