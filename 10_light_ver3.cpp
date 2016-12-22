/*�װ����б� ����Ʈ�����а� 
* 2011122355 ������
* ī�޶� �κ� source code
*/
#include<cstdio>
#include<cmath>
#include<glut.h>
#include<GL.H>
#include<GLU.H>
#define ANGLE_ARM 88

//typedef GLfloat GFL;

GLUquadricObj *c; // Cylinder
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

void initLight();
void setLight();

typedef struct vector{
	GLfloat x;
	GLfloat y;
	GLfloat z;
}Vector;

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800,1200);
	//glutInitWindowSize(500,750);
	glutInitWindowPosition(500,0);
	glutCreateWindow("2011122355_light_shade");

	glMatrixMode(GL_PROJECTION); glLoadIdentity();

	drawInit();
	menu();

	glutDisplayFunc(doDisplay);
	glutKeyboardFunc(doKeyboard);
	glutKeyboardUpFunc(doReleaseKey); // Ű���� �����Է��� ���� �ݹ��Լ�
	glutSpecialFunc(doSpecialKey);
	glutSpecialUpFunc(doSpecialReleaseKey); // Ű���� �����Է��� ���� �ݹ��Լ�
	glutTimerFunc(20,doTimer,1);

	glutMouseFunc(doMouse);
	glutMotionFunc(doMotion);

	//glutFullScreen();
	glutMainLoop();

	return 0;
} // not prob
void doMainMenu(int entryID){
	switch(entryID){
	case 0: CULLMODE = 0; break;
	case 1: CULLMODE = 1; break;
	case 2: CULLMODE = 2; break;
	case 3: CULLMODE = 3; break;

	case 4: glShadeModel(GL_SMOOTH); break;
	case 5: glShadeModel(GL_FLAT); break;
	case 10: exit(0); break;
	}
} // not prob


void menu(){
	GLint MainMenu = glutCreateMenu(doMainMenu);

	glutAddMenuEntry("�ĸ�����",0);
	glutAddMenuEntry("��������",1);
	glutAddMenuEntry("���ĸ�����",2);
	glutAddMenuEntry("���ĸ麸�̱�",3);

	glutAddMenuEntry("Shade/Smooth",4);
	glutAddMenuEntry("Shade/Flat",5);
	glutAddMenuEntry("���α׷� ����",10);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
} // not prob

/* void drawBase();
*	�κ����� Base�� �׸��� Function
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
		
		//gluQuadricOrientation(c, GLU_INSIDE);
		gluQuadricOrientation(c, GLU_OUTSIDE);
		glMaterialf(GL_FRONT, GL_SHININESS, 40.0);
		gluCylinder(c, 0.4, 0.2, 0.3, 80, 80);
		
	}else if(!mode){
		glColor3f(1,0,0); // Color Red
		glTranslatef(0, -1, 0);
		glRotatef(-90, 1, 0 ,0);
		glRotatef(_base, 0, 0, 1);
		gluQuadricDrawStyle(c, GLU_FILL);
		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_BACK, GL_FILL);
		
		gluQuadricOrientation(c, GLU_OUTSIDE);
		
		glMaterialf(GL_FRONT, GL_SHININESS, 40.0);
		gluCylinder(c, 0.4, 0.2, 0.3, 80, 80);
		
	}
} 

/* void drawLower();
*	�κ����� LowerArm �� �׸��� Function
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
*	�κ����� UpperArm �� �׸��� Function
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
* ī�޶� �κ��� �׸��� Function
*/
void drawCameraBot(){
	
	
	glBegin(GL_LINE_LOOP);
		glColor3f(1,1,1);
		glVertex3f(0, 0, 0);
		glVertex3f(20*vecx ,20*vecy, 20*vecz);
	glEnd(); // Vector from (0,0,0)

	glBegin(GL_LINE_LOOP);
		glColor3f(1,1,0);
		glVertex3f(botx, boty, botz);
		glVertex3f(atx ,aty, atz);
	glEnd(); // Vector from bot position to at position

	glColor3f(1,1,1);
	glBegin(GL_POLYGON);
		glVertex3f(botx + 3*vecx, boty + 3*vecy, botz + 3*vecz);
		glVertex3f(botx - vecz , boty, botz + vecx);
		glVertex3f(botx + vecz , boty, botz - vecx);
	glEnd(); // triangle 
}

/* void drawBackGround();
* ����� �׸��� Function
*/
void drawBackGround(){

	Vector nv = {0,0,0}; // �������� �Ҵ��ϱ� ���� ����ü (x, y, z)
	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_POLYGON);
	nv.x = 0;
	nv.y = 1;
	nv.z = 0;
	glNormal3f(nv.x, nv.y, nv.z);
	glVertex3f(10,-1,10);		
	glVertex3f(10,-1,-10);
	glVertex3f(-10,-1,-10);
	glVertex3f(-10,-1,10);			
	glEnd(); // �ٴڸ�

	/*
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
	glEnd(); // ���� 1

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
	glEnd(); // ���� 2

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
	glEnd(); // ���� 3

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
	glEnd(); // ���� 4
	*/

	for(int i = -10; i <= 10 ; i++){		
			glColor3f(1,0,0); // Line
			glBegin(GL_LINE_LOOP);
				glVertex3f(10,-1,i);
				glVertex3f(-10,-1,i);		
			glEnd();	

			glColor3f(0,0,1); // Line
			glBegin(GL_LINE_LOOP);
			glVertex3f(i,-1,10);
			glVertex3f(i,-1,-10);		
			glEnd();
	}
	


}


/*
* ��� �׸��� Function �� ���ĳ���
* BackGround();
* drawBase();
* drawLower(); 
* drawUpper();
* drawCameraBot();
*/
float recPoint;
void drawRectangle(GLfloat r, GLfloat g, GLfloat b){
	//glEnable(GL_NORMALIZE);
	GLfloat rec = 0.5;
	// �ϴ�
	//GLfloat material_ambient[ ] = {0.1, 0.1, 0.1, 1.0};      		//��ü Ư��
	//GLfloat material_diffuse[ ] =  {0.1, 0.1, 0.1, 1.0};
	//GLfloat material_specular[ ] =  {0.1, 0.1, 0.1, 1.0}; 
	GLfloat material_shininess[ ] = {100.0}; 
	//
	//glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);       //��ü Ư���Ҵ�
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
	glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);
	glVertex3f( rec,-rec,-rec); // + -
	glVertex3f( rec,-rec, rec);  // + +
	glVertex3f(-rec,-rec, rec); // - +
	glVertex3f(-rec,-rec,-rec);// - -		
	glEnd();
	
	// �ϴ�

	
	//glColor3f(0.5,0.5,0.5);
	// ���
	glBegin(GL_POLYGON);
	nv.x = 0;
	nv.y = 1;
	nv.z = 0;
	glNormal3f(nv.x , nv.y, nv.z);
	glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);
	glVertex3f(rec,rec,rec); //  + +
	glVertex3f(rec,rec,-rec); // + -
	glVertex3f(-rec,rec,-rec);// - -
	glVertex3f(-rec,rec,rec); // - +		
	glEnd();


	// �׻�! ���� ������ ������ �ȴٰ� ���� �ȴ�. 
	// �����
	//glColor3f(r,g,b);
	//glColor3f(0,0,0);
	//GLfloat i, j;
	//for(i = -0.5 ; i <= 0.5 ; i+=0.1){
	//	for(j = -0.5 ; j <= 0.5 ; j+=0.1){
	//		glBegin(GL_QUAD_STRIP);
	//		nv.x = 0.1;
	//		nv.y = 0;
	//		nv.z = 0;
	//		glNormal3f(nv.x , nv.y, nv.z);
	//		glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);
	//			glVertex3f(+rec ,  +i,  +j); // ++
	//			glVertex3f(+rec ,  -i,  +j); // ++
	//			glVertex3f(+rec ,  -i,  -j); // +-
	//			glVertex3f(+rec ,  +i,  -j); // +-	
	//		
	//	}
	//	glEnd();
	//}
	glBegin(GL_POLYGON);
	nv.x = 1;
	nv.y = 0;
	nv.z = 0;
	glNormal3f(nv.x , nv.y, nv.z);
	glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);
	glVertex3f(rec, rec, rec);
	glVertex3f(rec,-rec, rec);
	glVertex3f(rec,-rec,-rec);
	glVertex3f(rec, rec,-rec);
	glEnd();

	//glColor3f(0.5,0.5,0.5);
	//glColor3f(r,g,b);
	glBegin(GL_POLYGON);
	nv.x = 0;
	nv.y = 0;
	nv.z = -1;
	glNormal3f(nv.x , nv.y, nv.z);
	glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);
		glVertex3f(-rec,-rec,-rec);  // --
		glVertex3f(-rec,rec,-rec); // 
		glVertex3f( rec,rec,-rec); 
		glVertex3f( rec,-rec,-rec);		
	glEnd();
	//
	//glColor3f(r,g,b);
	glBegin(GL_POLYGON);
	nv.x = -1;
	nv.y = 0;
	nv.z = 0;
	glNormal3f(nv.x , nv.y, nv.z);
	glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);
	glVertex3f(-rec,-rec,rec); // -+
	glVertex3f(-rec, rec, rec);  // -+
	glVertex3f(-rec, rec,-rec); // --
	glVertex3f(-rec,-rec,-rec);// --
	glEnd();

	//glColor3f(0.5,0.5,0.5);
	glBegin(GL_POLYGON);
	nv.x = 0;
	nv.y = 0;
	nv.z = 1;
	glNormal3f(nv.x , nv.y, nv.z);
	glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);
	glVertex3f(rec,-rec,rec); // ++
	glVertex3f(rec, rec,rec); //++
	glVertex3f(-rec, rec,rec); // -+
	glVertex3f(-rec,-rec,rec); //-+
	glEnd();

}
void initLight(){
	GLfloat light0_POSITION[] = {0, 4, 0, 1.0};
	GLfloat light0_ANGLE[] = {90.0};
	GLfloat light0_DIRECTION[] = {0, -1, 0};
	GLfloat light0_AMBIENT[] = {0.5, 0.5, 0.5, 1.0};
	GLfloat light0_DIFFUSE[] = {0.5, 0.5, 0.5, 1.0};
	GLfloat light0_SPECULAR[] = {0.5, 0.5, 0.5, 1.0};

	glLightfv(GL_LIGHT0, GL_POSITION, light0_POSITION); // 
	//glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF, light0_ANGLE);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light0_DIRECTION);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_AMBIENT);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_DIFFUSE);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_SPECULAR);
	// light0 set
	GLfloat light1_POSITION[] = {(botx), (boty), (botz), 1.0};
	GLfloat light1_CUTOFF[] = {15.0};
	GLfloat light1_DIRECTION[] = {vecx, vecy, vecz};
	GLfloat light1_EXPONENT[] = {1.0};		
	GLfloat light1_DIFFUSE[] = {0.3, 0.3, 0.3, 1.0};

	glLightfv(GL_LIGHT1, GL_POSITION, light1_POSITION);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light1_DIRECTION);
	glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, light1_CUTOFF);
	glLightfv(GL_LIGHT1, GL_SPOT_EXPONENT, light1_EXPONENT);		
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_DIFFUSE);
	// light1 set
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
}
void setLight(){
	if(key['1']){
		glEnable(GL_LIGHT0);		
	}else if(!key['1']){
		glDisable(GL_LIGHT0);
	}

	if(key['`']){ 
		glEnable(GL_LIGHTING); 
	}else if(!key['`']){
		glDisable(GL_LIGHTING); 
	}
	
	if(key['h']){
		GLfloat light1_DIFFUSE[] = {0.3, 0.3, 0.3, 1.0};
		GLfloat light1_POSITION[] = {(botx), (boty), (botz), 1.0};
		GLfloat light1_DIRECTION[] = {vecx, vecy, vecz};

		if(key['2']){
			light1_DIFFUSE[0] = 1.0; 
			light1_DIFFUSE[1] = 0.0;
			light1_DIFFUSE[2] = 0.0;
			printf("KEY ON : RED HIGH LIGHT\n");
		}
		if(key['3']) {
			light1_DIFFUSE[0] = 0.0;
			light1_DIFFUSE[1] = 0.0;
			light1_DIFFUSE[2] = 1.0;			
			printf("KEY ON : BLUE HIGH LIGHT\n");
		}
		if(key['4']) {
			light1_DIFFUSE[0] = 1.0;
			light1_DIFFUSE[1] = 1.0;
			light1_DIFFUSE[2] = 0.0;
			printf("KEY ON : YELLOW HIGH LIGHT\n");
		}

		glLightfv(GL_LIGHT1, GL_POSITION, light1_POSITION);
		glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light1_DIRECTION);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_DIFFUSE);

		glEnable(GL_LIGHT1);
	}else if(!key['h']){
		glDisable(GL_LIGHT1);
	}
}
void drawFigure(){
	
	switch(CULLMODE){
	case 0: 
		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CCW);  
		glCullFace(GL_BACK);
		break;
	case 1: 
		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CCW);  
		glCullFace(GL_FRONT);
		break; // break;
	case 2: 
		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CCW);  
		glCullFace(GL_FRONT_AND_BACK); 		
		break;
	case 3: 
		glDisable(GL_CULL_FACE); 
		break;
	}
	// glFrontFace(GL_CCW); �� ���� �� ���, ó�� ����Ʈ ���� FrontFacet �ո��� �ݽð� Counter-Clock wise �̹Ƿ� �翬!	
	GLfloat material_shine[] = { 100.0 };

	glPushMatrix();
		glTranslatef(2,1,2);
		glMaterialfv(GL_FRONT, GL_SHININESS, material_shine);
		//glutSolidTeapot(0.1);
	glPopMatrix();

	glPushMatrix();	
		glColor3f(1,0,0);	glTranslatef(3,0,3);	glMaterialfv(GL_FRONT, GL_SHININESS, material_shine);	glutSolidSphere(0.3,300,300);	
	glPopMatrix(); // RED SPHERE

	glPushMatrix();	
		glColor3f(0,0,1);	glTranslatef(3,0,2);	glMaterialfv(GL_FRONT, GL_SHININESS, material_shine);glutSolidSphere(0.3,300,300);	
	glPopMatrix(); // BLUE SPHERE
	
	glPushMatrix();
		glColor3f(1,1,0);	glTranslatef(2,0,3);	glMaterialfv(GL_FRONT, GL_SHININESS, material_shine);glutSolidSphere(0.3,300,300);	
	glPopMatrix(); // YELLOW SPHERE
	
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
		glMaterialfv(GL_FRONT, GL_SHININESS, material_shine);		
		drawRectangle(1,1,0);
		//glutSolidCube(1);
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
		drawRectangle(0,1,1);
		//glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
		glColor3f(0,0.5,0.5);
		glTranslatef(-3,-0.5,-3);
		drawRectangle(0,0.5,0.5);
		//glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
		glColor3f(0.5,0.2,0.5);
		glScalef(0.5,0.5,0.5);
		glTranslatef(-3,-1.5,-3);
		drawRectangle(0.5,0.5,0);
		//glutSolidCube(1);
	glPopMatrix();


	
	if(key['1']){ // ������(����LIGHT1) ������ ON �� ���.
		glPushMatrix();
			glTranslatef(1,3,1);
			glMaterialfv(GL_FRONT, GL_SHININESS, material_shine);		
			glutSolidSphere(0.1, 200, 200);
		glPopMatrix();
	} 

	glDisable(GL_CULL_FACE);		 

	glPushMatrix(); drawCameraBot(); glPopMatrix();	
}


/* void display_1();
* ȭ��1 Function ; dis_1()
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
	glViewport(0, 400, 800, 800); // ���ϴ� + ����
	// viewport ����
	// MODELVIEW, ī�޶���
	// PROJECTION, ���ٰ� || ��� ����
	// MODELVIEW, �׸���
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	gluLookAt(botx, boty, botz,	atx, aty, atz,	upx, upy, upz); // ���� �ٶ󺸰� ���� ���� atX, atY, atZ�� �����ؾ� �ϴµ�..
	setLight();
	// 1 : ��ȯ���μ���


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40 , 1 , 1 ,100); // ���ٰ� ����
	// 2 : �������μ���
	glMatrixMode(GL_MODELVIEW);

	drawFigure();
	
	
	// 3 : �������μ���
	// 4 : ���������μ���
}
/* void display_2();
* ȭ�� 2 Function dis_2()
*/
void display_2(){
	glDisable(GL_DEPTH_TEST);

	glViewport(0, 0, 400, 400); 

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	gluLookAt(0, 5, 0, 
		0, 0, 0,
		0, 0, 1);
	setLight();

	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();
	glOrtho(-10, 10, -10, 10, -10, 10); // ���

	glMatrixMode(GL_MODELVIEW);

	drawFigure();

	glEnable(GL_DEPTH_TEST);
}
// ȭ�� 3 Function
void display_3(){
	glViewport(400, 0 , 400, 400);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	gluLookAt(11,11,11,
		0,0,0,
		0,1,0);
	setLight();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30,1,1,100); // ���ٰ�

	glMatrixMode(GL_MODELVIEW);

	drawFigure();
} 
/* void fullDisplay();
* ��ü display func
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
* �Ϲ����� Ű���� �ݹ��Լ�
*/

void doKeyboard(unsigned char keyPressed, int x, int y){
	unsigned char *kp = &keyPressed;	
	switch(*kp){
	case 'q': case 'Q': exit(0); break;
	case 'w': case 'W': key['W'] = true; break; // ���� ���� �ִ� BOT �� AT �� ���ؼ� ���� �ٲ���Ѵ�.
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

	case '1': key['1'] = !key['1']; break; // Key is ON/OFF
	case '2': key['2'] = true; key['3'] = key['4'] = key['5'] = false; break;
	case '3': key['3'] = true; key['2'] = key['4'] = key['5'] = false; break;
	case '4': key['4'] = true; key['2'] = key['3'] = key['5'] = false; break;
	case '5': key['5'] = true; key['2'] = key['3'] = key['4'] = false; break;
	case '6': key['6'] = !key['6']; break; // Key is ON/OFF

	case '`': key['`'] = !key['`']; break; // Key is ON/OFF

	case 'h': case 'H': key['h'] = !key['h']; break; // Key is ON/OFF
	}	
}
void doReleaseKey(unsigned char keyReleased, int x, int y){
	unsigned char *kp = &keyReleased;
	switch(*kp){	
	case 'w': case 'W': key['W'] = false; break; 
	case 's': case 'S': key['S'] = false; break; 
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
	//case '2': key['2'] = false; break;
	//case '3': key['3'] = false; break;
	//case '4': key['4'] = false; break;
	//case '5': key['5'] = false; break;
	//case '6': key['6'] = false; break;
	}
}
/* void doSpecialKey(int , int , int);
* Special keyboard callback func
* Ư�� Ű �ݹ��Լ�
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
* ���� �̵��� �ϱ� ���� ���콺 Function ���ʹ�ư�� ���� ���¿���
* �ش� ��ǥ�� �����ϰ� doMotion���� �����̵��� �Ѵ�.
*/
void doMouse(int Button ,int State, int X, int Y){
	(Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN) ? leftTempX = X, leftTempY = Y, Button_left_push = true : printf("leftButton false");	
	(Button == GLUT_LEFT_BUTTON && State == GLUT_UP) ?  Button_left_push = false : false ;
}

/* void doMotion(int, int);
* ���콺 �����̵��� ����Ѵ�.
*/
void doMotion(int X, int Y){
	GLfloat tmp = atx;
	GLfloat angle;	

	if(Button_left_push){
		if(leftTempY > Y){ 
			key[GLUT_KEY_UP] = true;
			//aty+=0.1; 
		}
		else if(leftTempY < Y){
			key[GLUT_KEY_DOWN] = true;
			//aty-=0.1; 
		}
		leftTempY = Y;

		if(leftTempX > X){
			key[GLUT_KEY_LEFT] = true;
			//angle = -0.05;		
			//atx =  (atx-botx) * cos(angle) - (atz-botz) * sin(angle) ;
			//atz =  (tmp-botx) * sin(angle) + (atz-botz) * cos(angle) ;
			//atx += botx;
			//atz += botz;	
		}else if(leftTempX < X){
			key[GLUT_KEY_RIGHT] = true;
			//angle = +0.05;
			//atx =  (atx-botx) * cos(angle) - (atz-botz) * sin(angle);
			//atz =  (tmp-botx) * sin(angle) + (atz-botz) * cos(angle);
			//atx += botx;
			//atz += botz;	
		}
		leftTempX = X;
	}
}

/* void drawInit();
*�׸��� ���� ������ ó�� ���� �Լ��� ȣ���� �� �ʱ�ȭ���ֱ� ���� Function
*/
void drawInit(){
	c = gluNewQuadric();
	gluQuadricDrawStyle(c, GLU_LINE);

	base = 0.0;
	lower = 0.0;
	upper = 0.0;

	_base = 0.0;
	_lower = 0.0;
	_upper = 0.0;

	botx = 5.0;
	botz = 5.0;
	boty = 0.0;

	atx = 0.0;
	aty = 0.0;
	atz = 0.0;

	upx = 0.0;
	upz = 0.0;
	upy = 1.0;

	vecx = (atx - botx)/20; 
	vecz = (atz - botz)/20;	
	vecy = (aty - boty)/20;
	
	CULLMODE = 3 ;	

	for(int i = 0 ; i < 256 ; i++)	key[i] = false;

	initLight();

	glClearColor(1,1,1,1);	
	glEnable(GL_DEPTH_TEST);
} 


// Ű ������ ����
void keyMotion(){
	vecx = (atx - botx)/20; 
	vecz = (atz - botz)/20;	
	vecy = (aty - boty)/20;
	
	GLfloat tmp = atx;
	GLfloat angle;

	// location point moving
	if(key['S']){ botx-=vecx/5; botz-=vecz/5;	atx-=vecx/5; atz-=vecz/5; }
	if(key['W']){ botx+=vecx/5; botz+=vecz/5;	atx+=vecx/5; atz+=vecz/5; }
	if(key['D']){ botx -= vecz/5; botz += vecx/5; atx -= vecz/5; atz += vecx/5; }
	if(key['A']){ botx +=vecz/5; botz -= vecx/5; atx +=vecz/5; atz -= vecx/5;	}

	if(key[' ']){ boty+=0.1;	aty+=0.1; 
	}else if(!key[' ']){ if(boty>=0.0){boty-=0.02;aty-=0.02;} }

	
	// view point moving
	if(key[GLUT_KEY_UP]){ 
		aty+=0.1; 
	}
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
	if(Button_left_push){
		key[GLUT_KEY_UP] = false;
		key[GLUT_KEY_DOWN] = false;
		key[GLUT_KEY_LEFT] = false;
		key[GLUT_KEY_RIGHT] = false;
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

	//if(key['2']){	} // disable key
	//if(key['3']){	} // disable key
	//if(key['4']){	} // disable key
	//if(key['5']){	} // disable key
	//if(key['6']){	} // disable key
	//if(key['7']){	} // disable key
	//if(key['8']){	} // disable key
	//if(key['9']){	} // disable key
	//if(key['0']){	} // disable key
	//if(key['-']){	} // disable key
	//if(key['=']){	} // disable key
	
	//printf("��𺸴� %f %f %f\n", vecx, vecy, vecz);
	//printf("��ġ��ġ %f %f %f\n", botx, boty, botz);
	//printf("���ٺ��� %f %f %f\n", atx, aty, atz);
}

// �������� �ε巴�� �ϱ����ؼ� doTimer
void doTimer(int v){
	keyMotion();
	glutPostRedisplay();
	glutTimerFunc(20, doTimer, 1);
}