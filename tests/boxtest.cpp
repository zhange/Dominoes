#include <iostream>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

using namespace std;

// Globals.
static int objID = 4; // Object ID.
static float Xangle = 0.0, Yangle = 0.0, Zangle = 0.0; // Angles to rotate objects.
static char *objName; // Pointer to object name.

// Routine to draw a stroke character string.
void writeStrokeString(void *font, char *string)
{  
   char *c;

   for (c = string; *c != '\0'; c++) glutStrokeCharacter(font, *c);
}

// Routine to write object name.
void writeObjectName()
{
   glPushMatrix();
   glTranslatef(-4.5, 10.0, -20.0);
   glScalef(0.01, 0.01, 0.01);
   writeStrokeString(GLUT_STROKE_ROMAN, objName);
   glPopMatrix();
}

// Drawing routine.
void drawScene()
{
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glLoadIdentity();
   
   // Position the objects for viewing.
   gluLookAt(10.0, 10.0, 14.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); 
    glLineWidth(2.0); // Thicken the wireframes.

   // Commands to turn the objects.
   glPushMatrix();
   glRotatef(Zangle, 0.0, 0.0, 1.0);
   glRotatef(Yangle, 1.0, 1.0, 0.0);
   glRotatef(Xangle, 1.0, 0.0, 0.0);

   // Draw objects.
   switch(objID)
   {
      case 3:
         glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
      // Define vertices in counter-clockwise (CCW) order with normal pointing out
      
		 objName = "Solid Cube";
         break;
      case 4:
         glutSolidCube(3.0);
		 objName = "Wire Cube";
         break;
      default:
		 break;
   }
   glPopMatrix();

   // Write label after disabling lighting.
   glDisable(GL_LIGHTING);
   glColor3f(0.0, 0.0, 0.0);
   writeObjectName();
   glEnable(GL_LIGHTING);

   glutSwapBuffers();
}

// Initialization routine.
void setup(void)
{
   // Material property vectors.
   float matSpec[] = { 0.0, 1.0, 1.0, 1.0 };
   float matShine[] = { 50.0 };
   float matAmbAndDif[] = {0.0, 0.1, 1.0, 1.0};

   // Light property vectors.
   float lightAmb[] = { 0.0, 0.1, 1.0, 1.0 };
   float lightDifAndSpec[] = { 0.0, 0.1, 1.0, 1.0 };
   float lightPos[] = { 0.0, 7.0, 3.0, 0.0 };
   float globAmb[] = { 0.2, 0.2, 0.2, 1.0 };

   // Material properties of the objects.
   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpec);
   glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matShine);
   glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matAmbAndDif);

   // Light0 properties.
   glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDifAndSpec);
   glLightfv(GL_LIGHT0, GL_SPECULAR, lightDifAndSpec);
   glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    
   // Poperties of the ambient light.
   glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb); // Global ambient light.

   glEnable(GL_LIGHTING); // Enable lighting calculations.
   glEnable(GL_LIGHT0); // Enable particular light source.
   glEnable(GL_DEPTH_TEST); // Enable depth testing.

   glEnable(GL_NORMALIZE); // Enable automatic normalization of normals.

   glClearColor(1.0, 1.0, 1.0, 0.0);
}

// OpenGL window reshape routine.
void resize (int w, int h)
{
   glViewport (0, 0, (GLsizei)w, (GLsizei)h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(60.0, (float)w/(float)h, 1.0, 50.0);
   glMatrixMode(GL_MODELVIEW);
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
   switch (key) 
   {
      case 27:
         exit(0);
         break;
      default:
         break;
   }
}

// Callback routine for non-ASCII key entry.
void specialKeyInput(int key, int x, int y)
{

   Xangle = Yangle = Zangle = 0.0;
   glutPostRedisplay();
}

// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
   cout << "Interaction:" << endl;
   cout << "Press the arrow keys to cycle through the objects." << endl
        << "Press x, X, y, Y, z, Z to turn the objects." << endl; 
}

// Main routine.
int main(int argc, char **argv) 
{
   printInteraction();
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 
   glutInitWindowSize (500, 500);
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("glutObjects.cpp");
   setup();
   glutDisplayFunc(drawScene);
   glutReshapeFunc(resize);
   glutKeyboardFunc(keyInput);
   glutSpecialFunc(specialKeyInput);
   glutMainLoop();
   
   return 0;
}
