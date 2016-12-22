#include<glut.h> // glut.h 헤더 파일 불러옴
#include<GL.H> // GL.H 헤더 파일 불러옴
#include<GLU.H> // GLU.h 헤더 파일 불러옴
#include<cstdio>
#include<math.h>
#include<stdlib.h>
#include<time.h>

// 변수 선언부
GLboolean random = false;
GLint tmpChange = 0;

GLint rotX, rotY;
GLfloat point[4][2] = { {-0.4,0.2}, {-0.4,-0.2}, {0.4, -0.2}, {0.4, 0.2} };
// 도형을 그리기위함 Vertex(정점)
GLint change = 0 ; // type 그려지는 타입
GLfloat R = 1.0, G = 1.0, B = 1.0; 
bool cnt = true;
GLboolean rt = false;
GLfloat cX, cY;

void doDisplay(){
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(R, G, B);
	glBegin(GL_LINE_LOOP);
	for(int idx = 0; idx < 4 ; idx++){
		glVertex3f(point[idx][0], point[idx][1], 0.0);
	}
	glEnd();

	glutSwapBuffers(); // 그린 후 버퍼를 바꿈.
}

void doKeyboard(unsigned char kp, int X, int Y){
	switch(kp){
	case 'q': case 'Q': exit(0); break;

	case '1': change = 1; rt = false;break;
	case '2': change = 2; rt = false;break;
	case '3': change = 3; rt = false;break;
	case '4': change = 4; rt = false;break;
	case 'a': change = 5; rt = false;break;
	case 'd': change = 6; rt = false;break;
	case 'w': change = 7; rt = false;break;
	case 'x': change = 8; rt = false;break;
	
	case 's': case 'S': 
		if(change != 0){
			tmpChange = change; change = 0 ;
		}else{
			change = tmpChange;
		} if(random){
			rt =true;
			random = false;
			change = 0;
		}else if(rt){
			rt = false; random = true;
		}break;

	case 'r': case 'R': change = 10; break; // reset;
	// color
	case 'g': case 'G': random = true; break;
	case 'h': case 'H': random = false; break;
	case 'z': case 'Z': R=1.0; G=B=0; break; // Red	
	}
}

void action(int v){
	float angle, tmpPoint;
	
	
	
	switch(v){ // clockwise-rot
	case 1:
		angle = -0.1;
		//glTranslatef(cX, cY, 0);
		
		cX = (point[0][0] + point[2][0])/2.0; //problem
		cY = (point[1][1] + point[3][1])/2.0;
		
		
		for(int i = 0; i < 4 ; i++){
			tmpPoint = point[i][0];
			printf("%f, %f \n",cX, cY);
			point[i][0] =  (point[i][0]-cX) * cos(angle) - (point[i][1]-cY) * sin(angle)  ;
			point[i][1] =  (tmpPoint-cX)      * sin(angle) + (point[i][1]-cY) * cos(angle) ;

			point[i][0] += cX;
			point[i][1] += cY;
		} break;
	case 2://counter-clockwise-rot
		angle = 1.0;
		cX = (point[0][0] + point[2][0])/2.0; //problem
		cY = (point[1][1] + point[3][1])/2.0;
		for (int i = 0; i<4; i++){
         tmpPoint = point[i][0];
		 printf("%f, %f \n",cX, cY);
         point[i][0] =  (point[i][0]-cX) * cos(angle) - (point[i][1]-cY) * sin(angle)  ;
			point[i][1] =  (tmpPoint-cX)      * sin(angle) + (point[i][1]-cY) * cos(angle) ;

			point[i][0] += cX;
			point[i][1] += cY;
      } break;
	case 3:// 확대
		for (int i = 0; i<4; i++){
			point[i][0] = point[i][0] * 1.02;
			point[i][1] = point[i][1] * 1.02;
		}break;
	case 4:
		for (int i = 0 ; i < 4 ; i++){
			point[i][0] = point[i][0] * 0.98;
			point[i][1] = point[i][1] * 0.98;
	} break;
	case 5: // 
		if(point[0][0] > -1 && point[1][0] > -1 && point[2][0] > -1 && point[3][0] > -1){
			for(int i = 0 ; i < 4 ; i++){
				point[i][0] = point[i][0] - 0.01;
				//cX -= 0.01;
			}
		} break;
	case 6:		
		if(point[0][0] < 1 && point[1][0] < 1 && point[2][0] < 1 && point[3][0] < 1){
			for(int i = 0 ; i < 4 ; i++){
				point[i][0] = point[i][0] + 0.01;
				//cX += 0.01;
			}
		} break;
	case 7:
		if(point[0][1] < 1 && point[1][1] < 1 && point[2][1] < 1 && point[3][1] < 1){
			for(int i = 0 ; i < 4 ; i++){
				point[i][1] = point[i][1] + 0.01;
				//cY += 0.01;
			}
		} break;
	case 8:
		if(point[0][1] > -1 && point[1][1] > -1 && point[2][1] > -1 && point[3][1] > -1){
			for(int i = 0 ; i < 4 ; i++){
				point[i][1] = point[i][1] - 0.01;
				//cY -= 0.01;
			}
		}break; 
	case 9: // un used		
		break;
	case 10:
		point[0][0] = -0.4; point[0][1] = 0.2;
		point[1][0] = -0.4; point[1][1] = -0.2;
		point[2][0] = 0.4; point[2][1] = -0.2;
		point[3][0] = 0.4; point[3][1] = 0.2;
		R = G = B = 1.0;
		break;		
	}
}

void doTimer(int v){
	 
	if(random){
		srand(time(NULL));
		int changeRandom = rand()%8 + 1;
		action(changeRandom);
		glutPostRedisplay(); // Redisplay
		glutTimerFunc(10, doTimer, 1);
		return;
	}else{
		action(change);	
	}

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
void SubMenu1(int eid){
   switch(eid){
   case 1: change = 1;break;
   case 2: change = 2; break;
   }
}
void SubMenu2(int eid){
   switch(eid){
   case 1: change =3 ; break;
   case 2: change =4 ;break;
   }
}
void SubMenu3(int eid){
   switch(eid){
   case 1: change = 5;break;
   case 2: change = 6; break;
   }
}

void menu(){
   GLint SubMenu_1 = glutCreateMenu(SubMenu1);
   glutAddMenuEntry("시계방향",1);
   glutAddMenuEntry("반시계방향",2);
   GLint SubMenu_2 = glutCreateMenu(SubMenu2);
   glutAddMenuEntry("확대",1);
   glutAddMenuEntry("축소",2);
   GLint SubMenu_3 = glutCreateMenu(SubMenu3);
   glutAddMenuEntry("좌",1);
   glutAddMenuEntry("우",2);

   GLint MainMenu = glutCreateMenu(doMainMenu);
   glutAddSubMenu("회전",SubMenu_1);

   glutAddSubMenu("확대/축소",SubMenu_2);

   glutAddSubMenu("이동",SubMenu_3);
      
   glutAddMenuEntry("자유변환",1);
   glutAddMenuEntry("프로그램 종료",0);

   glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char **argv){
	glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(600, 600); 
    glutInitWindowPosition(0, 0);
    glutCreateWindow("OpenGL 160929 Example");

	menu();

	
	
	glutKeyboardFunc(doKeyboard);
	glutDisplayFunc(doDisplay);
	glutTimerFunc(20, doTimer, 1);
	glutMainLoop();
	return 0;
}