#ifndef _DOMINO
#define _DOMINO

//includes

//domino class

class domino
{
	private:
		double x;//x position
		double y;//y position
		double norm;//forward vector
		double tilt;//angle of tilt
		double torque;//torque on domino about front bottom edge
		bool standing;//whether or not the domino is standing
		
	public:
		domino(double xpos, double ypos, double forward)
		{
			x = xpos;
			y = ypos;
			norm = forward;
			standing = true;
		}
		double getX()
		{
			return x;
		}
		double getY()
		{
			return y;
		}
		bool isStanding()
		{
			return standing;
		}
		void move(double xpos, double ypos)
		{
			x = xpos;
			y = ypos;
		}
		void rotate(double forward)
		{
			norm = forward;
		}
};

//member function implementations

#endif
