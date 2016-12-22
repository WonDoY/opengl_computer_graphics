#include<glut.h> // glut.h 헤더 파일 불러옴
#include<GL.H> // GL.H 헤더 파일 불러옴
#include<GLU.H> // GLU.h 헤더 파일 불러옴
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<iostream>

GLfloat rot = 0, zoom=50;
GLfloat rotup = 0;
GLfloat const firstX=4.5 , firstZ = 5; 
//카메라의첫 X와Z좌표 설정
//y축 고정 
GLfloat aspect;

GLfloat camX = 4.5
	, camY = 3
	, camZ = 10 ;


GLfloat wf;
GLfloat hf;

GLfloat MyVertices[10][3] = { //정점 배열 선언 
	{0, 0, 0},
	{1, 0, 0},
	{1, 1, 0},
	{0.5, 1.5, 0},
	{0, 1, 0},
	{0, 0, 1},
	{1, 0, 1},
	{1, 1, 1},
	{0.5, 1.5, 1},
	{0, 1, 1} 
};
GLfloat MyColors[10][3] = { //각 정점에 해당하는 색깔 설정
	{ 1.0, 0.0, 0.0 },
	{ 1.0, 0.0, 0.0 },
	
	{ 0.0, 0.0, 1.0 },
	{ 0.0, 0.0, 1.0 }, 
	{ 1.0, 1.0, 0.0 },
	{ 1.0, 1.0, 0.0 },
	{ 1.0, 0.0, 1.0 },
	{ 1.0, 0.0, 1.0 },
	{ 0.5, 0.9, 0.5 },
	{ 0.5, 0.9, 0.5 }
};
GLubyte MyVertexList[30] = { //  도형을 만들때의 구성요소인 정점 설정
	0, 5, 9, 4,
	3, 4, 9, 8,
	2, 3, 8, 7,
	1, 2, 7, 6,
	0, 1, 6, 5,
	5, 6, 7, 8, 9,
	0, 4, 3, 2, 1
};



void MyKeyboard(unsigned char KeyPressed, int X, int Y) { // 키보드 콜백함수
	rot = rotup = 0;
       switch (KeyPressed) {
       case 'a': case 'A': rot = 5 ; break;
       case 'd': case 'D': rot = -5; break;
	   //case 'w': case 'W': rotup = -5; break;
	   //case 's': case 'S': rotup = 5;  break;
       case 'e': case 'E': zoom -= 1; break;			
       case 'r': case 'R': zoom += 1; break;
	   case 'q': case 'Q': exit(0); break;
	   default: rot = 0 ; break;
       }
	   glutPostRedisplay();
}


void MyDisplay(){

	
	
	glClear(GL_COLOR_BUFFER_BIT);
	//glFrontFace(GL_FRONT); // 앞면 반시계 방향으로 그린다!
	// == glFrontFace(GL_CCW);
	// == glCullFace(GL_CCW);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);    

	glColorPointer(3, GL_FLOAT, 0, MyColors);
    glVertexPointer(3, GL_FLOAT, 0, MyVertices);

	// perspective projection
	glMatrixMode(GL_PROJECTION); // 2D->3D ? 단계를 나타낸다.
	glLoadIdentity(); // 단위행렬 초기화
	gluPerspective(zoom * (hf) , aspect, 1, 100); // 원근 투영 


	// camera
	glMatrixMode(GL_MODELVIEW); // 단계
	glLoadIdentity();

	GLfloat t, tt;

    t = rot * (3.14 / 180); 
	 
	// 초기상태를 기준으로 카메라의 위치를
	// rot -> t 로 변환  만큼 회전이동한 상태로 나타냄.
	GLfloat tmpX = camX;
    camX = (camX - 0.5)*cos(t) - (camZ- 0.5)*sin(t)  ; 
    camZ = (tmpX - 0.5)*sin(t) + (camZ- 0.5)*cos(t)  ;
	camX += 0.5;
	camZ += 0.5;

	//tmpX = camX;
 //   camX = (tmpX - 0.5)*cos(tt) - (camY- 0.5)*sin(tt)  ; 
 //   camY = (camX-0.5)* sin(tt) + (camY -0.5)*cos(tt) ;
	//camX += 0.5;
	//camY += 0.5;
	//tt = rotup * (3.14 / 180);
	//GLfloat tmpZ = camZ;
 //   camZ = (tmpZ - 0.5)*cos(tt) - (camY- 0.5)*sin(tt)  ; 
 //   camY = (tmpZ - 0.5) * sin(tt) + (camY -0.5)*cos(tt) ;
	//camZ += 0.5;
	//camY += 0.5;
	
	printf("%.2f %.2f\n",camX, camZ);
	GLfloat tx = 0.5-camX, tz = 0.5-camZ, ty = 0.5-camY;

	GLfloat n = sqrt(pow((ty/2)*tz,2)+ pow(tx*tz,2)+ pow(tx*(ty/2),2));
    gluLookAt(camX, camY, camZ, 0.5, 0.5, 0.5, tx, n, tz); //카메라의 위치 설정
	// atxyz 바라보는 방향 0.5 0.5 0.5 피사체의 중심 
	//gluLookAt(camX, camY, camZ, 0.5, 0.5, 0.5, 0,1,0);

	for (int i = 0; i < 5; i++){ // 사각형그리기
              glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &MyVertexList[4 * i]);
	} 
    for (int i = 0; i < 2; i++){  //오각형그리기
              glDrawElements(GL_POLYGON, 5, GL_UNSIGNED_BYTE, &MyVertexList[20+ 5 * i]);
	}
	printf("tt %.2f %.2f %.2f\n",tx, n, tz);
	glColor3f(0,1,0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.5,10,0.5);
	glVertex3f(0.5,0,0.5);
	glEnd();
	glColor3f(0,0,0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(tx, n, tz);
	glVertex3f(0,0,0);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glVertex3f(tx+0.5, n+0.5, tz+0.5);
	glVertex3f(0.5,0.5,0.5);
	glEnd();
	glColor3f(1,0,0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(10,0,0);
	glVertex3f(-10,0,0);
	glEnd();
	
	glColor3f(0,0,1);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0,0,10);
	glVertex3f(0,0,-10);
	glEnd();
	glutSwapBuffers();
	//glFlush();

}
void doReshape(int w, int h){
	glViewport(0,0,w,h);
	 wf = w/500.0;
	 hf = h/500.0;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	aspect = wf/hf;

	//glutPostRedisplay();

}

int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 100);
	glutCreateWindow("OpenGL View Example 161006");
	glClearColor(1.0, 1.0, 1.0, 1.0	);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0,-1.0,1.0,-1.0,1.0); //가시부피 설정
	
	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(doReshape);

	glutKeyboardFunc(MyKeyboard);
	glutMainLoop();
	return 0;
}