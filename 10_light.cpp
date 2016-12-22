/*항공대학교 소프트웨어학과 
* 2011122355 원도연
* 카메라 로봇 source code
*/
#include<cstdio>
#include<cmath>
#include<glut.h>
#include<GL.H>
#include<GLU.H>
#define ANGLE_ARM 88

//typedef GLfloat GFL;

GLUquadricObj *c;
GLfloat base, lower, upper;
GLfloat _base, _lower, _upper;
GLfloat botx,boty,botz;
GLfloat atx,aty,atz;
GLfloat upx,upy,upz;
GLfloat vecx, vecy, vecz;

int CULLMODE = 0;
int leftTempX, leftTempY;
bool Button_left_push = false;
bool key[256];
float lightx,lighty,lightz;

void drawRectangle(GLfloat r, GLfloat g, GLfloat b);
void drawBase(int mode = 1);
void drawLower(int mode = 1);
void drawUpper(int mode = 1);
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


void doMainMenu(int entryID);
void menu();

void setLight();

typedef struct vector{
	GLfloat x;
	GLfloat y;
	GLfloat z;
}Vector;

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500,750);
	glutInitWindowPosition(500,0);
	glutCreateWindow("2011122355_camera_bot");

	glMatrixMode(GL_PROJECTION); glLoadIdentity();

	drawInit();
	menu();
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
void doMainMenu(int entryID){
	switch(entryID){
	case 0: CULLMODE = 0; break;
	case 1: CULLMODE = 1; break;
	case 2: CULLMODE = 2; break;
	case 3: CULLMODE = 3; break;
	case 10: exit(0); break;
	}
}


void menu(){
	GLint MainMenu = glutCreateMenu(doMainMenu);


	glutAddMenuEntry("후면제거",0);
	glutAddMenuEntry("전면제거",1);
	glutAddMenuEntry("전후면제거",2);
	glutAddMenuEntry("전후면보이기",3);
	glutAddMenuEntry("프로그램 종료",10);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

/* void drawBase();
*	로봇암의 Base를 그리는 Function
*/
void drawBase(int mode){
	if(mode){
		glColor3f(1,0,0); // Color Red
		glTranslatef(0, -1, 0);
		glRotatef(-90, 1, 0 ,0);
		glRotatef(base, 0, 0, 1);
		
		gluQuadricDrawStyle(c, GLU_FILL);
		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_BACK, GL_FILL);
		glFrontFace(GL_CW);
		//gluQuadricOrientation(c, GLU_INSIDE);
		//gluQuadricOrientation(c, GLU_OUTSIDE);
		glMaterialf(GL_FRONT, GL_SHININESS, 40.0);
		gluCylinder(c, 0.4, 0.2, 0.3, 8, 8);
		glFrontFace(GL_CCW);
	}else if(!mode){
		glColor3f(1,0,0); // Color Red
		glTranslatef(0, -1, 0);
		glRotatef(-90, 1, 0 ,0);
		glRotatef(_base, 0, 0, 1);
		gluQuadricDrawStyle(c, GLU_FILL);
		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_BACK, GL_FILL);
		glFrontFace(GL_CW);
		gluQuadricOrientation(c, GLU_OUTSIDE);
		//glPolygonMode(GL_FRONT, GL_FILL);
		glMaterialf(GL_FRONT, GL_SHININESS, 40.0);
		gluCylinder(c, 0.4, 0.2, 0.3, 8, 8);
		glFrontFace(GL_CCW);
	}
} 

/* void drawLower();
*	로봇암의 LowerArm 을 그리는 Function
*/
void drawLower(int mode){
	if(mode){	
		glColor3f(0, 0, 1); // Color Blue
		glRotatef(base, 0, 1, 0);

		glTranslatef(0, -0.7, 0);
		glRotatef(lower, 0, 0, 1);
		glTranslatef(0, 0.5, 0);

		glScalef(0.2, 1, 0.2);

		//glutSolidCube(1);
		drawRectangle(0, 0, 1);
	}else if(!mode){
		glColor3f(0, 0, 1); // Color Blue
		glRotatef(_base, 0, 1, 0);

		glTranslatef(0, -0.7, 0);
		glRotatef(_lower, 0, 0, 1);
		glTranslatef(0, 0.5, 0);

		glScalef(0.2, 1, 0.2);

		//glutSolidCube(1);
		drawRectangle(0, 0, 1);
	}
}

/* void drawUpper();
*	로봇암의 UpperArm 을 그리는 Function
*/
void drawUpper(int mode){
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_FRONT);
	//glCullFace(GL_FRONT_AND_BACK); // other primitives such as lines and points are drawn.
	if(mode){
		glColor3f(0, 1, 0); // Color Green
		glRotatef(base, 0, 1, 0);

		glTranslatef(0, -0.7, 0);
		glRotatef(lower, 0, 0, 1);
		glTranslatef(0, 1.0, 0);
		glRotatef(upper, 0, 0, 1);
		glTranslatef(0, 0.4, 0);

		glScalef(0.2, 0.8, 0.2);

		//glutWireCube(1);

		//glutSolidCube(1);
		drawRectangle(0, 1, 0);
	}else if(!mode){
		glColor3f(0, 1, 0); // Color Green
		glRotatef(_base, 0, 1, 0);

		glTranslatef(0, -0.7, 0);
		glRotatef(_lower, 0, 0, 1);
		glTranslatef(0, 1.0, 0);
		glRotatef(_upper, 0, 0, 1);
		glTranslatef(0, 0.4, 0);

		glScalef(0.2, 0.8, 0.2);

		//glutWireCube(1);
		//glutSolidCube(1);
		drawRectangle(0, 1, 0);
	}

} 

/* void drawCameraBot();
* 카메라 로봇을 그리는 Function
*/
void drawCameraBot(){
	
	
	glBegin(GL_LINE_LOOP);
		glColor3f(1,1,1);
			glVertex3f(0, 0, 0);
			glVertex3f(-20*vecx ,-20*vecy, -20*vecz);
	glEnd();

	glBegin(GL_LINE_LOOP);
		glColor3f(1,1,0);
			glVertex3f(botx, boty, botz);
			glVertex3f(atx ,aty, atz);
	glEnd();
	glColor3f(1,1,0);
	glBegin(GL_POLYGON);
	glVertex3f(botx - 3*vecx, aty, botz - 3*vecz);
	glVertex3f(botx - vecz , boty, botz + vecx);
	glVertex3f(botx + vecz , boty, botz - vecx);
	glEnd();

	
	//glDisable(GL_LIGHT2);
}

/* void drawBackGround();
* 배경을 그리는 Function
*/
void drawBackGround(){

	Vector nv = {0,0,0};
	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_POLYGON);
	nv.x = 0;
	nv.y = 1;
	nv.z = 0;
	glNormal3f(nv.x, nv.y, nv.z);
	glVertex3f(10,-1,10);		
	glVertex3f(-10,-1,10);
	glVertex3f(-10,-1,-10);
	glVertex3f(10,-1,-10);			
	glEnd(); // 바닥면

	glColor3f(0.8, 0.8, 0.8);
	glBegin(GL_POLYGON);
	nv.x = -1;
	nv.y = 0;
	nv.z = 0;
	glNormal3f(nv.x, nv.y, nv.z);
	glVertex3f(10,-1,10);		
	glVertex3f(10,-1,-10);
	glVertex3f(10,10,-10);				
	glVertex3f(10,10,10);
	glEnd(); // 옆면 1

	glColor3f(0.8, 0.8, 0.8);
	glBegin(GL_POLYGON);
	nv.x = 0;
	nv.y = 0;
	nv.z = 1;
	glNormal3f(nv.x, nv.y, nv.z);
	glVertex3f(-10,-1,-10);		
	glVertex3f(-10,10,-10);
	glVertex3f(10,10,-10);				
	glVertex3f(10,-1,-10);
	glEnd(); // 옆면 2

	glColor3f(0.8, 0.8, 0.8);
	glBegin(GL_POLYGON);					
	nv.x = 1;
	nv.y = 0;
	nv.z = 0;
	glNormal3f(nv.x, nv.y, nv.z);
	glVertex3f(-10,10,10);
	glVertex3f(-10,10,-10);
	glVertex3f(-10,-1,-10);
	glVertex3f(-10,-1,10);	
	glEnd(); // 옆면 3

		glColor3f(0.8, 0.8, 0.8);
	glBegin(GL_POLYGON);
	nv.x = 0;
	nv.y = 0;
	nv.z = -1;
	glNormal3f(nv.x, nv.y, nv.z);
	glVertex3f(-10,-1,10);		
	glVertex3f(10,-1,10);
	glVertex3f(10,10,10);				
	glVertex3f(-10,10,10);
	glEnd(); // 옆면 4


	glColor3f(1,0,0); // Line
	glBegin(GL_LINE_LOOP);
	glVertex3f(10,-1,0);
	glVertex3f(-10,-1,0);		
	glEnd();

	glColor3f(0,0,1); // Line
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
float recPoint;
void drawRectangle(GLfloat r, GLfloat g, GLfloat b){
	recPoint = 0.5;
	// 하단
	//GLfloat material_ambient[ ] = {0.1, 0.1, 0.1, 1.0};      		//물체 특성
	//GLfloat material_diffuse[ ] =  {0.1, 0.1, 0.1, 1.0};
	//GLfloat material_specular[ ] =  {0.1, 0.1, 0.1, 1.0}; 
	GLfloat material_shininess[ ] = {100.0};
	//
	//glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);       //물체 특성할당
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
	//glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);

	glColor3f(r,g,b);
	//glColor3f(0.5,0.5,0.5);
	static Vector nv = {0,1,0};
	glBegin(GL_POLYGON);	
	nv.x = 0;
	nv.y = -1;
	nv.z = 0;
	glNormal3f(nv.x , nv.y, nv.z);
	glMaterialf(GL_FRONT, GL_SHININESS, 40.0);
	glVertex3f(recPoint,-recPoint,-recPoint);		
	glVertex3f(-recPoint,-recPoint,-recPoint);
	glVertex3f(-recPoint,-recPoint,recPoint);
	glVertex3f(recPoint,-recPoint,recPoint);	
	glEnd();

	
	//glColor3f(0.5,0.5,0.5);
	// 상단
	glBegin(GL_POLYGON);
	nv.x = 0;
	nv.y = 1;
	nv.z = 0;
	glNormal3f(nv.x , nv.y, nv.z);
	glMaterialf(GL_FRONT, GL_SHININESS, 40.0);
	glVertex3f(recPoint,recPoint,recPoint);
	glVertex3f(-recPoint,recPoint,recPoint);
	glVertex3f(-recPoint,recPoint,-recPoint);
	glVertex3f(recPoint,recPoint,-recPoint);		
	glEnd();


	// 항상! 보는 기점이 기준이 된다고 보면 된다. 
	// 옆면들
	//glColor3f(r,g,b);
	glBegin(GL_POLYGON);
	nv.x = 0;
	nv.y = 0;
	nv.z = 1;
	glNormal3f(nv.x , nv.y, nv.z);
	glMaterialf(GL_FRONT, GL_SHININESS, 40.0);
	glVertex3f(recPoint,-recPoint,recPoint);
	glVertex3f(-recPoint,-recPoint,recPoint);
	glVertex3f(-recPoint,recPoint,recPoint);
	glVertex3f(recPoint,recPoint,recPoint);		
	glEnd();

	//glColor3f(0.5,0.5,0.5);
	glBegin(GL_POLYGON);
	nv.x = 1;
	nv.y = 0;
	nv.z = 0;
	glNormal3f(nv.x , nv.y, nv.z);
	glMaterialf(GL_FRONT, GL_SHININESS, 40.0);
	glVertex3f(recPoint,-recPoint,recPoint);
	glVertex3f(recPoint,recPoint,recPoint);
	glVertex3f(recPoint,recPoint,-recPoint);
	glVertex3f(recPoint,-recPoint,-recPoint);		
	glEnd();
	//
	//glColor3f(r,g,b);
	glBegin(GL_POLYGON);
	nv.x = 0;
	nv.y = 0;
	nv.z = -1;
	glNormal3f(nv.x , nv.y, nv.z);
	glMaterialf(GL_FRONT, GL_SHININESS, 40.0);
	glVertex3f(recPoint,-recPoint,-recPoint);
	glVertex3f(recPoint,recPoint,-recPoint);
	glVertex3f(-recPoint,recPoint,-recPoint);
	glVertex3f(-recPoint,-recPoint,-recPoint);		
	glEnd();

	//glColor3f(0.5,0.5,0.5);
	glBegin(GL_POLYGON);
	nv.x = -1;
	nv.y = 0;
	nv.z = 0;
	glNormal3f(nv.x , nv.y, nv.z);
	glMaterialf(GL_FRONT, GL_SHININESS, 40.0);
	glVertex3f(-recPoint,-recPoint,-recPoint);
	glVertex3f(-recPoint,recPoint,-recPoint);
	glVertex3f(-recPoint,recPoint,recPoint);
	glVertex3f(-recPoint,-recPoint,recPoint);		
	glEnd();

}
void setLight(){
}
void drawFigure(){
	

	// glCullFace(GL_BACK);glFrontFace(GL_CW);

	glEnable(GL_CULL_FACE);
	switch(CULLMODE){
	case 0: glCullFace(GL_FRONT); glFrontFace(GL_CCW); break;
	case 1: glCullFace(GL_BACK); break; //glFrontFace(GL_CW); break;
	case 2: glCullFace(GL_FRONT_AND_BACK); break;
	case 3: glDisable(GL_CULL_FACE); break;
	}
	// glFrontFace(GL_CCW); 이 상태 일 경우, 처음 디폴트 값은 FrontFacet 앞면이 반시계 Counter-Clock wise 이므로 당연!	

	// light


	glPushMatrix(); 
	glColor3f(1,0,0);
	glTranslatef(lightx,lighty,lightz);
	glutSolidSphere(0.1,300,300);
	glPopMatrix();

	//glPushMatrix();	glColor3f(1,0,0);	glTranslatef(3,1,3);	glutSolidSphere(0.3,300,300);	glPopMatrix();
	//glPushMatrix();	glColor3f(1,0,0);	glTranslatef(4,1,3);	glutSolidSphere(0.3,300,300);	glPopMatrix();
	//glPushMatrix();	glColor3f(1,0,0);	glTranslatef(5,1,3);	glutSolidSphere(0.3,300,300);	glPopMatrix();
	//glPushMatrix();	glColor3f(1,0,0);	glTranslatef(6,1,-3);	glutSolidSphere(0.1,300,300);	glPopMatrix();

	glPushMatrix(); drawBackGround(); glPopMatrix();
	glPushMatrix(); drawBase(); glPopMatrix();
	
	glPushMatrix(); drawLower(); glPopMatrix();	
	glPushMatrix(); drawUpper(); glPopMatrix();	

	// leaf robot
	//glLoadIdentity();

	glPushMatrix();
	glTranslatef(2,-0.5,2);
	glScalef(0.5,0.5,0.5);
	glPushMatrix(); drawBase(0); glPopMatrix();
	glPushMatrix(); drawLower(0); glPopMatrix();	
	glPushMatrix(); drawUpper(0); glPopMatrix();	
	glPopMatrix();
	
	//glLoadIdentity();
	//glScalef(0.5,1,1);
	//glTranslatef(-4,0,-5);

	glPushMatrix();
	glTranslatef(-2,-0.5,2);	
	glScalef(0.5,0.5,0.5);		
	glPushMatrix(); drawBase(0); glPopMatrix();
	glPushMatrix(); drawLower(0); glPopMatrix();	
	glPushMatrix(); drawUpper(0); glPopMatrix();	
	glPopMatrix();



	// add code
	//glLoadIdentity();
	glPushMatrix();
	glColor3f(1,1,0);
	glTranslatef(0,-0.5,3);
	//glutSolidCube(1);
	drawRectangle(1,1,0);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1,0,1);
	glTranslatef(-3,-0.5,3);
	drawRectangle(1,0,1);
	//glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0,1,1);
	glTranslatef(3,-0.5,0);	
	//glutSolidCube(1);
	drawRectangle(0,1,1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0,0.5,0.5);
	glTranslatef(-3,-0.5,-3);
	//glutSolidCube(1);
	drawRectangle(0,0.5,0.5);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.5,0.2,0.5);
	glScalef(0.5,0.5,0.5);
	glTranslatef(-3,-1.5,-3);
	//glutSolidCube(1);
	drawRectangle(0.5,0.5,0);
	glPopMatrix();

	if(key['`']){
		glEnable(GL_LIGHTING);
		//setLight();	
	}else{
		glDisable(GL_LIGHTING);
	}
	
	if(key['1']){
		glPushMatrix();
			glTranslatef(1,3,1);
			glutSolidSphere(0.1, 200, 200);
		glPopMatrix();
	}

	glDisable(GL_CULL_FACE);		 

	glPushMatrix(); drawCameraBot(); glPopMatrix();

	glDisable(GL_CULL_FACE);
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

	gluLookAt(botx, boty, botz,	atx, aty, atz,	upx, upy, upz); // 위를 바라보고 싶을 때는 atX, atY, atZ를 수정해야 하는데..
	
	// 1 : 변환프로세서


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40 , 1 , 1 ,100); // 원근감 설정
	// 2 : 투상프로세서
	glMatrixMode(GL_MODELVIEW);
		if(key['h']){
		GLfloat light1_POSITION[] = {botx, (boty-0.5), (botz), 1.0};
		GLfloat light1_CUTOFF[] = {15.0};
		GLfloat light1_DIRECTION[] = { -vecx, -vecy, -vecz};
		GLfloat light1_EXPONENT[] = {36.0};

		GLfloat light1_AMBIENT[] = {0.3, 0.3, 0.3, 1.0};
		GLfloat light1_DIFFUSE[] = {0.3, 0.3, 0.3, 1.0};
		GLfloat light1_SPECULAR[] = {0.3, 0.3, 0.3, 1.0};

		glLightfv(GL_LIGHT1, GL_POSITION, light1_POSITION); // 
		glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, light1_CUTOFF); 
		glLightfv(GL_LIGHT1, GL_SPOT_EXPONENT, light1_EXPONENT);

		glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light1_DIRECTION);

		//glLightfv(GL_LIGHT1, GL_AMBIENT, light1_AMBIENT);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_DIFFUSE);
		//glLightfv(GL_LIGHT1, GL_SPECULAR, light1_SPECULAR);

		glShadeModel(GL_SMOOTH);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT1);
		glEnable(GL_COLOR_MATERIAL); // 물체 색상 그대로 보존		
		printf("H key on\n");
	}
	drawFigure();
	// 3 : 절단프로세서
	// 4 : 래스터프로세서
	//glDisable(GL_LIGHTING);
	

}
/* void display_2();
* 화면 2 Function dis_2()
*/
void display_2(){
	glDisable(GL_DEPTH_TEST);

	glViewport(0, 0, 250, 250); 

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0, 5, 0, 
		0, 0, 0,
		0, 0, 1);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10, 10, -10, 10, -100, 100); // 평면

	glMatrixMode(GL_MODELVIEW);

	drawFigure();

	glEnable(GL_DEPTH_TEST);
}
// 화면 3 Function
void display_3(){
	//glDisable(GL_LIGHTING);
	glViewport(250, 0 , 250, 250);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(20,15,20,
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
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
	case ' ': key[' '] = true; break;

	case 'u': case 'U':key['u'] = true; break;
	case 'i': case 'I':key['i'] = true; break;
	case 'o': case 'O':key['o'] = true; break;
	case 'p': case 'P':key['p'] = true; break;
	case '[': key['['] = true; break;		
	case ']': key[']'] = true; break;

	case '7': key['7'] = true; break;
	case '8': key['8'] = true; break;
	case '9': key['9'] = true; break;
	case '0': key['0'] = true; break;
	case '-':case '_': key['-'] = true; break;		
	case '+':case '=': key['='] = true; break;

	case '1': key['1'] = !key['1']; break;
	case '2': key['2'] = true; break;
	case '3': key['3'] = true; break;
	case '4': key['4'] = true; break;
	case '5': key['5'] = true; break;
	case '6': key['6'] = true; break;

	case '`': key['`'] = !key['`']; break;

	case 'h': case 'H': key['h'] = !key['h']; break;
	}	
}
void doReleaseKey(unsigned char keyReleased, int x, int y){
	unsigned char *kp = &keyReleased;
	switch(*kp){	
	case 'w': case 'W': key['W'] = false; break; // 현재 보고 있는 BOT 과 AT 에 대해서 값을 바꿔야한다.
	case 's': case 'S': key['S'] = false; break; // 
	case 'a': case 'A': key['A'] = false; break;
	case 'd': case 'D': key['D'] = false; break;
	case ' ': key[' '] = false; break;

	case 'u': case 'U':key['u'] = false; break;
	case 'i': case 'I':key['i'] = false; break;
	case 'o': case 'O':key['o'] = false; break;
	case 'p': case 'P':key['p'] = false; break;
	case '[': key['['] = false; break;		
	case ']': key[']'] = false; break;

	case '7': key['7'] = false; break;
	case '8': key['8'] = false; break;
	case '9': key['9'] = false; break;
	case '0': key['0'] = false; break;
	case '-':case '_': key['-'] = false; break;		
	case '+':case '=': key['='] = false; break;

	//case '1': key['1'] = false; break;
	case '2': key['2'] = false; break;
	case '3': key['3'] = false; break;
	case '4': key['4'] = false; break;
	case '5': key['5'] = false; break;
	case '6': key['6'] = false; break;
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
		if(leftTempY > Y){ 
			//(aty < 5)?aty+=0.05:false; 
			aty+=0.05;
		}
		else if(leftTempY < Y){
			//	(aty > -1.2)?aty-=0.05:false; 
			aty-=0.05;
		}
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

	base = lower = upper = _base = _lower = _upper = 0;
	botx = 3; 	botz = 3;	boty = 0;
	atx = aty = atz = 0; 
	upx = upz = 0;	upy = 1;
	vecx = (botx - atx)/20; vecz = (botz - atz)/20;	vecy = (boty - aty)/20;
	CULLMODE = 3 ;

	lightx = lighty = lightz = 0;
	

	for(int i = 0 ; i < 256 ; i++)	key[i] = false;

	glClearColor(1,1,1,1);	
	glEnable(GL_DEPTH_TEST);
	//glDisable(GL_DEPTH_TEST);	
	//glEnable(GL_LIGHTING);
} 


// 키 움직임 감지
void keyMotion(){
	vecx = (botx - atx)/20; vecz = (botz - atz)/20;	vecy = (boty - aty)/20;
	GLfloat tmp = atx;
	GLfloat angle;

	// location point moving
	if(key['W']){ botx-=vecx/5; botz-=vecz/5;	atx-=vecx/5; atz-=vecz/5; }
	if(key['S']){ botx+=vecx/5; botz+=vecz/5;	atx+=vecx/5; atz+=vecz/5; }
	if(key['A']){ botx -= vecz/5; botz += vecx/5; atx -= vecz/5; atz += vecx/5; }
	if(key['D']){ botx +=vecz/5; botz -= vecx/5; atx +=vecz/5; atz -= vecx/5;	}

	if(key[' ']){ boty+=0.1;	aty+=0.1; 
	}else if(!key[' ']){ 	if(boty>=-0.5){	boty-=0.02;	aty-=0.02;	}     }

	
	// view point moving
	if(key[GLUT_KEY_UP]){ aty+=0.1; }
	if(key[GLUT_KEY_DOWN]){	aty-=0.1; }
	if(key[GLUT_KEY_LEFT]){	angle = -0.02;		
		atx =  (atx-botx) * cos(angle) - (atz-botz) * sin(angle) ;
		atz =  (tmp-botx) * sin(angle) + (atz-botz) * cos(angle) ;
		atx += botx;
		atz += botz;	
	}
	if(key[GLUT_KEY_RIGHT]){ angle = +0.02;
		atx =  (atx-botx) * cos(angle) - (atz-botz) * sin(angle);
		atz =  (tmp-botx) * sin(angle) + (atz-botz) * cos(angle);
		atx += botx;
		atz += botz;	
	}

	// add 161117
	if(key['u']){
		(upper >= -ANGLE_ARM) ? upper--: false;
		(_upper <= ANGLE_ARM) ? _upper++ : false;
	}
	if(key['i']){
		(upper <= ANGLE_ARM) ? upper++ : false;
		(_upper >= -ANGLE_ARM) ? _upper--: false;
	}
	if(key['o']){
		(lower >= -ANGLE_ARM) ? lower-- : false;
		(_lower <= ANGLE_ARM) ? _lower++ : false;
	}
	if(key['p']){
		(lower <= ANGLE_ARM) ? lower++ : false;
		(_lower >= -ANGLE_ARM) ? _lower-- : false;
	}
	if(key['[']){
		base--;
		_base++;
	}
	if(key[']']){
		base++;
		_base--;
	}


	//if(key['7']){
	//	(_upper >= -ANGLE_ARM) ? _upper--: false;
	//}
	//if(key['8']){
	//	(_upper <= ANGLE_ARM) ? _upper++ : false;
	//}
	//if(key['9']){
	//	(_lower >= -ANGLE_ARM) ? _lower-- : false;
	//}
	//if(key['0']){
	//	(_lower <= ANGLE_ARM) ? _lower++ : false;
	//}
	//if(key['-']){
	//	_base--;
	//}
	//if(key['=']){
	//	_base++;
	//}
	if(key['2']){	} // disable key
	if(key['3']){	} // disable key
	if(key['4']){	} // disable key
	if(key['5']){	} // disable key
	if(key['6']){	} // disable key
	if(key['7']){	} // disable key
	if(key['8']){	} // disable key
	if(key['9']){	} // disable key
	if(key['0']){	} // disable key
	if(key['-']){	} // disable key
	if(key['=']){	} // disable key

	if(key['1']){
		GLfloat light0_POSITION[] = {0, 2, 1, 0.5};
		//GLfloat light2_ANGLE[] = {30.0};
		GLfloat light0_DIRECTION[] = {0, -10, 0};
		GLfloat light0_AMBIENT[] = {0.2, 0.2, 0.2, 0.2};

		GLfloat light0_DIFFUSE[] = {0, 1.0, 0, 0.2};
		GLfloat light0_SPECULAR[] = {0, 0, 1.0, 0.2};
		
		glLightfv(GL_LIGHT0, GL_POSITION, light0_POSITION); // 
		
		glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light0_DIRECTION);
		glLightfv(GL_LIGHT0, GL_AMBIENT, light0_AMBIENT);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_DIFFUSE);
		glLightfv(GL_LIGHT0, GL_SPECULAR, light0_SPECULAR);
		// 설정부 끝

		glEnable(GL_LIGHTING); // 활성화
		glEnable(GL_LIGHT0);
	}else if(!key['1']){
		glDisable(GL_LIGHT0);
	}

	/*
	if(key['h']){
		GLfloat light1_POSITION[] = {botx, (boty-0.5), (botz), 1.0};
		GLfloat light1_CUTOFF[] = {15.0};
		GLfloat light1_DIRECTION[] = { -vecx, -vecy, -vecz};
		GLfloat light1_EXPONENT[] = {36.0};

		GLfloat light1_AMBIENT[] = {0.3, 0.3, 0.3, 1.0};
		GLfloat light1_DIFFUSE[] = {0.3, 0.3, 0.3, 1.0};
		GLfloat light1_SPECULAR[] = {0.3, 0.3, 0.3, 1.0};

		glLightfv(GL_LIGHT1, GL_POSITION, light1_POSITION); // 
		glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, light1_CUTOFF); 
		glLightfv(GL_LIGHT1, GL_SPOT_EXPONENT, light1_EXPONENT);

		glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light1_DIRECTION);

		//glLightfv(GL_LIGHT1, GL_AMBIENT, light1_AMBIENT);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_DIFFUSE);
		//glLightfv(GL_LIGHT1, GL_SPECULAR, light1_SPECULAR);

		glShadeModel(GL_FLAT);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT1);
		glEnable(GL_COLOR_MATERIAL); // 물체 색상 그대로 보존		
		printf("H key on\n");



	} */// high light
	if(!key['h']){
		glDisable(GL_LIGHT1);
		printf("H key off\n");
	}
	
	printf("어디보니 %f %f %f\n", vecx, vecy, vecz);
	printf("위치위치 %f %f %f\n", botx, boty, botz);
	printf("본다본다 %f %f %f\n", atx, aty, atz);
}

// 움직임을 부드럽게 하기위해서 doTimer
void doTimer(int v){
	keyMotion();
	//vecx = (botx - atx)/20; vecz = (botz - atz)/20;
	glutPostRedisplay();
	glutTimerFunc(20, doTimer, 1);
}