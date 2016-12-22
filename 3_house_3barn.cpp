#include<glut.h> // glut.h ��� ���� �ҷ���
#include<GL.H> // GL.H ��� ���� �ҷ���
#include<GLU.H> // GLU.h ��� ���� �ҷ���
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<iostream>

GLfloat rot = 0, zoom=50;
GLfloat rotup = 0;
GLfloat const firstX=4.5 , firstZ = 5; 
//ī�޶���ù X��Z��ǥ ����
//y�� ���� 
GLfloat aspect;

GLfloat camX = 4.5
	, camY = 3
	, camZ = 10 ;


GLfloat wf;
GLfloat hf;

GLfloat MyVertices[10][3] = { //���� �迭 ���� 
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
GLfloat MyColors[10][3] = { //�� ������ �ش��ϴ� ���� ����
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
GLubyte MyVertexList[30] = { //  ������ ���鶧�� ��������� ���� ����
	0, 5, 9, 4,
	3, 4, 9, 8,
	2, 3, 8, 7,
	1, 2, 7, 6,
	0, 1, 6, 5,
	5, 6, 7, 8, 9,
	0, 4, 3, 2, 1
};



void MyKeyboard(unsigned char KeyPressed, int X, int Y) { // Ű���� �ݹ��Լ�
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
	//glFrontFace(GL_FRONT); // �ո� �ݽð� �������� �׸���!
	// == glFrontFace(GL_CCW);
	// == glCullFace(GL_CCW);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);    

	glColorPointer(3, GL_FLOAT, 0, MyColors);
    glVertexPointer(3, GL_FLOAT, 0, MyVertices);

	// perspective projection
	glMatrixMode(GL_PROJECTION); // 2D->3D ? �ܰ踦 ��Ÿ����.
	glLoadIdentity(); // ������� �ʱ�ȭ
	gluPerspective(zoom * (hf) , aspect, 1, 100); // ���� ���� 


	// camera
	glMatrixMode(GL_MODELVIEW); // �ܰ�
	glLoadIdentity();

	GLfloat t, tt;

    t = rot * (3.14 / 180); 
	 
	// �ʱ���¸� �������� ī�޶��� ��ġ��
	// rot -> t �� ��ȯ  ��ŭ ȸ���̵��� ���·� ��Ÿ��.
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
    gluLookAt(camX, camY, camZ, 0.5, 0.5, 0.5, tx, n, tz); //ī�޶��� ��ġ ����
	// atxyz �ٶ󺸴� ���� 0.5 0.5 0.5 �ǻ�ü�� �߽� 
	//gluLookAt(camX, camY, camZ, 0.5, 0.5, 0.5, 0,1,0);

	for (int i = 0; i < 5; i++){ // �簢���׸���
              glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &MyVertexList[4 * i]);
	} 
    for (int i = 0; i < 2; i++){  //�������׸���
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
	glOrtho(-1.0, 1.0,-1.0,1.0,-1.0,1.0); //���ú��� ����
	
	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(doReshape);

	glutKeyboardFunc(MyKeyboard);
	glutMainLoop();
	return 0;
}