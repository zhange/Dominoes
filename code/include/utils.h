//sets up for 2d mode
void mode2D()
{
	glDisable(GL_LIGHTING);
	glDepthMask(GL_FALSE);
	glDisable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,WIDTH,0,HEIGHT); //left,right,bottom,top

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
}

//sets up for 3d mode
void mode3D()
{
    
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
    
	//Set up projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//Using gluPerspective. It's pretty easy and looks nice.
	
gluPerspective(60, 9.0/5.0, 1, 10000);//gluPerspective(0, 1, 0, 10);
	//Set up modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
}

//writes bitmap string to screen
void writeString(int x, int y, void *font, const char *str)
{
	const char *cs;
	glRasterPos2i(x, y);
	for(cs = str; *cs != '\0'; cs++)
	{
		glutBitmapCharacter(font, *cs);
	}
	glutPostRedisplay();
}

//button drawing function
void drawButton(string name, int row, int column)
{
	int left, right, top, bottom;

	left = WIDTH - 385 + 190*(column - 1);
	right = left + 180;
	top = HEIGHT - 15 - 40*(row - 1);
	bottom = top - 30;	
	
	if((name == "Run Mode" && MODE == "RUN") || (name == "Draw Mode" && MODE == "DRAW"))
	{
		glColor3f(255.0/255.0, 255.0/255.0, 255.0/255.0);
	}
	else
	{
		glColor3f(0.0/255.0, 0.0/255.0, 0.0/255.0);
	}
	glBegin(GL_QUADS);
	glVertex2f(left, top);
	glVertex2f(left, bottom);
	glVertex2f(right, bottom);
	glVertex2f(right, top);
	glEnd();

	if((name == "Run Mode" && MODE == "RUN") || (name == "Draw Mode" && MODE == "DRAW"))
	{
		glColor3f(0.0/255.0, 0.0/255.0, 0.0/255.0);
	}
	else
	{
		glColor3f(255.0/255.0, 255.0/255.0, 255.0/255.0);
	}
	writeString(left + 5 + (180 - 10*name.length())/2, bottom + 8, GLUT_BITMAP_HELVETICA_18, name.c_str());
}

//saves the current dominoes to a file
void saveFile()
{
	ofstream file;
	file.open("setup.dsx");
	
	if(file.is_open())
	{
		for(int i = 0; i < dominoes.size(); i++)
		{
			file << "<domino>\n\t<xpos> " << dominoes[i].getX() << " </xpos>\n\t<ypos> " << dominoes[i].getY() << " </ypos>\n\t<norm> " << dominoes[i].getNorm() << " </norm>\n</domino>" << endl;
		}	
		file.close();
	}
	else
	{
		cout << "Error! File will not open for writing!" << endl;
	}
}

//reads from setup file and populates dominoes vector
void readFile()
{
	ifstream file;
	file.open("setup.dsx");
	
	if(file.is_open())
	{
		dominoes.clear();
		
		string temp;
		double val1,val2,val3;
	
		while(file >> temp)
		{
			if(temp == "<domino>")
			{
				file >> temp;
				if(temp == "<xpos>")
				{
					file >> val1;
					file >> temp;
					if(temp == "</xpos>")
					{
						file >> temp;
						if(temp == "<ypos>")
						{
							file >> val2;
							file >> temp;
							if(temp == "</ypos>")
							{
								file >> temp;
								if(temp == "<norm>")
								{
									file >> val3;
									file >> temp;
									if(temp == "</norm>")
									{
										file >> temp;
										if(temp == "</domino>")
										{
											dominoes.push_back(domino(val1, val2, val3));
											lead = &dominoes[0];											
										}
									}
								}
							}
						}
					}
				}			
			}
		}
		file.close();
	}
	else
	{
		cout << "Error! File will not open for reading!" << endl;
	}
}

//menu drawing function
void drawMenu()
{
	glColor3f(0.0/255.0, 0.0/255.0, 0.0/255.0);
	glBegin(GL_QUADS);
	glVertex2f(WIDTH - 400, 0);
	glVertex2f(WIDTH, 0);
	glVertex2f(WIDTH, HEIGHT);
	glVertex2f(WIDTH - 400, HEIGHT);
	glEnd();

	glColor3f(127.0/255.0, 127.0/255.0, 127.0/255.0);
	glBegin(GL_QUADS);
	glVertex2f(WIDTH - 390, 10);
	glVertex2f(WIDTH - 10, 10);
	glVertex2f(WIDTH - 10, HEIGHT - 10);
	glVertex2f(WIDTH - 390, HEIGHT - 10);
	glEnd();

	for(int i = 0; i < demButtons.size(); i++)
	{
		drawButton(demButtons[i].getName(), demButtons[i].getRow(), demButtons[i].getCol());
	}
}

void reset()
{
	for(int i = 0; i < dominoes.size(); i++)
	{
		dominoes[i].reset();
	}
	
	if(dominoes.size() != 0)
	{
		lead = &dominoes[0];
		leadInd = 0;
	}
}

void fullStep()
{
	
	for(int i = dominoes.size() - 1; i >= 0; i--)
	{
		if(dominoes[i].step() && i == leadInd)
		{
			touchFlag = true;
		}
	}
}

void colDet()
{
	if(touchFlag)
	{
		if(leadInd < dominoes.size() - 1)
		{
			dominoes[leadInd].setSupport(&dominoes[leadInd + 1]);
			lead = &dominoes[leadInd + 1];
			dominoes[leadInd].rest(&dominoes[leadInd + 1]);
			leadInd++;
			dominoes[leadInd].start();
		}
	}
}

void start()
{
	if(dominoes.size())
	{
		dominoes[0].start();
	}
}
