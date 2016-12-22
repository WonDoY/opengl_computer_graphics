#include<glut.h> // glut.h 헤더 파일 불러옴
#include<GL.H> // GL.H 헤더 파일 불러옴
#include<GLU.H> // GLU.h 헤더 파일 불러옴
#include<cstdio>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#define KEY_ESC 27

// 변수 선언부
GLboolean random = false;
GLint tmpChange = 0;

GLint rotX, rotY;
GLfloat point[4][2] = { {-0.4,0.2}, {-0.4,-0.2}, {0.4, -0.2}, {0.4, 0.2} };
// 도형을 그리기위함 Vertex(정점)
GLint change = 0 ; // type 그려지는 타입
GLint rot = 0;
GLint move = 0;
GLint scale = 0;
GLint star = 0;
GLfloat R = 1.0, G = 1.0, B = 1.0; 
bool cnt = true;
GLboolean rt = false;
GLfloat cX, cY;

void doDisplay(){
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(R, G, B);
	
	glBegin(GL_POLYGON);

	for(int idx = 0; idx < 4 ; idx++){
		glVertex3f(point[idx][0], point[idx][1], 0.0);
	}
	glEnd();


	glutSwapBuffers(); // 그린 후 버퍼를 바꿈.
}
// key ignored
void doKeyboard(unsigned char kp, int X, int Y){
	switch(kp){
	case 'q': case 'Q': case KEY_ESC: exit(0); break;

	case '1': rot = 1; break;
	case '2': rot = 2; break;
	case '3': scale = 3; break;
	case '4': scale = 4; break;
	case 'a': case 'A': move = 5; break;
	case 'd': case 'D': move = 6; break;
	case 'w': case 'W': move = 7; break;
	case 'x': case 'X': move = 8; break;
	
	case 's': case 'S': 
		rot=scale=move=star=0;

	case 'r': case 'R': change = 10; break; // reset;
	// color

	case 'z': case 'Z': R=1.0, G=B=0; break; // Red	
	case 'g': case 'G': G=1.0; R=B=0; break;
	case 'c': case 'C': B=1.0; R=G=0; break;
	case 'v': case 'V': 
		if(!star){
			star = 1;
		}else {
			star =0;
		}break;
	}
}

void action(int v){
	float angle, tmpPoint;	
	
	
}
GLint loop = 0 ;
GLfloat tmpR,tmpG,tmpB;
void doTimer(int v){
	 
	//if(random){
	//	srand(time(NULL));
	//	int changeRandom = rand()%8 + 1;
	//	action(changeRandom);
	//	glutPostRedisplay(); // Redisplay
	//	glutTimerFunc(10, doTimer, 1);
	//	return;
	//}else{
	//action(change);	

	if(star){
		if(!loop){
			loop = 1;
			tmpR = R; tmpG = G; tmpB = B;
			R=G=B =0;
		}else{
			R=tmpR; G=tmpG; B=tmpB;
			loop = 0;
		}
		//srand(time(NULL));
		//GLfloat sOfR = (double)rand()/RAND_MAX; ;GLfloat sOfG = (double)rand()/RAND_MAX ; GLfloat sOfB = (double)rand()/RAND_MAX ;
		//R = sOfR; G = sOfG; B = sOfB;	
	}	
	GLfloat angle,tmpPoint;
	cX = (point[0][0] + point[2][0])/2.0; //problem
	cY = (point[1][1] + point[3][1])/2.0;

	glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	angle = 0;
	//glPushMatrix();
	
	switch(rot){
	case 1: angle = 10;break;
	case 2: angle = -10; break;
			
	}
	glTranslatef(cX,cY,0);
	glRotatef(-angle,0,0,1.0 );
	glTranslatef(-cX,-cY,0);
	//glPopMatrix();
	


	//glPushMatrix();


	//glPushMatrix();
	switch(scale){
	case 3:glScalef(1.05,1.05,0);break;
	case 4:glScalef(0.95,0.95,0);break;
	}
	//glPopMatrix();
	
		glBegin(GL_POINTS);
	for(int idx = 0; idx < 4 ; idx++){
		glVertex3f(point[idx][0], point[idx][1], 0.0);
	}
	glEnd();
	glMatrixMode(GL_PROJECTION);
		switch(move){
	case 5:glTranslatef(-0.02,0,0); break;
	case 6:glTranslatef(0.02,0,0);break;
	case 7:glTranslatef(0,0.02,0);break;
	case 8:glTranslatef(0,-0.02,0);break;
	}
	//glPopMatrix();
		for(int idx = 0; idx < 4 ; idx++){
		glVertex3f(point[idx][0], point[idx][1], 0.0);
	}
	glEnd();

	glutPostRedisplay(); // Redisplay
	glutTimerFunc(20, doTimer, 1);
}

// Mouse Right Buttom Click Menu
void doMainMenu(int entryID){
   switch(entryID){
   case 1: random = true; break;
   case 2:  break;
   case 0:
      exit(0); break;
   }
}
void SubMenu1(int eid){ // Rotation
	switch(eid){
	case 0: rot = 0; break;
	case 1: rot = 1; break;
	case 2: rot = 2; break;
	}
}
void SubMenu2(int eid){ // Scaling
	switch(eid){
	case 0: scale = 0 ; break;
	case 1: scale = 3; break;
	case 2: scale = 4; break;
	}
}
void SubMenu3(int eid){ // Translation
   	switch(eid){
	case 0: 
	case 1: move = 7;break;
	case 2: move = 8;break;
	case 3: move = 5;break;
	case 4: move = 6;break;
	}
}
void SubMenu4(int eid){ // Color
	switch(eid){
	
	case 0: R=G=B=1.0; break;
	case 1: R=1.0; G=B=0; break;
	case 2: G=1.0; R=B=0; break;
	case 3: B=1.0; R=G=0; break;	
	}
}
void SubMenu5(int eid){ // Star
	
	switch(eid){
	case 0: star =0; break;
	case 1: star = 1; break;// Redisplay
	}
}

void menu(){
   GLint SubMenu_1 = glutCreateMenu(SubMenu1);
   glutAddMenuEntry("선택안함",0);
   glutAddMenuEntry("시계방향",1);
   glutAddMenuEntry("반시계방향",2);
   GLint SubMenu_2 = glutCreateMenu(SubMenu2);
   glutAddMenuEntry("선택안함",0);
   glutAddMenuEntry("확대",1);
   glutAddMenuEntry("축소",2);
   GLint SubMenu_3 = glutCreateMenu(SubMenu3);
   glutAddMenuEntry("선택안함",0);
   glutAddMenuEntry("상",1);
   glutAddMenuEntry("하",2);
   glutAddMenuEntry("좌",3);
   glutAddMenuEntry("우",4);
   GLint SubMenu_4 = glutCreateMenu(SubMenu4);
   glutAddMenuEntry("White(Default)",0);
   glutAddMenuEntry("Red",1);
   glutAddMenuEntry("Green",2);
   glutAddMenuEntry("Blue",3);
   GLint SubMenu_5 = glutCreateMenu(SubMenu5);
   glutAddMenuEntry("선택안함",0);
   glutAddMenuEntry("반짝이",1);



   GLint MainMenu = glutCreateMenu(doMainMenu);
   glutAddSubMenu("회전",SubMenu_1);
   glutAddSubMenu("스케일링",SubMenu_2);
   glutAddSubMenu("이동",SubMenu_3);
   glutAddSubMenu("색",SubMenu_4);
   glutAddSubMenu("반짝이",SubMenu_5);

   glutAddMenuEntry("프로그램 종료",0);

   glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void doReshape(int W, int H){
	glViewport(0,0, W,H);
	GLfloat WF = (GLfloat)W / (GLfloat)600;
	GLfloat HF = (GLfloat)H / (GLfloat)300;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(- WF, WF, -HF, HF , -1.0, 1.0);
}
int main(int argc, char **argv){
	glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(600, 300); 
    glutInitWindowPosition(0, 0);
    glutCreateWindow("OpenGL 160929 Example");

	menu();

	glOrtho(-2.0, 2.0, -1.0, 1.0 , -1.0, 1.0);
	glutReshapeFunc(doReshape);
	glutKeyboardFunc(doKeyboard);
	glutDisplayFunc(doDisplay);
	glutTimerFunc(20, doTimer, 1);
	glutMainLoop();
	return 0;
}