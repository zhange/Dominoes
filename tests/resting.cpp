#include <cmath>
#include <iostream>
using namespace std;

int main()
{
	while(true)
	{
		double h,d,o,n;
		
		cout << "height = ";
		cin >> h;
		cout << "distance = ";
		cin >> d;
		cout << "old angle = ";
		cin >> o;
		
		n = asin(d*sin(o/180*M_PI)/h)+o/180*M_PI;
		n = abs(n);
		cout << n/M_PI*180 << endl;
	}
}
