#include<glut.h> // glut.h 헤더 파일 불러옴
#include<GL.H> // GL.H 헤더 파일 불러옴
#include<GLU.H> // GLU.h 헤더 파일 불러옴
#include<cstdio>
#include<math.h>

#define MAX 1000 
#define KEY_ESC 27
#define KEY_LEFT 100
#define KEY_RIGHT 102

GLint TopLeftX[MAX], TopLeftY[MAX], BottomRightX[MAX], BottomRightY[MAX];
GLfloat R[MAX], G[MAX], B[MAX];
GLint type[MAX];

int cnt = 0;
int cnt_constraint = 0;



GLfloat winSizeX, winSizeY;
void storeFigure(){
}
void MyDisplay( ){	

	//glViewport(0, 0, 300, 300); // 뷰포트 설정.
	glClear(GL_COLOR_BUFFER_BIT); // 현재 컬러버퍼에 저장된 값으로 화면을 clear

	if(cnt+1 > MAX){ // Error 
		printf("Error 01 %d; 출력초과\n",MAX);	exit(0);		
	} // 내부적으로 정해둔 것을 초과함.
	
	for(int i = 0 ; i < cnt; i++){
		glColor3f(R[i], G[i], B[i]); 
		printf("%d 번째 도형, 타입 %d ; TopLeftX/Y <%d,%d> BottomRightX/Y <%d,%d> \n",i+1, type[i], TopLeftX[i],TopLeftY[i], BottomRightX[i], BottomRightY[i]); 
		switch(type[i]){
		case 0: 
			glBegin(GL_LINES);   // 뷰포트 좌표계  모델좌표계 // 이전의 그렸던 것들 

				glVertex3f(TopLeftX[i]/ 300.0, (300-TopLeftY[i])/300.0, 0.0); 			
				glVertex3f(BottomRightX[i]/300.0, (300-BottomRightY[i])/300.0, 0.0);
			
			glEnd( ); 
			break;
		case 1:
			glBegin(GL_TRIANGLES);   // 뷰포트 좌표계  모델좌표계 // 이전의 그렸던 것들 

				glVertex3f(TopLeftX[i]/300.0, (300-TopLeftY[i])/300.0, 0.0); 			
				glVertex3f(TopLeftX[i]/300.0, (300-BottomRightY[i])/300.0, 0.0);  
				glVertex3f(BottomRightX[i]/300.0, (300-BottomRightY[i])/300.0, 0.0);
				glVertex3f(BottomRightX[i]/300.0, (300-TopLeftY[i])/300.0, 0.0); 

			glEnd( );
			break;
		case 2:
			glBegin(GL_POLYGON);   // 뷰포트 좌표계  모델좌표계 // 이전의 그렸던 것들 

				glVertex3f(TopLeftX[i]/300.0, (300-TopLeftY[i])/300.0, 0.0); 			
				glVertex3f(TopLeftX[i]/300.0, (300-BottomRightY[i])/300.0, 0.0);  
				glVertex3f(BottomRightX[i]/300.0, (300-BottomRightY[i])/300.0, 0.0);
				glVertex3f(BottomRightX[i]/300.0, (300-TopLeftY[i])/300.0, 0.0); 
			
			glEnd( );
			break;
		case 3:
			// type i == 3 은 일단보류
			break;
		}


		// glFlush() 부분이 여기있었다...
	}
	glColor3f(R[cnt], G[cnt], B[cnt]);
	switch(type[cnt]){ // 현재 그리고 있는 것.
	case 0: 
		glBegin(GL_LINES);   // 뷰포트 좌표계  모델좌표계 // 이전의 그렸던 것들 

		glVertex3f(TopLeftX[cnt]/300.0, (300-TopLeftY[cnt])/300.0, 0.0); 			
		glVertex3f(BottomRightX[cnt]/300.0, (300-BottomRightY[cnt])/300.0, 0.0);

		glEnd( ); break;
	case 1: 
		glBegin(GL_TRIANGLES);   // 뷰포트 좌표계  모델좌표계 // 이전의 그렸던 것들 

		glVertex3f(TopLeftX[cnt]/300.0, (300-TopLeftY[cnt])/300.0, 0.0); 			
		glVertex3f(TopLeftX[cnt]/300.0, (300-BottomRightY[cnt])/300.0, 0.0);  
		glVertex3f(BottomRightX[cnt]/300.0, (300-BottomRightY[cnt])/300.0, 0.0);
		glVertex3f(BottomRightX[cnt]/300.0, (300-TopLeftY[cnt])/300.0, 0.0); 
		glEnd( );
		break;
	case 2:
		glBegin(GL_POLYGON);   // 뷰포트 좌표계  모델좌표계 // 이전의 그렸던 것들 


		glVertex3f(TopLeftX[cnt]/300.0, (300-TopLeftY[cnt])/300.0, 0.0); 			
		glVertex3f(TopLeftX[cnt]/300.0, (300-BottomRightY[cnt])/300.0, 0.0);  
		glVertex3f(BottomRightX[cnt]/300.0, (300-BottomRightY[cnt])/300.0, 0.0);
		glVertex3f(BottomRightX[cnt]/300.0, (300-TopLeftY[cnt])/300.0, 0.0); 
		glEnd( );
		break;
	case 3:
		glBegin(GL_POLYGON);   // 뷰포트 좌표계  모델좌표계 // 이전의 그렸던 것들 
		// 일단 보류
		glEnd( );
		break;
	}

	if(cnt+1 < MAX && cnt >= 0){
		type[cnt+1] = type[cnt];
		R[cnt+1] = R[cnt]; 
		G[cnt+1] = G[cnt];
		B[cnt+1] = B[cnt];
	}
	glFlush( );	// Display 마지막에는 Flush 가 있어야 바로바로 쏠 수 있다. 
}

//bool Click = false;
void MyMouseClick(GLint Button, GLint State, GLint X, GLint Y){

	if(Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN){ // 마우스클릭 click ; press
		TopLeftX[cnt] = X;
		TopLeftY[cnt] = Y;		
	}
	if(Button == GLUT_LEFT_BUTTON && State == GLUT_UP){ // 마우스클릭 release
		cnt++;
		if(cnt_constraint > 0){
			cnt_constraint = 0;
		}
	}
	// glutPostRedisplay(); // 이 부분을 넣었을 때 0,0 부터 ~ 클릭한 부분으로 잠깐 출력이 되었다. ; 제거


}
/*
*
* MyMouseMove(GLint , GLint);
* glutMotionFunc(argv) ; 의 argv callback function 
* press->pressed ; 이후 release 전까지 Mouse Motion 의 움직임이 있을 때 연속적으로 호출한다.  
*/
void MyMouseMove(GLint X, GLint Y){ // pressed, moving

	BottomRightX[cnt] = X;
	BottomRightY[cnt] = Y;

	glutPostRedisplay(); 
}
/*
* 
* Key board callback func
*/
void CaptureScreen()
{
	/*
	BMP(bitmap)의 구조
	비트맵파일헤더
	비트맵인포헤더
	팔레트
	이미지데이터
	typedef unsigned long       DWORD;
	typedef unsigned short      WORD;
	BYTE (=unsigned char) : 0~255
	CHAR (=signed char) : -128~127
	INT(=int) : 16 or 32 bit (machine dependent)
	INT8 (=signed char) : -128~127
	INT16 (=short) : -32768~32767
	INT32 (=long) : -2147483648~2147483647
	LONG (=long) : -2147483648~2147483647 (machine dependent)
	SHORT (=short) : -32768~32767
	TCHAR (=char or INT16) : 8bit or 16bit char, _UNICODE 정의에 따라 다름
	UINT (=unsigned int) : 16 or 32bit (0~65535:16bit) (machine dependent)
	UINT8 (=unsigned char) : 0~255
	UINT16 (=unsigned short) : 0~65535
	UINT32 (=unsigned long) : 0~4294967295
	ULONG (=unsigned long) : 0~4294967295 (machine dependent)
	USHORT (=unsigned short): 0~65535
	
	float : 3.4x10^-38 ~ 3.4x10^38    (유효숫자 7자리)
	double : 1.7x10^-308 ~ 1.7x10^308    (유효숫자 15자리)
	long double : 3.4x10^-4932 ~ 3.4x10^4932    (유효숫자 19자리)

	DWORD (=unsigned long) : 0~4294967295
	32비트 = 4바이트
	WORD = 2바이트
	typedef struct tagBITMAPFILEHEADER {
	v	WORD bfType;            //BM 이라고 써있으면 bmp
	v	DWORD bfSize;           //이미지 크기
		WORD bfReserved1;
		WORD bfReserved2;
	v	DWORD bfOffBits;      //이미지 데이터가 있는 곳의 포인터
	} BITMAPFILEHEADER
	14 = 4+2+4+4+2 

	typedef struct tagBITMAPINFOHEADER{
	v	DWORD biSize;          //현 구조체의 크기
	v	LONG biWidth;          //이미지의 가로 크기
	v	LONG biHeight;         //이미지의 세로 크기
	v	WORD biPlanes;        //플레인수
	v	WORD biBitCount     //비트 수
		DWORD biCompression;  //압축 유무
	v	DWORD biSizeImage;       //이미지 크기
		LONG biXPelsPerMeter;  //미터당 가로 픽셀
		LONG biYPelsPerMeter;  //미터당 세로 픽셀
		DWORD biClrUsed;         //컬러 사용 유무
		DWORD biClrImportant;  //중요하게 사용하는 색
	} BITMAPINFOHEADER;
	4+4+4+2+2+4+4+4+4+4+4
	= 40
	*/

	BITMAPFILEHEADER bmpfile; // 비트맵파일헤더
	BITMAPINFOHEADER bmpinfo; // 비트맵정보헤더

	int Width, Height;
	Width = Height = 300;

	unsigned char *pixels	= new unsigned char[sizeof(unsigned char)*Width*Height*3]; //unsigned char = BYTE 0-255
	FILE *file	= fopen("capture.bmp", "wb");


	glReadPixels( 0, 0, Width, Height, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels );

	// void * memset ( void * ptr, int value, size_t num );
	// memset 메모리 블록을 채운다.  ptr로 시작하는 메모리 주소부터 num개의 바이트를 value 값으로 채움. 
	// 이때 value 는 unsigned char 형변환된다.
	// ptr ; 값을 채울 메모리의 시작 주소
	// value ; 채울 값. 인자로는 int 로 전달되지만 함수 내부적으로는 unsigned char 로 형변환 되어서 사용된다.
	// num ; value 로 채울 바이트 수
	// ptr 값이 리턴 
	/*
	int main ()
	{
		char str[] = "Hello, World!";
		memset (str,'-',6);
		puts (str);
		return 0;
	}
	일시에 출력은
	Hello, World!
	------ World!

	*/

	memset( &bmpfile, 0, sizeof( bmpfile ) ); // 14바이트 0 값.
	memset( &bmpinfo, 0, sizeof( bmpinfo ) ); // 
	printf("%d",sizeof( bmpfile ));
	bmpfile.bfType	= 'MB'; 
	bmpfile.bfSize	= sizeof(bmpfile)+sizeof(bmpinfo)+Width*Height*3;
	bmpfile.bfOffBits	= sizeof(bmpfile)+sizeof(bmpinfo); 

	bmpinfo.biSize	= sizeof(bmpinfo); // 구조체크기
	bmpinfo.biWidth	= Width; // 이미지 가로
	bmpinfo.biHeight	= Height; // 이미지 세로
	bmpinfo.biPlanes	= 1; // 플레인수
	bmpinfo.biBitCount	= 24; // 비트수 
	bmpinfo.biSizeImage	= Width*Height*3; // 이미지의크기

	fwrite( &bmpfile, sizeof(bmpfile), 1, file );
	fwrite( &bmpinfo, sizeof(bmpinfo), 1, file );
	fwrite( pixels, sizeof(unsigned char), Height*Width*3, file );

	fclose( file );

	free( pixels );

}

void MyKeyboard(unsigned char KeyPressed, int X, int Y){
	switch(KeyPressed){
	case 'Q': case'q':	exit(0); break;
	case 'S': case 's':
		CaptureScreen();
		printf("save!\n");
		
		break;
	case 'A': case'a':
		if(cnt > 0){
			cnt--;
			cnt_constraint++;			
		}
		glutPostRedisplay();
		break;
	case 'D': case 'd':
		if(cnt+1 < MAX && cnt_constraint > 0){
			cnt++;	
			cnt_constraint--;
		}
		glutPostRedisplay();
		break;
	case KEY_ESC : // ASCII code 값으로 int 형 값이 들어가야함! ESC
		for(int i = 0 ; i < cnt+1 ; i++){ // 값초기화
			if(i==cnt){				
				type[0] = type[i];
				R[0] = R[i];
				G[0] = G[i];
				B[0] = B[i]; 
			}
			TopLeftX[i] = TopLeftY[i] = 0;
			BottomRightX[i] = BottomRightY[i] = 0;
			R[i] = G[i] = B[i] = 0; 			
		}
		cnt = 0;
		glutPostRedisplay(); // 이게 다시 re-display를 해주므로 추가! 'ESC' Key를 눌렀을 때 다시 화면에 뿌려줌.
		break;
		
		// 빨주노초파남보
		//  1 2 3 4 5 6 7
		// Case. color Function 

	case '1': // Red
		R[cnt] = 1.0; G[cnt] = B[cnt] = 0; break;
	case '2': // Orange
		R[cnt] = 1.0; G[cnt] = 0.5;	B[cnt] = 0; break;
	case '3': // Yellow
		R[cnt] = 1.0; G[cnt] = 1.0;	B[cnt] = 0; break;
	case '4': // Green
		G[cnt] = 1.0; R[cnt] = B[cnt] = 0; break;
	case '5': // Blue
		B[cnt] = 1.0; G[cnt] = R[cnt] = 0; break;
	case '6': // deep Blue
		B[cnt] = 0.5; G[cnt] = R[cnt] = 0; break;
	case '7': // purple
		G[cnt] = 0;	R[cnt] = B[cnt] = 1.0; break;
	case 'W': case 'w': // Line
		type[cnt] = 0;	break;
	case 'E': case 'e': // Triangle
		type[cnt] = 1;	break;
	case 'R': case 'r': // Rectangle
		type[cnt] = 2;	break;
	case 'C': case 'c': // Circle ; 굉장히 하기 힘든거구나.
		type[cnt] = 3;	break;
	}

}
// struct ! 
// 
void MyMainMenu(int entryID){
	switch(entryID){
	case 1: break;
	case 2: break;
	case 3:
		exit(0); break;
	}
}

//void MyReshape(int NewWidth, int NewHeight){
//	glViewport(0,0,NewWidth, NewHeight);
//
//	GLfloat WidthF = (GLfloat) NewWidth / (GLfloat)300;
//	GLfloat HeightF = (GLfloat) NewHeight / (GLfloat)300;
//
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//
//	glOrtho(-1.0 * WidthF, 1.0 *WidthF , -1.0 * HeightF, 1.0 *HeightF, -1.0, 1.0);
//}
int main(int argc, char** argv){

	// 1. 윈도우 초기생성
	glutInit(&argc, argv); // 메인함수의 매개변수로 초기화시킴.	
	glutInitDisplayMode(GLUT_RGB); // 현재 저장된 GLUT_RGB (State Variable)로 디스플레이모드를 초기화
	glutInitWindowSize(300, 300); // WindowSize , 300pixel * " 로 
	glutInitWindowPosition(0, 0); // WindowPosition 0, 0 
	glutCreateWindow("OpenGL Drawing Example");	// Window 창을 만듬. 


	glClearColor(1.0 , 1.0 , 1.0 , 1.0 );	// 색을 1,1,1 로 클리어
	glMatrixMode(GL_PROJECTION); // 투사체
	glLoadIdentity();
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);

	GLint MyMainMenuID = glutCreateMenu(MyMainMenu);
	glutAddMenuEntry("Save",1);
	glutAddMenuEntry("Load",2);
	glutAddMenuEntry("Exit",3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutDisplayFunc(MyDisplay);  // 1 ; 
	glutMouseFunc(MyMouseClick); // 마우스 click & release 시 호출
	glutMotionFunc(MyMouseMove); // 마우스 press 상태에서 움직임 좌표값.
	//glutReshapeFunc(MyReshape);
	glutKeyboardFunc(MyKeyboard);
	/* 1 ; 이 위치로 변경된다고 해서 KeyboardFunc 다음에 호출되는 것은 아니다. */
	glutMainLoop();

	return 0;
}

