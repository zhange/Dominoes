
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
    glTranslatef( 0, 0,-50 );
    
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



/// old code ////

/*
#include <stdio.h>

void draw_domino(domino d)
{
    float x = d.getX();
    float y = d.getY();

    glPushMatrix();
    glTranslatef(x,y,0);
    glRotatef(90,1,0,0);
    glScalef(.5,.5,1);
    glColor3f(1,0,0);
    glutSolidCube(100);
    glPopMatrix();
}
void rdisplay()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    float pos[] = {200,200,0};
    float dif[] = {.3,.3,.3,3};
    float spe[] = {1,1,1,1};
    float amb[] = {1,1,1,0};
    glLightfv(GL_LIGHT0,GL_POSITION,pos);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,dif);
    glLightfv(GL_LIGHT0,GL_AMBIENT,amb);
    glLightfv(GL_LIGHT0,GL_SPECULAR,spe);

    //glTranslatef(50,50,0);
    //glRotatef(30,1,0,0);
    //glRotatef(-30,0,1,0);

    //xgluPerspective(0, 1, 0, 10);
    
    // creating the domino
    domino x(0,0,0);

    draw_domino(x);

    //glFlush();
}
void reshape(int w,int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,400,0,400,-400,400);
    glMatrixMode(GL_MODELVIEW);
    //gluLookAt(0,  0,  0,  0,  0,  0,  0,  0,  0);
}

void r_display()
{
    //glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(400,400);
    glutCreateWindow("runmode.h");
    glClearColor(0,0,0,0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);


    glShadeModel(GL_SMOOTH);
    glutReshapeFunc(reshape);
    glutDisplayFunc(rdisplay);

    glutMainLoop();
}
*/
