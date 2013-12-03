
void init()
{
/*
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
*/
}


void draw_domino(domino d)
{
  float W = WIDTH/2;
  float H = HEIGHT/2;
   
    float x = d.getX()-W;
    float y = d.getY()-H;
    float tilt = d.getTilt();
    float norm = d.getNorm()/180*3.14;
    
    glPushMatrix();
    
   // put two rotations in here, one for tilt one for forward
    glRotatef(tilt, 1 , 0 , 0 );
    glRotatef(norm, 0 , 1 , 0 );
    //glRotatef(45,forward,rotation,0); // do rotation before translation
    glTranslatef(x,y,0);
    glScalef(1.5, 2.5, .5); //glScalef(.025,.025,.025);
    glColor3f(1,0,0);
            
            glBegin(GL_QUADS);
            glNormal3d(  0,      0,   1 );
            glVertex3f(  0.5, -0.5, 0.5 );
            glVertex3f(  0.5,  0.5, 0.5 );
            glVertex3f( -0.5,  0.5, 0.5 );
            glVertex3f( -0.5, -0.5, 0.5 );
            glEnd();
             
            // Purple side - RIGHT
            glBegin(GL_QUADS);
            glVertex3f( 0.5, -0.5, -0.5 );
            glVertex3f( 0.5,  0.5, -0.5 );
            glVertex3f( 0.5,  0.5,  0.5 );
            glVertex3f( 0.5, -0.5,  0.5 );
            glEnd();
             
            // Green side - LEFT
            glBegin(GL_QUADS);
            glVertex3f( -0.5, -0.5,  0.5 );
            glVertex3f( -0.5,  0.5,  0.5 );
            glVertex3f( -0.5,  0.5, -0.5 );
            glVertex3f( -0.5, -0.5, -0.5 );
            glEnd();
             
            // Blue side - TOP
            glBegin(GL_QUADS);
            glVertex3f(  0.5,  0.5,  0.5 );
            glVertex3f(  0.5,  0.5, -0.5 );
            glVertex3f( -0.5,  0.5, -0.5 );
            glVertex3f( -0.5,  0.5,  0.5 );
            glEnd();
             
            // Red side - BOTTOM
            glBegin(GL_QUADS);
            glVertex3f(  0.5, -0.5, -0.5 );
            glVertex3f(  0.5, -0.5,  0.5 );
            glVertex3f( -0.5, -0.5,  0.5 );
            glVertex3f( -0.5, -0.5, -0.5 );
            glEnd();
             
            glutSwapBuffers();
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
    
    //if(dominos.size()>1)gluLookAt(0.0, 0.0, 50, dominos[0].getX(), dominos[0].getY(), 0.0, 0, 1, 0);
    glTranslatef( 0, 0, -250 );
    //if(dominos.size()>1)gluLookAt(0.0, 0.0, 50, dominos[0].getX(), dominos[0].getY(), 0.0, 0, 1, 0);
  for (int i = 0; i < dominos.size(); i++)
  {
    draw_domino(dominos[i]);
    cout << dominos[i].getX() << " " << dominos[i].getY() << " normal: " << dominos[i].getNorm() << endl;
  }
  //if(dominos.size()>1)gluLookAt(dominos[0].getX(), dominos[0].getY(), 250, dominos[0].getX(), dominos[0].getY(), 0.0, 0, 1, 0);
  // look at first domino ?
  //gluLookAt(0.0, 0.0, 5.0, x.getX(), x.getY(), 0.0, 0.0, 0.0, 1.0);
  
  glutSwapBuffers();
  //Draw order
  // this makes flashy glFlush();
}

//Main program
int r_display()
{
   glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
   rdraw();
   init();
  //glutDisplayFunc(rdraw);
  return 0;
}
