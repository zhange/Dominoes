void make_floor()
{   
// Material property vectors.
   float matSpec[] = { 0.0, 1.0, 1.0, 1.0 };
   float matShine[] = { 50.0 };
   float matAmbAndDif[] = {0.0, 0.1, 1.0, 1.0};
   
   // Material properties of the objects.
   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpec);
   glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matShine);
   glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matAmbAndDif);

  // Draw a blue grid 
  glColor3f(1, 0, 0);
  glBegin(GL_QUADS);
    glVertex3f(0, 0, 12.5); glVertex3f(WIDTH - 400, 0, 12.5);
    glVertex3f(WIDTH - 400, HEIGHT, 12.5); glVertex3f(0, HEIGHT, 12.5);
  glEnd();


  
}

void draw_domino(domino d)
{
	// Material property vectors.
   float matSpec[] = { 1.0, 0.0, 0.0, 1.0 };
   float matShine[] = { 50.0 };
   float matAmbAndDif[] = {1.0, 0.0, 0.0, 1.0};
   
   // Material properties of the objects.
   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpec);
   glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matShine);
   glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matAmbAndDif);

  float W = WIDTH/2;
  float H = HEIGHT/2;
   
    float x = d.getX();
    float y = d.getY();
    float tilt = d.getTilt()*180/M_PI;
    float norm = d.getNorm()*180/M_PI;
    
    glPushMatrix();
    // rotate then translate...
    glTranslatef(x,y,0);    
    
    // put two rotations in here, one for tilt one for forward
    
    glRotatef(norm, 0 , 0 , 1 );
    glTranslatef(0,0,12.5);
    glRotatef(tilt, 0,  -1 , 0 );
    glTranslatef(0,0,-12.5);
    glScalef(5,15,-25);
    glutWireCube(.75);
    glPopMatrix();
}
//Drawing funciton
void rdraw(void)
{ 
	//Background color
	glClearColor(0,1,1,1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// move back a bit
	if(dominoes.size())
	{
		if(lead == NULL)
		{
			lead = &dominoes[0];
		}
		double centX,centY;
		centX = lead -> getX() + cos(lead -> getTilt())*25*.75*cos(lead -> getNorm());
		centY = lead -> getY() + cos(lead -> getTilt())*25*.75*sin(lead -> getNorm());
		if(CAM == 1)
		{
			gluLookAt(centX + cos(lead -> getNorm())*100 + testThingX, centY + sin(lead -> getNorm())*100 + testThingY, -30, centX, centY, 0, 0, 0, -1);
		}
		else if(CAM == 2)
		{
			gluLookAt(-300 + testThingX, 250 + testThingY, -300, 250, 400, 0, 0, 0, -1);
		}
	}
	else
	{
		gluLookAt(testThingX, testThingY, -300, 0, 0, 0, 0, 0, -1);
	}

	make_floor();

	for (int i = 0; i < dominoes.size(); i++)
	{
		draw_domino(dominoes[i]);
	}
}
