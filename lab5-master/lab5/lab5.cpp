#include <cmath>
#include <cstdlib>
#include <iostream>
#include "tga.h"
using namespace std;


#ifdef __APPLE__
  #include <GLUT/glut.h>         /* glut.h includes gl.h and glu.h*/
#else
  #include <GL/glut.h>         /* glut.h includes gl.h and glu.h*/
#endif

#define X_AXIS 1
#define Y_AXIS 2
#define Z_AXIS 3
#define STOP 4

#define MAX_TEXTURES 	 10  	// max textures displayed
//*****************************************************************
// Begin: Global variables about the camera location and orientation
//*****************************************************************

//Camera on y = 0 plan, circling around (0,0,0)
//The following variable records the current angle between the vector (1,0,0) and (eyex, eyey, eyez)
double C_angle;

const double PI = 3.14156;

//Camera on y = 0 plan, circling around (0,0,0)
//The following variable records the radius of the camera's orbit
double C_Radius;

//Camera on y = 0 plan, circling around (0,0,0)
//The following variable records the rotation speed of the camera
double C_increment;

double prev_C_increment;

//Camera on y = 0 plan, circling around (0,0,0)
//Recording the currnet position of the camera.
double eyex, eyey, eyez; 

//Camera on y = 0 plan, circling around (0,0,0)
//Specifies the position of the point looked at
double centerx, centery, centerz; 
	

//Specifies the direction of the up vector. 
double upx, upy, upz;

char currentAxis;
GLuint textureArray[MAX_TEXTURES];
//*****************************************************************
// End of Globa variables about the camera location and orientation
//*****************************************************************

void drawAxesXYZ()
{	//Draw XYZ axes
	glBegin(GL_LINES);
	
		glColor3f(1,0,0);
		glVertex3f(0,0,0);
		glVertex3f(15,0,0);

		glColor3f(0,1,0);
		glVertex3f(0,0,0);
		glVertex3f(0,15,0);

		glColor3f(0,0,1);
		glVertex3f(0,0,0);
		glVertex3f(0,0,15);

	glEnd();

	//Show the X, Y, Z letters
	glColor3f(1,0,0);
	glRasterPos3f(5, 0, 0);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'X');

	glColor3f(0, 1, 0);
	glRasterPos3f(0, 5, 0);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'Y');

	glColor3f(0, 0, 1);
	glRasterPos3f(0, 0, 5);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'Z');

}

void init()
{
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
    glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);

	float scale = 30.0;

	/* set clear color to black */
	glClearColor (0.0, 0.0, 0.0, 0.0);

	/* set fill  color to white */
	glColor3f(1.0, 1.0, 1.0);

	/* set up standard orthogonal view with clipping */
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	//glOrtho(-scale, scale, -scale, scale, 0.1, 5*scale);
	gluPerspective(90, 1, 0.1, 100);


	//setup all textures
	glEnable(GL_TEXTURE_2D);	
    CreateTexture(textureArray,"concrete2.tga",0);
	CreateTexture(textureArray,"bricks.tga",1);
	CreateTexture(textureArray,"sky.tga",2);
	CreateTexture(textureArray,"grass.tga",3);
}


void initCameraSetting()
{	
//The following variable records the current angle between the vector (1,0,0) and (eyex, eyey, eyez)
	C_angle = 0;

//Camera on y = 0 plan, circling around (0,0,0)
//The following variable records the radius of the camera's orbit
	C_Radius = 13;

//Camera on y = 0 plan, circling around (0,0,0)
//The following variable records the rotation speed of the camera
	C_increment = (2*PI / (360*2)  );

//Recording the currnet position of the camera.
	eyex = 0; eyey = 0; eyez = C_Radius;//C_Radius;

//Specifies the position of the point looked at as (0,0,0).
	centerx = 0; centery = 0; centerz=0;

//Specifies the direction of the up vector. 
	upx = 0; upy=1;  upz=0;

	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	//gluLookAt(eyex, eyey, eyez, centerx, centery, centerz, upx, upy, upz);

	//glMatrixMode (GL_PROJECTION);

//specify which axis we are rotating around
	currentAxis = 'y';

}

void moveCamera()
{	
	//Camera on y = 0 plan, circling around (0,0,0)
	//The following variable records the current angle between the vector (1,0,0) and (eyex, eyey, eyez)
	C_angle += C_increment;


	if ( C_angle > 2*PI)
		C_angle -= 2*PI;

	if (currentAxis == 'y') //checks what axis we are currently want to be orbiting around
	{
		eyex = C_Radius * cos(C_angle);
		eyey = 0;
		eyez = C_Radius * sin(C_angle);
	}

	else if (currentAxis == 'x') //checks what axis we are currently want to be orbiting around
	{
		 eyex=0;
		 eyey=C_Radius*cos(C_angle);
	     eyez=C_Radius*sin(C_angle);
		 upx=0;
		 upy=cos(C_angle+PI/2);
		 upz=sin(C_angle+PI/2);
	}

	else if (currentAxis == 'z') //checks what axis we are currently want to be orbiting around
	{
		 eyex=C_Radius*cos(C_angle);
		 eyey=C_Radius*sin(C_angle);
	     eyez=0;
		 upx=cos(C_angle+PI/2);;
		 upy=sin(C_angle+PI/2);
		 upz=0;
	}

	glutPostRedisplay();

}

void keyboard (unsigned char key, int x, int y)
{
   switch (key) {
      case 'j': //increase the rotational speed
         C_increment+= 0.0005;
         glutPostRedisplay();
         break;
      case 'k': //decrease the rotational speed
		if (C_increment <= 0.0005)
			C_increment = 0.0;
		else
			C_increment-= 0.0005;
         glutPostRedisplay();
         break;
      case 'i': //increase the radius of orbit of the rotating camera
         C_Radius++;
         glutPostRedisplay();
         break;
      case 'm': //decrease the radius of orbit of the rotating camera
         C_Radius--;
         glutPostRedisplay();
         break;
      case 'x': //rotate around the x axis
		 currentAxis = 'x';
         glutPostRedisplay();
         break;
	  case 'y': //rotate around the y axis
		 currentAxis = 'y';
         upx = 0; 
		 upy=1;  
		 upz=0;
         glutPostRedisplay();
         break;
      case 'z': //rotate around the z axis
		 currentAxis = 'z';
         glutPostRedisplay();
         break;
      default:
         break;
   }
}

//*****************************************************
//A global GLUquadricObj object dynamically allocated 
//	for drawing GLU guadric objects in display() 
//*****************************************************
GLUquadricObj * ptrToQuadricInfo;
GLUquadric * ptrToGLUquadricInfo;

//***************************************************************
//OpenGL commands to regenerate the scene saved in two functions:
//		display() and reshape( int w, int h)
//***************************************************************
void reshape(int w, int h)
{

 float left = -5.2;
 float right = 5.2;
 float bottom = -5.2;
 float top = 5.2;
 float near = 0.1;
 float far = 50;

 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();

 if (w >= h)
     glOrtho( left * ( float(w)/ float(h)), right * ( float(w)/ float(h)),
              bottom, top,
              near, far
            );
 else
     glOrtho(  left , right , 
               bottom*( float(h)/ float(w)), top* ( float(h)/ float(w)),
               near, far
            );

 glMatrixMode(GL_MODELVIEW);


}

void createBell()
{
	//sphere for the top of the bell
	 glPushMatrix();
	 glColor3f(0.65,0.75,0.70); //color it
	 glutSolidSphere(.5, 200, 50);
	 glPopMatrix();
	 //cone for the bottom of the bell
	 glPushMatrix();
	 glTranslatef(0.0, -0.5, 0.0); //move it
	 glRotatef(-90, 1.0, 0.0, 0.0); //rotate it
	 glutSolidCone(.65, 1, 75, 4);
	 glPopMatrix();
	//sphere for the ball at the bottom of the bell
	 glPushMatrix();
	 glColor3f(0.65,0.75,0.70); //color it
	 glTranslatef(0.15, -0.60, 0.0); //move it
	 glutSolidSphere(.13, 100, 30);
	 glPopMatrix();
	 //the part at the top of the bell that connects it to the columns
	 glPushMatrix();
	 glColor3f(1,0.3,0.45); //color it
	 glTranslatef(0.0, 0.70, 0.0); //move it
	 glScalef(0.70,2,0.70); //scale it
	 glutSolidCube(.25); 
	 glPopMatrix();
}

void createBase()
{
	 glColor3f(1,0.5,0.5);
	 glBindTexture(GL_TEXTURE_2D, textureArray[1]);

	 glBegin(GL_QUADS);
	 glTexCoord2f(1, 1); glVertex3f(-.5, .25, 0.5);
	 glTexCoord2f(0, 1); glVertex3f(-.5, .25, -0.5);
	 glTexCoord2f(0, 0); glVertex3f(-.5, -.25, -0.5);
	 glTexCoord2f(1, 0); glVertex3f(-.5, -.25, 0.5);
	 glEnd();

	 glBegin(GL_QUADS);
	 glTexCoord2f(1, 1); glVertex3f(.5, .25, 0.5);
	 glTexCoord2f(0, 1); glVertex3f(.5, .25, -0.5);
	 glTexCoord2f(0, 0); glVertex3f(.5, -.25, -0.5);
	 glTexCoord2f(1, 0); glVertex3f(.5, -.25, 0.5);
	 glEnd();

	 glBegin(GL_QUADS);
	 glTexCoord2f(1, 1); glVertex3f(.5, .25, 0.5);
	 glTexCoord2f(1, 0); glVertex3f(.5, -.25, 0.5);
	 glTexCoord2f(0, 0); glVertex3f(-.5, -.25, 0.5);
	 glTexCoord2f(0, 1); glVertex3f(-.5, .25, 0.5);
	 glEnd();

	 glBegin(GL_QUADS);
	 glTexCoord2f(1, 1); glVertex3f(.5, .25, -0.5);
	 glTexCoord2f(1, 0); glVertex3f(.5, -.25, -0.5);
	 glTexCoord2f(0, 0); glVertex3f(-.5, -.25, -0.5);
	 glTexCoord2f(0, 1); glVertex3f(-.5, .25, -0.5);
	 glEnd();
}

void createGrass()
{

	 glBindTexture(GL_TEXTURE_2D, textureArray[3]);
	 glColor3f(1,1,1);
	 glBegin(GL_QUADS);
	 glTexCoord2f(0, 0); glVertex3f(-0.425, 0.270, 0.425);
	 glTexCoord2f(0, 1.0); glVertex3f(-0.425, 0.270, -0.425);
	 glTexCoord2f(1.0, 1.0); glVertex3f(0.425, 0.270, -0.425);
	 glTexCoord2f(1.0, 0); glVertex3f(0.425, 0.270, 0.425);
	 glEnd();

}

void createSky()
{
	 glBindTexture(GL_TEXTURE_2D, textureArray[2]);
	 glColor3f(1,1,1);
	 glBegin(GL_QUADS);
	 glTexCoord2f(0, 0); glVertex3f(-20, 20, 20);
	 glTexCoord2f(0, 1.0); glVertex3f(-20, 20, -20);
	 glTexCoord2f(1.0, 1.0); glVertex3f(20, 20, -20);
	 glTexCoord2f(1.0, 0); glVertex3f(20, 20, 20);
	 glEnd();

	 glBegin(GL_QUADS);
	 glTexCoord2f(0, 0); glVertex3f(-20, 20, 20);
	 glTexCoord2f(0, 1.0); glVertex3f(-20, -.27, 20);
	 glTexCoord2f(1.0, 1.0); glVertex3f(20, -.27, 20);
	 glTexCoord2f(1.0, 0); glVertex3f(20, 20, 20);
	 glEnd();

	 glBegin(GL_QUADS);
	 glTexCoord2f(0, 0); glVertex3f(-20, 20, -20);
	 glTexCoord2f(0, 1.0); glVertex3f(-20, -.27, -20);
	 glTexCoord2f(1.0, 1.0); glVertex3f(20, -.27, -20);
	 glTexCoord2f(1.0, 0); glVertex3f(20, 20, -20);
	 glEnd();

	 glBegin(GL_QUADS);
	 glTexCoord2f(0, 0); glVertex3f(-20, 20, -20);
	 glTexCoord2f(0, 1.0); glVertex3f(-20, -.27, -20);
	 glTexCoord2f(1.0, 1.0); glVertex3f(-20, -.27, 20);
	 glTexCoord2f(1.0, 0); glVertex3f(-20, 20, 20);
	 glEnd();

	 glBegin(GL_QUADS);
	 glTexCoord2f(0, 0); glVertex3f(20, 20, -20);
	 glTexCoord2f(0, 1.0); glVertex3f(20, -.27, -20);
	 glTexCoord2f(1.0, 1.0); glVertex3f(20, -.27, 20);
	 glTexCoord2f(1.0, 0); glVertex3f(20, 20, 20);
	 glEnd();
}

void display()
{


	 ////Select the ModelView matrix 
	 glMatrixMode(GL_MODELVIEW);
	 glLoadIdentity();

	 gluLookAt
	 ( eyex, eyey, eyez, centerx, centery, centerz, upx, upy, upz);
	 //View the object through the camera settings

	 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	 
	 glBindTexture(GL_TEXTURE_2D, textureArray[0]);
	 glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	 glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	 glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	 //glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	 glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

	 glColor3f(1,1,1);
	 glBegin(GL_QUADS);
	 glTexCoord2f(-7.0, -7.0); glVertex3f(-20, -.27, 20);
	 glTexCoord2f(-7.0, 1.0); glVertex3f(-20, -.27, -20);
	 glTexCoord2f(1.0, 1.0); glVertex3f(20, -.27, -20);
	 glTexCoord2f(1.0, -7.0); glVertex3f(20, -.27, 20);
	 glEnd();

	 //base one
	 glPushMatrix();
	 glTranslatef(0, 0, -2); //move it
	 createBase();
	 glPopMatrix();

	 //base one grass
	 glPushMatrix();
	 glColor3f(0.0,1,0.0); //color it
	 glScalef(0.85,0.60,0.85); //scale it
	 glTranslatef(0, 0.10, -2.35); //move it
	 glutSolidCube(1); 
	 glPopMatrix();
	 
	 //base two
	 glPushMatrix();
	 glTranslatef(-2, 0, 2); //move it
	 createBase();
	 glPopMatrix();


	 //base two grass
	 glPushMatrix();
	 glColor3f(0,1,0); //color it
	 glScalef(0.85,0.60,0.85); //scale it
	 glTranslatef(-2.35, 0.10, 2.35); //move it
	 glutSolidCube(1); 
	 glPopMatrix();

	 //base three
	 glPushMatrix();
	 glTranslatef(4, 0, 0); //move it
	 createBase();
	 glPopMatrix();

	 //base three grass
	 glPushMatrix();
	 glColor3f(0,1,0); //color it
	 glScalef(0.85,0.60,0.85); //scale it
	 glTranslatef(4.75, 0.10, 0.0); //move it
	 glutSolidCube(1); 
	 glPopMatrix();

	 //tallest column
	 glPushMatrix();
	 glColor3f(1,0.3,0.45); //color it
	 glTranslatef(1.85, 3.75, 0); //move it
	 glRotatef(32, 0.0, 0.0, 1.0); //rotate it
	 glScalef(0.4,9.25,0.4); //scale it
	 glutSolidCube(1); 
	 glPopMatrix();

	 //2nd tallest column
	 glPushMatrix();
	 glColor3f(1,0.3,0.45); //color it
	 glTranslatef(0, 3.25, -0.95); //move it
	 glRotatef(16, 1.0, 0.0, 0.0); //rotate it
	 glScalef(0.4,7,0.4); //scale it
	 glutSolidCube(1); 
	 glPopMatrix();

	 //shortest column
	 glPushMatrix();
	 glColor3f(1,0.3,0.45); //color it
	 glTranslatef(-1, 2.25, 0.75); //move it
	 glRotatef(-30, 1.0, 0.0, 0.0); //rotate it
	 glRotatef(-20, 0.0, 0.0, 1.0); //rotate it
	 glScalef(0.4,5.75,0.4); //scale it
	 glutSolidCube(1); 
	 glPopMatrix();

	 //first bell
	 glPushMatrix();
	 glScalef(0.85,0.85,0.85); //scale it
	 glTranslatef(0.65, 5.60, 0); //move it
	 createBell();
	 glPopMatrix();

	 //second bell
	 glPushMatrix();
	 glScalef(0.70,0.70,0.70); //scale it
	 glTranslatef(2, 5, 0); //move it
	 createBell();
	 glPopMatrix();

	 //third bell
	 glPushMatrix();
	 glScalef(0.60,0.60,0.60); //scale it
	 glTranslatef(3.65, 3.90, 0); //move it
	 createBell();
	 glPopMatrix();

	 //fourth bell
	 glPushMatrix();
	 glScalef(0.45,0.45,0.45); //scale it
	 glTranslatef(6.25, 3.20, 0); //move it
	 createBell();
	 glPopMatrix();

	 //fifth bell
	 glPushMatrix();
	 glTranslatef(-0.50, 2.30, 0); //move it
	 createBell();
	 glPopMatrix();

	 createSky();

	 // grass textures
	 glPushMatrix();
	 glTranslatef(0, 0.10, -2); //move it
	 createGrass();
	 glPopMatrix();

	 glPushMatrix();
	 glTranslatef(-2, 0.10, 2);
	 createGrass();
	 glPopMatrix();

	 glPushMatrix();
	  glTranslatef(4., 0.10, 0.0); //move it
	 createGrass();
	 glPopMatrix();

	 drawAxesXYZ();

	glutSwapBuffers();
}
//************End of display function *****************

void menuEventHandler(int option) 
{

	switch (option) {
		//rotate around the x axis
		case X_AXIS : 
			currentAxis = 'x';
			if (C_increment == 0) //if the the camera is in "STOP" mode, unfreeze it
				 C_increment = prev_C_increment;
			glutPostRedisplay();
			break;

		//rotate around the y axis
		case Y_AXIS : 
			 currentAxis = 'y';
			 upx = 0; 
			 upy=1;  
			 upz=0;
			 if (C_increment == 0) //if the the camera is in "STOP" mode, unfreeze it
				 C_increment = prev_C_increment;
			 glutPostRedisplay();
			break;

		//rotate around the z axis
		case Z_AXIS : 
			 currentAxis = 'z';
			 if (C_increment == 0) //if the the camera is in "STOP" mode, unfreeze it
				 C_increment = prev_C_increment;
			 glutPostRedisplay();
			break;

		//stop rotating
		case STOP :
			prev_C_increment = C_increment;
			C_increment = 0;
			break;
	}
}
void createGlutMenu()
{
	int menu;

	menu = glutCreateMenu(menuEventHandler); //create a menu that looks to menuEventHandler to process the events

	//adds entries to the menu where the user will see the label that is in quotations
	glutAddMenuEntry("X Axis", X_AXIS);
	glutAddMenuEntry("Y Axis", Y_AXIS);
	glutAddMenuEntry("Z Axis", Z_AXIS);
	glutAddMenuEntry("Stop", STOP);

	glutAttachMenu(GLUT_RIGHT_BUTTON); //attaches the menu to the right button
}

int main(int argc, char** argv)
{

	/* Initialize mode and open a window in upper left corner of screen */

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (500, 500); 
	glutInitWindowPosition (0, 0);
	glutCreateWindow("my scene");
	glutDisplayFunc(display);
	glutIdleFunc(moveCamera);
	glutKeyboardFunc(keyboard);
	createGlutMenu();
	ptrToQuadricInfo = gluNewQuadric();
	ptrToGLUquadricInfo = gluNewQuadric();
	init();
	initCameraSetting();

	glutMainLoop();

}
