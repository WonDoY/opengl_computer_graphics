#include<iostream>
#include <cmath> // sin함수와 cos함수를 사용하기 위하여 전처리
#include<stdio.h>
#include<glut.h>
#define ANGLE_ARM 80
GLUquadricObj *c;

GLfloat base, lower, upper;
int intBase, intLower, intUpper;

void Base() {
	glColor3f(1.0, 0, 0);
	glTranslatef(0, -1, 0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(base, 0, 0, 1);
	gluCylinder(c, 0.4, 0.2, 0.3, 8, 8);
	
}
void lower_arm() {
	glColor3f(0, 0, 1.0);
	glRotatef(base, 0, 1, 0);

	glTranslatef(0, -0.7, 0);
	glRotatef(lower, 0, 0, 1);
	glTranslatef(0, 0.5, 0);

	glScalef(0.2, 1, 0.2);
	
	glutSolidCube(1);
}
void upper_arm() {
	glColor3f(0, 1.0, 0);
	glRotatef(base, 0, 1, 0);

	glTranslatef(0, -0.7, 0);
	glRotatef(lower, 0, 0, 1);
	glTranslatef(0, 1.0, 0);
	glRotatef(upper, 0, 0, 1);
	glTranslatef(0, 0.4, 0);

	glScalef(0.2, 0.8, 0.2);

	glutSolidCube(1);
}

void doDisplay() { //도형을 그리는 함수

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLoadIdentity();
	gluLookAt(0.1, 0.1, 0.1, 0, 0.0, 0, 0.0, 1.0, 0.0);

	glPushMatrix();
		Base();
	glPopMatrix();

	glPushMatrix();
		lower_arm();
	glPopMatrix();

	glPushMatrix();
		upper_arm();
	glPopMatrix();

	glutSwapBuffers();
}

void doKeyboard(unsigned char KeyPressed, int X, int Y) {
	switch(KeyPressed){
	case 'q' : case 'Q':
				   exit(0); break;
	case 'a': case 'A': (upper >= -ANGLE_ARM) ? upper-- : false ; break;
	case 's': case 'S':(upper <= ANGLE_ARM) ? upper++ : false; break;
	case 'z': case 'Z':(lower >= -ANGLE_ARM) ? lower-- : false; break;
	case 'x': case 'X':(lower <= ANGLE_ARM) ? lower++ : false; break;
	case 'c':case 'C': intBase--; break;		
	case 'v':case 'V': intBase++; break;
	}
	glutPostRedisplay();
}


int leftTempX, leftTempY;
int rightTempX, rightTempY;
int middleTempX, middleTempY;
bool Button_left_push = false;
bool Button_right_push = false;
bool Button_middle_push = false;
void doMouse(int Button ,int State, int X, int Y){
	switch(Button){
	case GLUT_LEFT_BUTTON:
		printf("LEFTBUTTON\n");break;
	case GLUT_RIGHT_BUTTON:
		printf("RIGHTBUTTON\n");break;
	}
	(Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN) ? leftTempX = X, leftTempY = Y, Button_left_push = true : printf("leftButton false");
	(Button == GLUT_RIGHT_BUTTON && State == GLUT_DOWN) ? rightTempX = X, rightTempY = Y, Button_right_push = true : printf("rightBN false");
	(Button == GLUT_MIDDLE_BUTTON && State == GLUT_DOWN) ? middleTempX = X, middleTempY = Y, Button_middle_push = true : printf("centerBN false");

	(Button == GLUT_LEFT_BUTTON && State == GLUT_UP) ?  Button_left_push = false : false ;
	(Button == GLUT_RIGHT_BUTTON && State == GLUT_UP) ?  Button_right_push = false : false ;
	(Button == GLUT_MIDDLE_BUTTON && State == GLUT_UP) ?  Button_middle_push = false : false ;
	
}

void doMotion(int X, int Y){

	if(Button_left_push){
		(base >= 0 && base <=136 || base >= 320) ?
		(leftTempX>X) ? ((lower<=ANGLE_ARM) ? lower++ : false) : ((lower>=-ANGLE_ARM) ? lower-- : false)
		:
		(leftTempX>X) ? ((lower>=-ANGLE_ARM) ? lower-- : false) : ((lower<=ANGLE_ARM) ? lower++ : false);

		printf("%d %d >> %d %d lower : %f\n",leftTempX, leftTempY, X, Y, lower);
		leftTempX = X; leftTempY = Y;
	}
	if(Button_right_push){
		(rightTempX>X) ? intBase++ :  intBase--;
		(intBase <= 0) ? intBase+=360 : false ;
		base = intBase%360;
		printf("%d %d >> %d %d base : %f\n",rightTempX, rightTempY, X, Y, base);
		rightTempX = X; rightTempY = Y;	
	}
	if(Button_middle_push){
		/*if(base > 45){*/
		(base >= 0 && base <=136 || base >= 320) ?
		(middleTempX > X)? ((upper<=ANGLE_ARM)? upper++ : false) : ((upper>=-ANGLE_ARM) ? upper-- : false) 
		:
		(middleTempX > X)? ((upper>=-ANGLE_ARM)? upper-- : false) : ((upper<=ANGLE_ARM) ? upper++ : false) ; 
		
		middleTempX = X; middleTempY = Y;
	}
	glutPostRedisplay();
}


void init(void) {
	c = gluNewQuadric();
	gluQuadricDrawStyle(c, GLU_LINE);

	intUpper = intLower = upper = lower = 0;
	intBase = base = 45;

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
}


int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(1000, 200);
	glutCreateWindow("OpenGL Drawing Example");
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
	glutDisplayFunc(doDisplay);
	glutKeyboardFunc(doKeyboard);
	glutMouseFunc(doMouse);
	glutMotionFunc(doMotion);
	init();
	glutMainLoop();

	return 0;

}