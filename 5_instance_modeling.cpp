#include<cstdio>
#include<cmath>
#include<glut.h>
#include<GL.H>
#include<GLU.H>

#define WHITE        0
#define RED          1
#define GREEN        2
#define BLUE         3
#define YELLOW		 4
#define BLACK        5

#define MAX 200


#define KEY_ESC 27
#define KEY_SPACE 32
#define KEY_BACKSPACE 8

GLfloat botx[MAX],boty[MAX],botz[MAX];
GLfloat atx[MAX],aty[MAX],atz[MAX];
GLfloat upx[MAX],upy[MAX],upz[MAX];
GLfloat vecx, vecy, vecz;
int count;
GLfloat MyVertices[20][3] = {

	{ -0.5, 0, -0.5 },
	{ -0.5, 0, 0.5 },
	{ -0.5, 1, 0.5 },
	{ -0.5, 1.5, 0 },
	{ -0.5, 1, -0.5 },
	{ 0.5, 0, -0.5 },
	{ 0.5, 0, 0.5 },
	{ 0.5, 1, 0.5 },
	{ 0.5, 1.5, 0 },
	{ 0.5, 1, -0.5 },

	//10~13 땅을 표현하기 위한 좌표
	{ 2000, 0, 2000 },
	{ -2000, 0, 2000 },
	{ -2000, 0, -2000 },
	{ 2000, 0, -2000 },

	//좌표축을 표시하기 위한 좌표
	{ 2000, 0, 0 },
	{ -2000, 0, 0 },//x
	{ 0, 2000, 0 },
	{ 0, -2000, 0 },//y
	{ 0, 0, 2000 },
	{ 0, 0, -2000 },
};

GLubyte MyVertexList[40] = {
	4, 9, 5, 0,
	8, 9, 4, 3,
	7, 8, 3, 2,
	6, 7, 2, 1,
	5, 6, 1, 0,
	9, 8, 7, 6, 5,
	1, 2, 3, 4, 0,
	13, 12, 11, 10,
	14, 15,
	16, 17,
	18, 19
};



void createInstance(GLint Color, GLdouble x, GLdouble y, GLdouble z){
	glTranslatef(x, y, z);

	switch (Color)	{
	case WHITE: glColor3f(0.0, 0.0, 0.0); break;
	case RED:   glColor3f(1.0, 0.0, 0.0); break;
	case GREEN: glColor3f(0.0, 1.0, 0.0); break;
	case BLUE:  glColor3f(0.0, 0.0, 1.0); break;
	case YELLOW:glColor3f(1.0, 1.0, 0.0); break;
	case BLACK: glColor3f(1.0, 1.0, 1.0); break;
	}
	for (GLint i = 0; i < 5; i++){
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &MyVertexList[4 * i]);
	}
	glDrawElements(GL_POLYGON, 5, GL_UNSIGNED_BYTE, &MyVertexList[20]);
	glDrawElements(GL_POLYGON, 5, GL_UNSIGNED_BYTE, &MyVertexList[25]);
} // instance modeling func

void instanceModeling(int Color, GLfloat x, GLfloat y, GLfloat z){
	glPushMatrix();
	createInstance(Color, x, y, z);
	glPopMatrix();
}
void drawFigure(){
		glColor3f(0.5, 0.5, 0.5);
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, MyVertices);	

		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &MyVertexList[30]);

		glColor3f(1.0, 0.0, 0.0);
		glDrawElements(GL_LINES, 2, GL_UNSIGNED_BYTE, &MyVertexList[34]);
		glDrawElements(GL_LINES, 2, GL_UNSIGNED_BYTE, &MyVertexList[36]);
		glDrawElements(GL_LINES, 2, GL_UNSIGNED_BYTE, &MyVertexList[38]);
		
		instanceModeling(0, 2, 0, 2);
		instanceModeling(1, -2, 0, 2);
		instanceModeling(2, 2, 0, -2);
		instanceModeling(3, -2, 0, -2);
		instanceModeling(4, 3, 0, 1);
		instanceModeling(5, 3, 0, 3);
}

void doDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	gluLookAt(botx[count], boty[count], botz[count],
		atx[count], aty[count], atz[count],
		upx[count], upy[count], upz[count]);		

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, 1, 1, 60.0);

	glMatrixMode(GL_MODELVIEW);
	drawFigure();	

	glutSwapBuffers();
}



void doTimer(int Value)
{
	vecx = (botx - atx)/20; vecz = (botz - atz)/20;
	glutPostRedisplay();
	glutTimerFunc(40, doTimer, 1);
}
void drawInit(){
	count = 0;

	botx[count] = 10;
	botz[count] = 4;	
	boty[count] = 1;

	atx[count] = 0; 
	aty[count] = 0;
	atz[count] = 0;

	upx[count] = 0;
	upy[count] = 1;
	upz[count] = 0;	

	vecx = (botx[count] - atx[count])/20;
	vecy = 0;
	vecz = (botz[count] - atz[count])/20;	

	

	glEnable(GL_DEPTH_TEST);
}
void doKeyboard(unsigned char kp, int X, int Y) {
	GLfloat tmp = atx[count];
	GLfloat angle;
	vecx = (botx[count] - atx[count])/20;
	vecy = 0;
	vecz = (botz[count] - atz[count])/20;	
	switch (kp){
	case 'Q':   case 'q': // key : 종료
		exit(0); break;
	case '<': case ',':   // < : 시점이동좌
		angle = -0.02;		

		atx[count] =  (atx[count]-botx[count]) * cos(angle) - (atz[count]-botz[count]) * sin(angle) ;
		atz[count] =  (tmp-botx[count]) * sin(angle) + (atz[count]-botz[count]) * cos(angle) ;
		atx[count] += botx[count];
		atz[count] += botz[count];
		break;
	case '>': case '.': // > : 시점이동 우
		angle = +0.02;

		atx[count] =  (atx[count]-botx[count]) * cos(angle) - (atz[count]-botz[count]) * sin(angle);
		atz[count] =  (tmp-botx[count]) * sin(angle) + (atz[count]-botz[count]) * cos(angle);
		atx[count] += botx[count];
		atz[count] += botz[count];
		break;
	case 'w': case 'W': botx[count]-=vecx/5; botz[count]-=vecz/5;	atx[count]-=vecx/5; atz[count]-=vecz/5;  break;
	case 's': case 'S': botx[count]+=vecx/5; botz[count]+=vecz/5;	atx[count]+=vecx/5; atz[count]+=vecz/5;  break;
	case 'a': case 'A': botx[count]-=vecz/5; botz[count]+=vecx/5;   atx[count]-=vecz/5; atz[count]+=vecx/5; break;
	case 'd': case 'D': botx[count]+=vecz/5; botz[count]-=vecx/5; 	atx[count]+=vecz/5; atz[count]-=vecx/5; break;
	case KEY_ESC:   // view init
		drawInit();
		break;
	case KEY_BACKSPACE:  // view pop
		if(count > 0) count--;
		vecx = (botx[count] - atx[count])/20;
		vecy = 0;
		vecz = (botz[count] - atz[count])/20;
		break;
	case KEY_SPACE:   // view stack
		if(count < MAX) count++;
		botx[count] = botx[count - 1];
		boty[count] = boty[count - 1];
		botz[count] = botz[count - 1];

		atx[count] = atx[count - 1];
		aty[count] = aty[count - 1];
		atz[count] = atz[count - 1];

		upx[count] = upx[count - 1];
		upy[count] = upy[count - 1];
		upz[count] = upz[count - 1];
		break;
	}
	glutPostRedisplay();
}



int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(400, 400);
	glutCreateWindow("2011122355_instance_modeling");
	glClearColor(0.70, 0.91, 1, 0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	drawInit();

	glutDisplayFunc(doDisplay);
	glutKeyboardFunc(doKeyboard);
	glutTimerFunc(40, doTimer, 1);
	glutMainLoop();
	return 0;
}