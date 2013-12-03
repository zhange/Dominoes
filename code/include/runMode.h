
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
    float norm = d.getNorm()*180/3.14;
    //if (norm >= 100) 
    //norm = 90;
    
    if ( (norm<=1 && norm >=-1) || (norm-180<=1 && norm-180>=-1) ) norm = 90;
    else{
    if (norm <= 0) norm+=180;
    else norm-=90;
    if (norm >90) norm -=90;
    if (norm <=0) norm+=90;
    }
    cout << (int)norm << "  ";
    glPushMatrix();
    // rotate then translate...
    

    //glRotatef(45,forward,rotation,0); // do rotation before translation
    glTranslatef(x,y,0);    
    
    // put two rotations in here, one for tilt one for forward
    
    glRotatef(norm, 0 , 1 , 0 );
    glRotatef(tilt, 1,  0 , 0 );
    //glScalef(1.5, 2.5, .5); //glScalef(.025,.025,.025);
    glScalef(10,25,3);
    //glScalef(.5,.5,.5);
    //glColor3f(1,0,0);
    //glutSolidCube(1);
    glutWireCube(1);
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
    glTranslatef( 0, 0, -300 );
    //if(dominos.size()>1)gluLookAt(0.0, 0.0, 50, dominos[0].getX(), dominos[0].getY(), 0.0, 0, 1, 0);
    gluLookAt(10.0, 10.0, 14.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); 
    
    gluLookAt(0.0, 0.0, 0.0, WIDTH/2, HEIGHT/2, 5.0, 0, 1, 0);
  for (int i = 0; i < dominos.size(); i++)
  {
    draw_domino(dominos[i]);
    cout << dominos[i].getX() << " " << dominos[i].getY() << " normal: " << endl;//dominos[i].getNorm()*180/3.14 << endl;
  }
  //if(dominos.size()>1)gluLookAt(dominos[0].getX(), dominos[0].getY(), 250, dominos[0].getX(), dominos[0].getY(), 0.0, 0, 1, 0);
  // look at first domino ?
  //gluLookAt(0.0, 0.0, 5.0, x.getX(), x.getY(), 0.0, 0.0, 0.0, 1.0);

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
