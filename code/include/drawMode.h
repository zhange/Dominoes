// Function to draw all points in the points array.
void drawPoints(void)
{
   // Loop through the points array drawing each point.
   vector<Point>::iterator pointsIterator = points.begin();
   if(points.begin() != points.end())
   {
	   while(pointsIterator != points.end() )
	   {
		  pointsIterator->drawPoint();
		  pointsIterator++;
	   }
   }
}

// Function to draw all points in the points array.
void drawLines(void)
{
   // Loop through the points array drawing each point.
   vector<domino>::iterator domIterator = dominoes.begin();
   if(dominoes.begin() != dominoes.end())
   {
	   while(domIterator != dominoes.end() )
	   {
		  domIterator->drawline();
		  domIterator++;
	   }
   }
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
	}
	temp[temp.size()-1].forward = temp[temp.size()-2].forward;
	
	return temp;
}

//distance formula
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

vector<domino> pointtodomino(vector<Point>pts)
{
	vector<domino>out;
	for(int i=0; i<pts.size(); i++)
	{
		out.push_back(domino(pts[i].x, pts[i].y, pts[i].forward));
	}
	return out;
}


void mousemove(int x, int y)
{
	if(MODE == "DRAW" && x < WIDTH - 400 && x >= 0 && y <= HEIGHT && y >= 0 && !up)
	{
		vector<Point>temp;
		y = HEIGHT - y;
		if(points.size() >= 1)
		{
			temp = interp(points[points.size()-1].x, points[points.size()-1].y, x, y, 12);
		}
		for(int i = 0; i<temp.size(); i++)
		{
			points.push_back(temp[i]);
		}	
		points.push_back( Point(x,y) );
		glutPostRedisplay();
	}
	else
	{
		up = true;
		
		points = removedups(points);
		points = choosepts(points, 10);
		points = calcforward(points);
		dominoes = pointtodomino(points);
		ptslines = 1;			
	}
}

