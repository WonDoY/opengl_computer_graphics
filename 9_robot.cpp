#include<iostream>
#include <cmath> // sin함수와 cos함수를 사용하기 위하여 전처리
#include <glut.h>
#include <gl\GL.h>
#include <gl\GLU.h>

using namespace std;
GLint width = 500, height = 500;
GLint cfmode=0;
GLfloat zoom = 0;
GLfloat cam=5, x=0, y=0;
static GLfloat base, lower, upper;


void draw1() {//바깥쪽그리기
	GLUquadricObj *c;

	c = gluNewQuadric();
	gluQuadricDrawStyle(c, GLU_LINE);
	glPushMatrix();
		glColor3f(1.0, 0.5, 0);
		glTranslatef(0, -1, 0);
		glRotatef(-90, 1, 0, 0);
		glRotatef(base, 0, 0, 1);
		gluCylinder(c, 0.4, 0.4, 0.3, 8, 5);
	glPopMatrix();

	glPushMatrix();
		glColor3f(0, .5, 1.0);
		glRotatef(base, 0, 1, 0);
		glTranslatef(0, -0.7, 0);
		glRotatef(lower, 0, 0, 1);
		glTranslatef(0, 0.5, 0);
		glScalef(0.2, 1, 0.2);
		glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
		glColor3f(0, 1.0, 0);
		glRotatef(base, 0, 1, 0);
		glTranslatef(0, -0.7, 0);
		glRotatef(lower, 0, 0, 1);
		glTranslatef(0, 1.0, 0);
		glRotatef(upper, 0, 0, 1);
		glTranslatef(0, 0.4, 0);
		glScalef(0.2, 0.8, 0.2);
		glutSolidCube(1);
		glPopMatrix();
}
void draw2() {//안쪽그리기
	GLUquadricObj *c;
	c = gluNewQuadric();
	gluQuadricDrawStyle(c, GLU_LINE);
	glPushMatrix();
	glColor3f(.5, 0.5, 0.5);
	glTranslatef(0, -1, 0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(base, 0, 0, 1);
	gluCylinder(c, 0.399, 0.399, 0.299, 8, 5);
	glPopMatrix();

	glPushMatrix();
	glColor3f(.5, 0.5, 0.5);
	glRotatef(base, 0, 1, 0);
	glTranslatef(0, -0.7, 0);
	glRotatef(lower, 0, 0, 1);
	glTranslatef(0, 0.5, 0);
	glScalef(0.2, 1, 0.2);
	glutSolidCube(0.99);
	glPopMatrix();

	glPushMatrix();
	glColor3f(.5, 0.5, 0.5);
	glRotatef(base, 0, 1, 0);
	glTranslatef(0, -0.7, 0);
	glRotatef(lower, 0, 0, 1);
	glTranslatef(0, 1.0, 0);
	glRotatef(upper, 0, 0, 1);
	glTranslatef(0, 0.4, 0);
	glScalef(0.2, 0.8, 0.2);
	glutSolidCube(0.99);
	glPopMatrix();
}
void drawModel() {
	glPushMatrix();
	draw1();
	draw2();
	glPopMatrix();

	glPushMatrix();
	glScalef(1.2, 1.2, 1.2);
	glTranslatef(1, 0, 0);
	draw1();
	draw2();
	glPopMatrix();

}
void MyKeyboard(unsigned char KeyPressed, int X, int Y) {
	if (KeyPressed == 'x') {
		base += 2;
	}
	else if (KeyPressed == 'z') {
		base -= 2;
	}
	else if (KeyPressed == 's') {
		if (lower <= 88)
			lower += 2;
	}
	else if (KeyPressed == 'a') {
		if (lower >= -88)
			lower -= 2;
	}
	else if (KeyPressed == 'w') {
		if (upper <= 88)
			upper += 2;
	}
	else if (KeyPressed == 'q') {
		if (upper >= -88)
			upper -= 2;
	}
	else if (KeyPressed == 'e') {//확대
		zoom++;
	}
	else if (KeyPressed == 'd') {//축소
		zoom--;
	}
	else if (KeyPressed == 'i') {//접근
		cam += 0.1;
	}
	else if (KeyPressed == 'k') {//후퇴
		cam -= 0.1;
	}
	else if (KeyPressed == 'j') {//좌측보기
		x -= 0.1;
	}
	else if (KeyPressed == 'l') {//우측보기
		x += 0.1;
	}
	else if (KeyPressed == '1') {
		cfmode = GL_FRONT; //view back
	}
	else if (KeyPressed == '2') {
		cfmode = GL_BACK; //view front
	}
	else if (KeyPressed == '3') {
		cfmode = GL_FRONT_AND_BACK; //view nothing
	}
	else if (KeyPressed == '4') {
		cfmode = 0; 
	}

	//
	//	 전면, 후면, 전후면 제거를 선택 하여 디스플레이 실험.
	//시점을 로봇암의 내부로 설정하여 내부 면이 보이도록 디스플레이.
	//	 가시부피의 전절단면이 로봇암과 교차되도록 설정하여 암의 내외부가 동시에 보이도록 디스플레이
	// 필요한 경우 솔리드 모델링 사용,   
	//

	glutPostRedisplay();
}


void MyDisplay() { //도형을 그리는 함수
	glEnable(GL_CULL_FACE);
	glCullFace(cfmode); 
	if (cfmode == 0)	glDisable(GL_CULL_FACE);


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
		glLoadIdentity();
		gluPerspective(50+zoom, 1.0, 3.0, 100.0);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
			gluLookAt(0, 0, cam, x, y, 0.0, 0.0, 1.0, 0.0); //cam has zoom function and is cutting area and x,y are coordinating camera
			drawModel();
		glPopMatrix();
		glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glutSwapBuffers();
}
void init(void) {
	glClearColor(0.8, 0.8, 0.8, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-5.0, 5.0, -5.0, 5.0, -10.0, 10.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	base = 0; upper = 0; lower = 0;
	glEnable(GL_DEPTH_TEST);
}
void MyReshape(int w, int h) {
	width = w;
	height = h;
}
int main(int argc, char** argv) {


	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("openGL");
	init();
	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);
	glutKeyboardFunc(MyKeyboard);
	//glutSpecialFunc(SpecialKey);
	glutMainLoop();
	return 0;
}