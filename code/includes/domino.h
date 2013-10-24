#ifndef _DOMINO_H
#define _DOMINO_H

//includes

//domino class

class Point
{
	private:
		int x;
		int y;
		bool down;
	  
	public:
		Point(int i, int j, bool press)
		{
			x = i;
			y = j;
			down = press;
		}
		int getX()
		{
			return x;
		}
		int getY()
		{
			return y;
		}
		bool getDown()
		{
			return down;
		}
};

//member function implementations

#endif
