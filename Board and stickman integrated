#include <windows.h>
#include <gl\glut.h>
#include <iostream>
using namespace std;

int c = 0;

void stickman(void) 
{ glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix

glLoadIdentity();  
glTranslatef(-33.5f, -33.5f, -60.0f);
 
 glColor3f(0.0, 1.0, 0.0); 
 glBegin(GL_POLYGON); 
  glVertex3f((4.0+25.0)*0.5, (6.5+25)*0.5, -1.0); 
  glVertex3f((6.0+25)*0.5, (6.5+25)*0.5, -1.0); 
  glVertex3f((6.0+25)*0.5, (8.5+25)*0.5, -1.0); 
  glVertex3f((4.0+25)*0.5, (8.5+25)*0.5, -1.0); 
 glEnd(); 
 glFlush(); 
 
  glColor3f(0.0, 1.0, 0.0); 
  glBegin(GL_LINES); 
  glVertex3f((5.0+25)*0.5, (6.5+25)*0.5, -1.0); 
  glVertex3f((5.0+25)*0.5, (3.0+25)*0.5, -1.0);
  glVertex3f((3.5+25)*0.5, (5.1+25)*0.5, -1.0); 
  glVertex3f((6.5+25)*0.5, (5.1+25)*0.5, -1.0);
  glVertex3f((5.0+25)*0.5, (3.0+25)*0.5, -1.0); 
  glVertex3f((3.5+25)*0.5, (1.0+25)*0.5, -1.0);
  glVertex3f((5.0+25)*0.5, (3.0+25)*0.5, -1.0); 
  glVertex3f((6.5+25)*0.5, (1.0+25)*0.5, -1.0);

  glEnd(); 
  glFlush();
 
}

void drawSquare(GLint x1, GLint y1, GLint x2, GLint y2, GLint x3, GLint y3, GLint x4, GLint y4)
{
// c alternates color of square
if (c == 0)
{
glColor3f(0.6, 0, 0); 
c = 1;
}
else
{
glColor3f(0, 0, 0); 
c = 0;
}

// Draw Square

glBegin(GL_POLYGON);

glVertex3f(x1*0.08, y1*0.08,-4.0);
glVertex3f(x2*0.08, y2*0.08,-4.0);
glVertex3f(x3*0.08, y3*0.08,-4.0);
glVertex3f(x4*0.08, y4*0.08,-4.0);
glEnd();
}

void board()
{
glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix
glClear(GL_COLOR_BUFFER_BIT);

glLoadIdentity();  
glTranslatef(-25.0f, -25.0f, -60.0f);
int x, y;

c = 0; //so that mouse click does not swap colors of squares

for (x = 25; x <= 475; x += 75)
{
for (y = 25; y <= 475; y += 75)
{
drawSquare(x, y + 75, x + 100, y + 75, x + 100, y, x, y);
}
}
// Process all OpenGL routines as quickly as possible

stickman();

}

 
void reshape(int width, int height) {  // GLsizei for non-negative integer
   // aspect ratio of the new window:
   if (height == 0 || width == 0) return;                // To prevent divide by 0
   glMatrixMode(GL_PROJECTION);  // Projection matrix operated on
   glLoadIdentity();             
   GLfloat aspect = (GLfloat)width / (GLfloat)height;

   gluPerspective(45.0f, aspect, 0.1f, 1000.0f);
   glMatrixMode(GL_MODELVIEW);  // Projection matrix operated on
 
   glViewport(0, 0, width, height);// Set the viewport to cover the new window
	
   // Perspective projection parameters - fovy, aspect, zNear and zFar
}

void TimerFunc(int extra)
{
    glutPostRedisplay();
    glutTimerFunc(1000 , TimerFunc, 0);
}

int main(int agrc, char ** argv)
{
glutInit(&agrc, argv);
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
glutInitWindowPosition(100, 100);
glutInitWindowSize(800, 600);
glutCreateWindow("War of Stick Men");

// for setting the transformation (here it is 2D)

glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
glutDisplayFunc(board);

glutReshapeFunc(reshape);

glutTimerFunc(2000,TimerFunc,0);
 
glutMainLoop();
return 0;
}





