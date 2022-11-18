/***
   CTIS164 - Template Source Program
----------
STUDENT : Mert URAS
SECTION : 001
HOMEWORK: 1
----------
PROBLEMS:
----------
ADDITIONAL FEATURES:At X and Y coordinates Randomly moving 5 bird
***/

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

#define WINDOW_WIDTH  1000
#define WINDOW_HEIGHT 800

#define TIMER_PERIOD  10 // Period for the timer.
#define TIMER_ON         1// 0:disable timer, 1:enable timer

#define D2R 0.0174532

/* Global Variables for Template File */

int currentPosOfX, currentPosOfY;
int  xB = 0;
bool up = false, down = false, right = false, left = false;
int  winWidth, winHeight; // current Window width and height
bool activeTimer = true;
int Fx = 0, Fy = 0;
int randX, randY;
int Cx;

typedef struct {
	float posX, posY;
}fish_t;

fish_t fish[10];
int count = 0;

//
// to draw circle, center at (x,y)
// radius r
//


void circle(int x, int y, int r)
{
#define PI 3.1415
	float angle;
	glBegin(GL_POLYGON);
	for (int i = 0; i < 100; i++)
	{
		angle = 2 * PI * i / 100;
		glVertex2f(x + r * cos(angle), y + r * sin(angle));
	}
	glEnd();
}

void circle_wire(int x, int y, int r)
{
#define PI 3.1415
	float angle;

	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 100; i++)
	{
		angle = 2 * PI * i / 100;
		glVertex2f(x + r * cos(angle), y + r * sin(angle));
	}
	glEnd();
}

void print(int x, int y, const char* string, void* font)
{
	int len, i;

	glRasterPos2f(x, y);
	len = (int)strlen(string);
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(font, string[i]);
	}
}

// display text with variables.
// vprint(-winWidth / 2 + 10, winHeight / 2 - 20, GLUT_BITMAP_8_BY_13, "ERROR: %d", numClicks);
void vprint(int x, int y, void* font, const char* string, ...)
{
	va_list ap;
	va_start(ap, string);
	char str[1024];
	vsprintf_s(str, string, ap);
	va_end(ap);

	int len, i;
	glRasterPos2f(x, y);
	len = (int)strlen(str);
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(font, str[i]);
	}
}

// vprint2(-50, 0, 0.35, "00:%02d", timeCounter);
void vprint2(int x, int y, float size, const char* string, ...) {
	va_list ap;
	va_start(ap, string);
	char str[1024];
	vsprintf_s(str, string, ap);
	va_end(ap);
	glPushMatrix();
	glTranslatef(x, y, 0);
	glScalef(size, size, 1);

	int len, i;
	len = (int)strlen(str);
	for (i = 0; i < len; i++)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
	}
	glPopMatrix();
}

void name()
{
	glColor3f(0.1f, 0.1f, 0.1f);//Dark grey
	glRectf(-75, 375, 75, 300);
	glColor3f(7, 0, 0);
	vprint(-50, 350, GLUT_BITMAP_HELVETICA_18, "MERT URAS");
	vprint(-40, 325, GLUT_BITMAP_HELVETICA_18, "21801938");
}

void backgorund()
{
	//sea
	glColor3f(0.0f, 0.0f, 1.0f);
	glRectf(-500, -70, 500, -500);

	//sand
	glColor3f(0.8f, 0.8f, 0.2f);
	glRectf(-500, -372, 500, -500);


	//stone
	glColor3f(0.8f, 0.6f, 0.8f);
	glBegin(GL_POLYGON);
	glVertex2f(-399, -398);
	glVertex2f(-427, -364);
	glVertex2f(-357, -329);
	glVertex2f(-269, -346);
	glVertex2f(-254, -367);
	glVertex2f(-295, -396);
	glEnd();
	//stone
	glColor3f(1, 0.6f, 0.8f);
	glBegin(GL_POLYGON);
	glVertex2f(-234, -397);
	glVertex2f(-178, -400);
	glVertex2f(-220, -324);
	glVertex2f(-153, -329);
	glVertex2f(-113, -366);
	glVertex2f(-127, -395);
	glEnd();


	
	//stone
	glColor3f(1, 0.6f, 0.8f);
	glBegin(GL_POLYGON);
	glVertex2f(-534, -397);
	glVertex2f(-478, -400);
	glVertex2f(-520, -324);
	glVertex2f(-453, -329);
	glVertex2f(-413, -366);
	glVertex2f(-427, -395);
	glEnd();

	//cloud
	glColor3f(1, 1, 1);
	circle(-417, 325, 50);

	glColor3f(1, 1, 1);
	circle(-334, 325, 50);

	glColor3f(1, 1, 1);
	circle(-381, 317, 50);

	glColor3f(1, 1, 1);
	circle(-89, 191, 50);

	glColor3f(1, 1, 1);
	circle(-34, 204, 50);

	glColor3f(1, 1, 1);
	circle(16, 186, 50);

	//sun
	glColor3f(1, 1, 0.2);
	circle(470, 360, 80);

	
}
void iskele()
{
	//iskele
	glColor3f(1.0f, 0.5f, 0.0f);
	glRectf(-500, -18, -210, -68);
	glColor3f(1.0f, 0.5f, 0.0f);
	glBegin(GL_TRIANGLES);
	glVertex2f(-368, -69);
	glVertex2f(-500, -210);
	glVertex2f(-500, -69);
	glEnd();
}
void sea(int Fx, int Fy)
{


	glColor3f(1.0f, 1.0f, 0.0f);
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 0.0f); //üst yüzgeç
	glVertex2f(Cx + Fx - 40, Fy - 100);
	glVertex2f(Cx + Fx - 40, Fy - 100);
	glVertex2f(Cx + Fx - 35, Fy - 80);
	glVertex2f(Cx + Fx - 80, Fy - 80);
	glVertex2f(Cx + Fx - 75, Fy - 100);
	glEnd();

	//lines1
	glColor3ub(255, 0, 0);
	glBegin(GL_LINES);
	for (int i = -80; i <= -100; i = i + 5)
	{
		glColor3f(0, 0, 0);
		glVertex2f(Cx + Fx + i, Fy - 76);
		glVertex2f(Cx + Fx + i, Fy - 79);
	}
	glEnd();


	//balýk
	glColor3f(1.0f, 0.5f, 0.0f);
	circle(Cx + Fx - 50, Fy - 120, 35);
	glColor3f(0.5, 0.0, 0.0);
	//kuyruk
	glColor3f(1.0f, 0.5f, 0.0f);
	glBegin(GL_TRIANGLES);
	glVertex2f(Cx + Fx - 86, Fy - 120);
	glVertex2f(Cx + Fx - 114, Fy - 103);
	glVertex2f(Cx + Fx - 114, Fy - 139);
	glEnd();
	glColor3ub(255, 0, 0);
	glBegin(GL_LINES);
	// line 2
	for (int i = -135; i <= -110; i = i + 5)
	{
		glColor3f(0, 0, 0);
		glVertex2f(Cx + Fx - 98, Fy + i);
		glVertex2f(Cx + Fx - 114, Fy + i);
	}
	glEnd();
	 //DUDAK
	glColor3f(1.0f, 1.0f, 0.0f);
	glRectf(Cx + Fx - 21, Fy - 118, Cx + Fx - 8, Fy - 124);
	glColor3f(1.0f, 1.0f, 0.0f);
	glRectf(Cx + Fx - 20, Fy - 123, Cx + Fx - 13, Fy - 130);

	glColor3f(1.0f, 0.5f, 0.0f);
	circle(Cx + Fx - 25, Fy - 105, 15);
	glColor3f(0.5, 0.0, 0.0);

	glColor3f(0, 0, 0);
	circle(Cx + Fx - 12, Fy - 103, 5);
	glColor3f(0.5, 0.0, 0.0);
	//DUDAK
	glColor3f(1.0f, 1.0f, 0.0f); //yüzgeç
	glBegin(GL_POLYGON);
	glVertex2f(Cx + Fx - 50, Fy - 130);
	glVertex2f(Cx + Fx - 67, Fy - 135);
	glVertex2f(Cx + Fx - 75, Fy - 126);
	glVertex2f(Cx + Fx - 67, Fy - 115);

	glEnd();


}

void birds()
{


	srand(time(NULL));

	for (int i = 1; i <= 5; i++)
	{

		randY = (rand() % (400-70)) + 150;
		randX = (rand() % (400)) + -150;


		glBegin(GL_POLYGON);
		glColor3f(1, 0.8, 0.3); //wing
		glVertex2f(randX + xB - 40, randY + -100);
		glVertex2f(randX + xB - 35, randY + -80);
		glVertex2f(randX + xB - 80, randY + -80);
		glVertex2f(randX + xB - 75, randY + -100);
		glEnd();
		glColor3ub(255, 0, 0);
		glBegin(GL_LINES);
		// line 1
		for (int i = -80; i <= -35; i = i + 5)
		{
			glColor3f(0, 0, 0);
			glVertex2f(randX + xB + i, randY + -80);
			glVertex2f(randX + xB + i, randY + -100);
		}
		glEnd();

		glColor3f(1, 1, 1);
		circle(randX + xB - 50, randY + -120, 35);
		glBegin(GL_TRIANGLES);
		glVertex2f(randX + xB - 75, randY + -120);
		glVertex2f(randX + xB - 110, randY + -105);
		glVertex2f(randX + xB - 110, randY + -140);
		glEnd();
		glColor3ub(255, 0, 0);
		glBegin(GL_LINES);
		// line 2
		for (int i = -135; i <= -110; i = i + 5)
		{
			glColor3f(0, 0, 0);
			glVertex2f(randX + xB - 95, randY + i);
			glVertex2f(randX + xB - 110, randY + i);
		}
		glEnd();

		glColor3f(0, 0, 0);//eye
		circle(randX + xB - 35, randY + -105, 5);

		glColor3f(0, 0, 0);//mouth
		glBegin(GL_POLYGON);
		glColor3f(1, 0.8, 0.3); //yüzgeç
		glVertex2f(randX + xB - 20, randY + -120);
		glVertex2f(randX + xB - 27, randY + -135);
		glVertex2f(randX + xB - 10, randY + -130);

		glEnd();


		glBegin(GL_POLYGON);
		glColor3f(1, 0.8, 0.3); //yüzgeç
		glVertex2f(randX + xB - 50, randY + -120);
		glVertex2f(randX + xB - 50, randY + -130);
		glVertex2f(randX + xB - 67, randY + -135);
		glVertex2f(randX + xB - 75, randY + -126);
		glVertex2f(randX + xB - 67, randY + -115);
		glEnd();
		glColor3ub(255, 0, 0);
		glBegin(GL_LINES);
	}

	glEnd();
}
//
// To display onto window using OpenGL commands
//
void display() {
	//
	// clear window to black
	//
	glClearColor(0.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	backgorund();
	for (int i = 0; i < count; i++)
	{
		sea(fish[i].posX, fish[i].posY);
	}
	birds();

	vprint(-396,- 375, GLUT_BITMAP_8_BY_13, "(%d,%d)", currentPosOfX, currentPosOfY);
	name();
	iskele();
	glutSwapBuffers();
}

//
// key function for ASCII charachters like ESC, a,b,c..,A,B,..Z
//
void onKeyDown(unsigned char key, int x, int y)
{
	// exit when ESC is pressed.
	if (key == 27)
		exit(0);

	// to refresh the window it calls display() function
	glutPostRedisplay();
}

void onKeyUp(unsigned char key, int x, int y)
{
	// exit when ESC is pressed.
	if (key == 27)
		exit(0);

	// to refresh the window it calls display() function
	glutPostRedisplay();
}

//
// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//
void onSpecialKeyDown(int key, int x, int y)
{
	// Write your codes here.
	switch (key) {
	case GLUT_KEY_UP: up = true; break;
	case GLUT_KEY_DOWN: down = true; break;
	case GLUT_KEY_LEFT: left = true; break;
	case GLUT_KEY_RIGHT: right = true; break;
	}

	if (key == GLUT_KEY_F1)
	{
		activeTimer = !activeTimer;;
	}

	// to refresh the window it calls display() function
	glutPostRedisplay();
}

//
// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//
void onSpecialKeyUp(int key, int x, int y)
{
	// Write your codes here.
	switch (key) {
	case GLUT_KEY_UP: up = false; break;
	case GLUT_KEY_DOWN: down = false; break;
	case GLUT_KEY_LEFT: left = false; break;
	case GLUT_KEY_RIGHT: right = false; break;
	}

	// to refresh the window it calls display() function
	glutPostRedisplay();
}

//
// When a click occurs in the window,
// It provides which button
// buttons : GLUT_LEFT_BUTTON , GLUT_RIGHT_BUTTON
// states  : GLUT_UP , GLUT_DOWN
// x, y is the coordinate of the point that mouse clicked.
//
void onClick(int button, int stat, int x, int y)
{
	// Write your codes here.

	switch (button)
	{
	case GLUT_RIGHT_BUTTON:
		if (stat == GLUT_DOWN && currentPosOfY<-70)
		{
			if (count < 10) {
				count++;
				fish[count - 1].posX = currentPosOfX - Cx + 50;
				fish[count - 1].posY = currentPosOfY + 100;
			}
		}
		break;
	}

	/*	if (button == GLUT_RIGHT_BUTTON && stat == GLUT_DOWN) {
			//map from GLUT coordinate system to OpenGL Coordinate System
				Fx = x - winWidth / 2 + 50;
				Fy = winHeight / 2 - y + 100;
		}
		*/

		// to refresh the window it calls display() function
	glutPostRedisplay();
}

//
// This function is called when the window size changes.
// w : is the new width of the window in pixels.
// h : is the new height of the window in pixels.
//
void onResize(int w, int h)
{
	winWidth = w;
	winHeight = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-w / 2, w / 2, -h / 2, h / 2, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	display(); // refresh window.
}

void onMoveDown(int x, int y) {
	// Write your codes here.



	// to refresh the window it calls display() function   
	glutPostRedisplay();
}

// GLUT to OpenGL coordinate conversion:
//   x2 = x1 - winWidth / 2
//   y2 = winHeight / 2 - y1
void onMove(int x, int y) {
	// Write your codes here.

	currentPosOfX = x - winWidth / 2;
	currentPosOfY = winHeight / 2 - y;


	// to refresh the window it calls display() function
	glutPostRedisplay();
}

#if TIMER_ON == 1
void onTimer(int v) {

	glutTimerFunc(TIMER_PERIOD, onTimer, 0);
	// Write your codes here.

	if (activeTimer)
	{

		if (Cx < 500 )
		{

			Cx++;
			
		}

		else
		{
			Cx = -525;
		
		}
	}

	if ( xB < 500)
	{

		
		xB++;
	}

	else
	{
		
		xB = -525;
	}
	// to refresh the window it calls display() function
	glutPostRedisplay(); // display()

}
#endif

void Init() {

	// Smoothing shapes
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	//glutInitWindowPosition(100, 100);
	glutCreateWindow("21801938-Ocean");

	glutDisplayFunc(display);
	glutReshapeFunc(onResize);

	//
	// keyboard registration
	//
	glutKeyboardFunc(onKeyDown);
	glutSpecialFunc(onSpecialKeyDown);

	glutKeyboardUpFunc(onKeyUp);
	glutSpecialUpFunc(onSpecialKeyUp);

	//
	// mouse registration
	//
	glutMouseFunc(onClick);
	glutMotionFunc(onMoveDown);
	glutPassiveMotionFunc(onMove);

#if  TIMER_ON == 1
	// timer event
	glutTimerFunc(TIMER_PERIOD, onTimer, 0);
#endif

	Init();

	glutMainLoop();
}