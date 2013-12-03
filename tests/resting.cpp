#include <cmath>
#include <iostream>
using namespace std;

int main()
{
	while(true)
	{
		double tilt, w, d;
		
		cout << "tilt = ";
		cin >> tilt;
		cout << "w = ";
		cin >> w;
		d = 2;
		
		double theta = asin(w*cos(tilt/180*M_PI)/2)+tilt/180*M_PI;
		cout << theta/M_PI*180 << endl;
	}
}
