#ifndef _DOMINO
#define _DOMINO

//includes
#include <cmath>
#include <vector>
using namespace std;

//domino class

class domino
{
	private:
		double x;//x position
		double y;//y position
		double norm;//forward vector
		double tilt;//angle of tilt
		int load;//number of dominoes resting on it
		bool standing;//whether or not the domino is standing
		bool resting;//whether of not the domino is resting
		domino* support;//domino it is resting on
		
	public:
		//constructor
		domino(double xpos, double ypos, double forward)
		{
			x = xpos;
			y = ypos;
			norm = forward;
			torque = 0;
			standing = true;
			resting = false;
			support = NULL;
		}
		
		//get the x position
		double getX()
		{
			return x;
		}
		
		//get the y position
		double getY()
		{
			return y;
		}
		
		//get the tilt angle
		double getTilt()
		{
			return tilt;
		}
		
		//get the standing status
		bool isStanding()
		{
			return standing;
		}
		
		//add resting dominues
		void newload(int x)
		{
			load += x;
		}
		
		//timestep
		void step()
		{
			if(!resting)
			{
				double speed = tilt/10 + load; 
				tilt += speed/60;
				if(tilt >= 90)
				{
					tilt = 90;
					resting = true;
				}
			}
			else
			{
				if(tilt != 90)
				{
					double w = sqrt((x - support -> getX())^2 + (y - support -> getY())^2);
					double theta = asin(w*cos(support -> getTilt()/180*M_PI)/2)+support -> getTilt()/180*M_PI;
				}
			}
		}
};

#endif
