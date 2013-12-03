

void make_floor()
{   
// Material property vectors.
   float matSpec[] = { 0.0, 1.0, 1.0, 1.0 };
   float matShine[] = { 50.0 };
   float matAmbAndDif[] = {0.0, 0.1, 1.0, 1.0};

    float t = 1000*WIDTH;
    
  //glClear(GL_COLOR_BUFFER_BIT);

  // Draw a blue grid 
  glColor3f(1, 0, 0);
  glBegin(GL_QUADS);
    glVertex3f(0, 0, 0); glVertex3f(t, 0, 0);
    glVertex3f(t, t, 0); glVertex3f(0, t, 0);
  /*
  for (GLfloat i = -t; i <= t; i += t/1000) {
    glVertex3f(i, t, 0); glVertex3f(i, -t, 0);
    glVertex3f(t, i, 0); glVertex3f(-t, i, 0);
  }
  */
  glEnd();


  
}

void draw_domino(domino d)
{
	// Material property vectors.
   float matSpec[] = { 1.0, 1.0, 0.0, 1.0 };
   float matShine[] = { 50.0 };
   float matAmbAndDif[] = {1.0, 0.1, 0.0, 1.0};

  float W = WIDTH/2;
  float H = HEIGHT/2;
   
    float x = d.getX();
    float y = d.getY();
    float tilt = d.getTilt();
    float norm = d.getNorm()*180/3.14;
    //if (norm >= 100) 
    //norm = 90;
    
    // normalize stuff //
    /*
    if ( (norm<=1 && norm >=-1) || (norm-180<=1 && norm-180>=-1) ) norm = 90;
    else{
    if (norm <= 0) norm+=180;
    else norm-=90;
    if (norm >90) norm -=90;
    if (norm <=0) norm+=90;
    }
    */
    cout << (int)norm << "  ";
    glPushMatrix();
    // rotate then translate...
    

    //glRotatef(45,forward,rotation,0); // do rotation before translation
    glTranslatef(x,y,0);    
    
    // put two rotations in here, one for tilt one for forward
    
    glRotatef(norm, 0 , 0 , 1 );
    glRotatef(tilt, 0,  1 , 0 );
    //glScalef(1.5, 2.5, .5); //glScalef(.025,.025,.025);
    glScalef(5,15,-25);
    //glScalef(.5,.5,.5);
    //glColor3f(1,0,0);
    //glutSolidCube(.75);
    glutWireCube(.75);
    glPopMatrix();
}
//Drawing funciton
void rdraw(void)
{

 // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
  //Background color
  glClearColor(0,1,1,1);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

    // move back a bit
    
    //if(dominoes.size()>1)gluLookAt(0.0, 0.0, 50, dominoes[0].getX(), dominoes[0].getY(), 0.0, 0, 1, 0);
    glTranslatef( 0, 0, -300 );

    //if(dominoes.size()>1)gluLookAt(0.0, 0.0, 50, dominoes[0].getX(), dominoes[0].getY(), 0.0, 0, 1, 0);
    // need 2 to give it perspective, or maybe just one done right
    //gluLookAt(10.0, 10.0, -14.0, 0.0, 0.0, 0.0, 0.0, 0, -1); 
    if(dominoes.size())
    {
    	gluLookAt(lead -> getX() - 25, lead -> getY() - 25, -25, lead -> getX(), lead -> getY(), 0, 0, 0, -1);
	}
	else
	{
		gluLookAt(-25, -25, -25, 0, 0, 0, 0, 0, -1);
	}
    
    make_floor();
    
  for (int i = 0; i < dominoes.size(); i++)
  {
    draw_domino(dominoes[i]);
    cout << dominoes[i].getX() << " " << dominoes[i].getY() << " normal: " << endl;//dominoes[i].getNorm()*180/3.14 << endl;
  }

}

//Main program
int r_display()
{
   glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
   rdraw();
  
  return 0;
}
