#ifndef _POINT
#define _POINT

//includes
#include <cmath>
#include <vector>
using namespace std;

float pointSize = 3.0;

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

	float x, y; // x and y co-ordinates of point.
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


#endif
