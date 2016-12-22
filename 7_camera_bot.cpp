/*항공대학교 소프트웨어학과 
* 2011122355 원도연
* 카메라 로봇 source code
*/
#include<cstdio>
#include<cmath>
#include<glut.h>
#include<GL.H>
#include<GLU.H>


GLUquadricObj *c;
GLfloat base, lower, upper;
GLfloat botx,boty,botz;
GLfloat atx,aty,atz;
GLfloat upx,upy,upz;
GLfloat vecx, vecy, vecz;

int leftTempX, leftTempY;
bool Button_left_push = false;
bool key[256];

void drawBase();
void drawLower();
void drawUpper();
void drawCameraBot();
void drawBackGround();
void drawFigure();

void display_1();
void display_2();
void display_3();
void fullDisplay();
void doDisplay();

void doKeyboard(unsigned char keyPressed, int x, int y);
void doReleaseKey(unsigned char keyReleased, int x, int y);

void doSpecialKey(int keyPressed, int x, int y);
void doSpecialReleaseKey(int keyReleased, int x, int y);

void doMouse(int Button ,int State, int X, int Y);
void doMotion(int X, int Y);

void drawInit();

void keyMotion();
void doTimer(int v);

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500,750);
	glutInitWindowPosition(500,0);
	glutCreateWindow("2011122355_camera_bot");

	glMatrixMode(GL_PROJECTION); glLoadIdentity();

	drawInit();
	
	glutDisplayFunc(doDisplay);
	glutKeyboardFunc(doKeyboard);
	glutKeyboardUpFunc(doReleaseKey); // 키보드 동시입력을 위한 콜백함수
	glutSpecialFunc(doSpecialKey);
	glutSpecialUpFunc(doSpecialReleaseKey); // 키보드 동시입력을 위한 콜백함수

	glutTimerFunc(20,doTimer,1);
	
	glutMouseFunc(doMouse);
	glutMotionFunc(doMotion);
	
	glutMainLoop();

	return 0;
} 

/* void drawBase();
 *	로봇암의 Base를 그리는 Function
 */
void drawBase(){
	glColor3f(1,0,0); // Color Red
	glTranslatef(0, -1, 0);
	glRotatef(-90, 1, 0 ,0);
	glRotatef(base, 0, 0, 1);
	gluCylinder(c, 0.4, 0.2, 0.3, 8, 8);
} 

/* void drawLower();
 *	로봇암의 LowerArm 을 그리는 Function
 */
void drawLower(){
	glColor3f(0, 0, 1); // Color Blue
	glRotatef(base, 0, 1, 0);

	glTranslatef(0, -0.7, 0);
	glRotatef(lower, 0, 0, 1);
	glTranslatef(0, 0.5, 0);

	glScalef(0.2, 1, 0.2);
	
	glutSolidCube(1);
}

/* void drawUpper();
 *	로봇암의 UpperArm 을 그리는 Function
 */
void drawUpper(){
	glColor3f(0, 1, 0); // Color Green
	glRotatef(base, 0, 1, 0);
	
	glTranslatef(0, -0.7, 0);
	glRotatef(lower, 0, 0, 1);
	glTranslatef(0, 1.0, 0);
	glRotatef(upper, 0, 0, 1);
	glTranslatef(0, 0.4, 0);
	
	glScalef(0.2, 0.8, 0.2);

	glutWireCube(1);
	//glutSolidCube(1);
} 

/* void drawCameraBot();
 * 카메라 로봇을 그리는 Function
 */
void drawCameraBot(){
	glColor3f(1,1,0);
	glBegin(GL_POLYGON);
		glVertex3f(botx - 3*vecx, aty, botz - 3*vecz);
		glVertex3f(botx - vecz , boty, botz + vecx);
		glVertex3f(botx + vecz , boty, botz - vecx);
	glEnd();
}

/* void drawBackGround();
 * 배경을 그리는 Function
 */
void drawBackGround(){
	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_POLYGON);
		glVertex3f(10,-1,10);		
		glVertex3f(-10,-1,10);
		glVertex3f(-10,-1,-10);
		glVertex3f(10,-1,-10);			
	glEnd();

	glColor3f(1,0,0);
	glBegin(GL_LINE_LOOP);
		glVertex3f(10,-1,0);
		glVertex3f(-10,-1,0);		
	glEnd();

	glColor3f(0,0,1); // Blue
	glBegin(GL_LINE_LOOP);
		glVertex3f(0,-1,10);
		glVertex3f(0,-1,-10);		
	glEnd();
}

/*
 * 모든 그리는 Function 을 합쳐놓음
 * BackGround();
 * drawBase();
 * drawLower();
 * drawUpper();
 * drawCameraBot();
 */
void drawFigure(){
	glPushMatrix(); drawBackGround(); glPopMatrix();
	glPushMatrix(); drawBase(); glPopMatrix();
	glPushMatrix(); drawLower(); glPopMatrix();
	glPushMatrix(); drawUpper(); glPopMatrix();
	glPushMatrix(); drawCameraBot(); glPopMatrix();
}


/* void display_1();
* 화면1 Function ; dis_1()
* *-------------*
* |				|
* |				|
* |dis_1		|
* |				|
* |-------------|
* |dis_2 | dis_3|
* *-------------* 500x750
*/
void display_1(){
	glViewport(0, 250, 500, 500); // 좌하단 + 우상단
	// viewport 설정
	// MODELVIEW, 카메라설정
	// PROJECTION, 원근감 || 평면 결정
	// MODELVIEW, 그리기
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(botx, boty, botz,
		atx, aty, atz,
		upx, upy, upz); // 위를 바라보고 싶을 때는 atX, atY, atZ를 수정해야 하는데..

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40,1,1,20); // 원근감 설정

	glMatrixMode(GL_MODELVIEW);
	
	drawFigure();
}
/* void display_2();
* 화면 2 Function dis_2()
*/
void display_2(){
	glViewport(0, 0, 250, 250);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0, 3, 0, 
		0, 0, 0,
		0, 0, 1);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-5, 5, -5, 5, -10, 10); // 평면

	glMatrixMode(GL_MODELVIEW);

	drawFigure();
}
// 화면 3 Function
void display_3(){
	glViewport(250, 0 , 250, 250);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(10,10,10,
		0,0,0,
		0,1,0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30,1,1,100); // 원근감

	glMatrixMode(GL_MODELVIEW);

	drawFigure();

} 
/* void fullDisplay();
* 전체 display func
* *-------------*
* |				|
* |				|
* |dis_1		|
* |				|
* |-------------|
* |dis_2 | dis_3|
* *-------------* 500x750
*/
void fullDisplay(){
	display_1();
	display_2();
	display_3();
}
/* void doDisplay();
* Display callback func
*/
void doDisplay(){	
	glClear(GL_COLOR_BUFFER_BIT);
	
	fullDisplay();
	
	glutSwapBuffers();
} 

/* void doKeyboard(unsigned char, int , int);
* keyboard callback func
* 일반적인 키보드 콜백함수
*/

void doKeyboard(unsigned char keyPressed, int x, int y){
	unsigned char *kp = &keyPressed;
	switch(*kp){
	case 'q': case 'Q': exit(0); break;
	case 'w': case 'W': key['W'] = true; break; // 현재 보고 있는 BOT 과 AT 에 대해서 값을 바꿔야한다.
	case 's': case 'S': key['S'] = true; break; // 
	case 'a': case 'A': key['A'] = true; break;
	case 'd': case 'D': key['D'] = true; break;

	}	
}
void doReleaseKey(unsigned char keyReleased, int x, int y){
	unsigned char *kp = &keyReleased;

	switch(*kp){	
	case 'w': case 'W': key['W'] = false; break; // 현재 보고 있는 BOT 과 AT 에 대해서 값을 바꿔야한다.
	case 's': case 'S': key['S'] = false; break; // 
	case 'a': case 'A': key['A'] = false; break;
	case 'd': case 'D': key['D'] = false; break;
	}
}
/* void doSpecialKey(int , int , int);
* Special keyboard callback func
* 특수 키 콜백함수
*/
void doSpecialKey(int keyPressed, int x, int y){
	int *kp = &keyPressed;
	switch(*kp){
	case GLUT_KEY_UP: key[GLUT_KEY_UP] = true; break;
	case GLUT_KEY_DOWN: key[GLUT_KEY_DOWN] = true; break;
	case GLUT_KEY_LEFT: key[GLUT_KEY_LEFT] = true; break;
	case GLUT_KEY_RIGHT: key[GLUT_KEY_RIGHT] = true; break;
	}
}
void doSpecialReleaseKey(int keyReleased, int x, int y){
	int* kr = &keyReleased;
	switch(*kr){
	case GLUT_KEY_UP: key[GLUT_KEY_UP] = false; break;
	case GLUT_KEY_DOWN: key[GLUT_KEY_DOWN] = false; break;
	case GLUT_KEY_LEFT: key[GLUT_KEY_LEFT] = false; break;
	case GLUT_KEY_RIGHT: key[GLUT_KEY_RIGHT] = false; break;
	}
}


/* void doMouse(int, int, int, int);
* 시점 이동을 하기 위한 마우스 Function 왼쪽버튼을 누른 상태에서
* 해당 좌표를 저장하고 doMotion으로 시점이동을 한다.
*/
void doMouse(int Button ,int State, int X, int Y){
	(Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN) ? leftTempX = X, leftTempY = Y, Button_left_push = true : printf("leftButton false");	
	(Button == GLUT_LEFT_BUTTON && State == GLUT_UP) ?  Button_left_push = false : false ;
}

/* void doMotion(int, int);
* 마우스 시점이동을 담당한다.
*/
void doMotion(int X, int Y){
	GLfloat tmp = atx;
	GLfloat angle;	
	
	if(Button_left_push){
		if(leftTempY > Y){ (aty < 5)?aty+=0.05:false; }
		else if(leftTempY < Y){ (aty > -1.2)?aty-=0.05:false; }
		leftTempY = Y;

		if(leftTempX > X){
			angle = -0.02;		
			atx =  (atx-botx) * cos(angle) - (atz-botz) * sin(angle) ;
			atz =  (tmp-botx) * sin(angle) + (atz-botz) * cos(angle) ;
			atx += botx;
			atz += botz;	
		}else if(leftTempX < X){
			angle = +0.02;
			atx =  (atx-botx) * cos(angle) - (atz-botz) * sin(angle);
			atz =  (tmp-botx) * sin(angle) + (atz-botz) * cos(angle);
			atx += botx;
			atz += botz;	
		}
		leftTempX = X;
	}
}

/* void drawInit();
*그리기 위한 변수를 처음 메인 함수를 호출할 때 초기화해주기 위한 Function
*/
void drawInit(){
	c = gluNewQuadric();
	gluQuadricDrawStyle(c, GLU_LINE);

	base = lower = upper = 0;
	botx = 3; 	botz = 3;	boty = -0.5;
	atx = aty = atz = 0;
	upx = upz = 0;	upy = 1;
	vecx = (botx - atx)/20; vecz = (botz - atz)/20;	vecy = 0;

	for(int i = 0 ; i < 256 ; i++)	key[i] = false;

	glClearColor(1,1,1,1);	
} 


// 키 움직임 감지
void keyMotion(){
	GLfloat tmp = atx;
	GLfloat angle;
	if(key['W']){	
		botx-=vecx/5; botz-=vecz/5;
		atx-=vecx/5; atz-=vecz/5; 
	}
	if(key['S']){	
		botx+=vecx/5; botz+=vecz/5;
		atx+=vecx/5; atz+=vecz/5;
	}
	if(key['A']){	
		botx -= vecz/5; botz += vecx/5; 
		atx -= vecz/5; atz += vecx/5;
	}
	if(key['D']){	
		botx +=vecz/5; botz -= vecx/5; 
		atx +=vecz/5; atz -= vecx/5;
	}
	if(key[GLUT_KEY_UP]){
		(aty < 5)?aty+=0.1:false; 
	}
	if(key[GLUT_KEY_DOWN]){
		(aty > -1.2)?aty-=0.1:false;
	}
	if(key[GLUT_KEY_LEFT]){
		angle = -0.02;		
			
		atx =  (atx-botx) * cos(angle) - (atz-botz) * sin(angle) ;
		atz =  (tmp-botx) * sin(angle) + (atz-botz) * cos(angle) ;
		atx += botx;
		atz += botz;	
	}
	if(key[GLUT_KEY_RIGHT]){
		
		angle = +0.02;
				
		atx =  (atx-botx) * cos(angle) - (atz-botz) * sin(angle);
		atz =  (tmp-botx) * sin(angle) + (atz-botz) * cos(angle);
		atx += botx;
		atz += botz;	
	}
}

// 움직임을 부드럽게 하기위해서 doTimer
void doTimer(int v){
	keyMotion();
	vecx = (botx - atx)/20; vecz = (botz - atz)/20;
	glutPostRedisplay();
	glutTimerFunc(20, doTimer, 1);
}