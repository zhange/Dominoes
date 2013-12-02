
void init()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
}

void draw_domino(domino d)
{
   
    float x = d.getX();
    float y = d.getY();
    
    
    glPushMatrix();
    glTranslatef(x,y,0);
    //glRotatef(angle,0,0,0); // do rotation before translation
    glScalef(1, 2.5, .5);
    glColor3f(1,0,0);
    glutSolidCube(5);
    glPopMatrix();
}
//Drawing funciton
void rdraw(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //Background color
  glClearColor(0,1,1,1);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

    // move back a bit
    glTranslatef( 0, 0, -50 );
    
    glPushMatrix();
    glScalef(1, 2.5, .5);
    glColor3f(1,0,0);
    glutSolidCube(5);
    glPopMatrix();
  /*

  domino x(0,0,0);
  draw_domino(x);
  // look at first domino ?
  //gluLookAt(0.0, 0.0, 5.0, x.getX(), x.getY(), 0.0, 0.0, 0.0, 1.0);
  
  domino y(-10,-10,0);
  draw_domino(y);
  */
  
  glutSwapBuffers();
  //Draw order
  // this makes flashy glFlush();
}

//Main program
int r_display()
{
   glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
   rdraw();
   init();
  //glutDisplayFunc(rdraw);
  return 0;
}
