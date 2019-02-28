#include <stdio.h>
#include <stdlib.h>
//#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include <vector>
#include <sstream>
#include <string>
#include "test.h"


using namespace std;


void saveBmp(const char* name,int width,int height,unsigned char* data)
{
	// BITMAPFILEHEADER hdr;
	// BITMAPINFOHEADER infoHdr;
	// infoHdr.biSize=40;
	// infoHdr.biWidth=width;
	// infoHdr.biHeight =height;
	// infoHdr.biPlanes =1;
	// infoHdr.biBitCount =24;
	// infoHdr.biCompression =0;
	// infoHdr.biSizeImage=width*height*3;
	// infoHdr.biXPelsPerMeter=0;
	// infoHdr.biYPelsPerMeter=0;
	// infoHdr.biClrUsed=0;
	// infoHdr.biClrImportant=0;
	
	// hdr.bfType = 0x4D42;
	// hdr.bfReserved1 = 0;
	// hdr.bfReserved2 = 0;
	// hdr.bfOffBits = 54;
	// hdr.bfSize =(DWORD)(sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+width* height * 3);
	
	// unsigned char x;
	// for(int i=0;i<infoHdr.biSizeImage;i+=3)
	// {
	// 	x=data[i];
	// 	data[i]=data[i+2];
	// 	data[i+2]=x;
	// }
	
	// FILE *fd;
	// fd=fopen(name,"wb");
	// fwrite(&hdr,sizeof(BITMAPFILEHEADER),1,fd);
	// fwrite(&infoHdr,sizeof(BITMAPINFOHEADER),1,fd);
	// fwrite(data,width* height*3,1,fd);
	// fclose(fd);
}


void saveSceneImage()
{
	int view[4];
	glGetIntegerv(GL_VIEWPORT,view);
	int bufferSize=view[2]*view[3]*3;
	void* color_buffer=malloc(bufferSize);
	glReadPixels(view[0],view[1],view[2],view[3],GL_RGB,GL_UNSIGNED_BYTE,color_buffer);
	
	string st,loc;
	loc="D:/test3/";
	stringstream  ss;
	ss<<count_here;
	ss>>st;
	st+=".bmp";
	loc+=st;
	saveBmp(loc.c_str(),view[2],view[3],(unsigned char*)color_buffer);
	free(color_buffer);	
}


void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
/*
	glutSolidCube(0.1);
	glColor3f(0,1,0);
	glutSolidCube(0.05);*/

	mysystem->drawThis();
	mysystem->drawThisInAnotherWayPart1();

	if(play==1)
	{
		mysystem->flowOfCalculate(count_here);
		//	saveSceneImage();
		count_here++;
	}

	//	mysystem->drawThisInAnotherWayPart2();
	
	CalculateFrameRate();
	glutSwapBuffers(); //˫����ʱ����
	glFlush();
	
	glutPostRedisplay();
}

void makeSmooth()
{
	glEnable(GL_LINE_SMOOTH); 
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glHint(GL_LINE_SMOOTH_HINT,GL_DONT_CARE);
	glLineWidth(1.5);
	
	glPointSize(2.0);
	
	glEnable(GLUT_MULTISAMPLE);
	glEnable(GL_POLYGON_SMOOTH);
}

void lightControl()
{

	float light_position[] ={0.09,-0.03,0.06,0};
	float white_light[] ={1,1,1.5,1};
	float lmod_ambient[]={0.5,0.5,0.65,1}; 
	float spot_direction[]={0,0.6,-0.9}; //�۹�Ƶ������������
	glShadeModel(GL_SMOOTH);
	glLightfv(GL_LIGHT0,GL_POSITION,light_position);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,white_light);
	glLightfv(GL_LIGHT0,GL_SPECULAR,white_light);
	glLightf(GL_LIGHT0,GL_SPOT_CUTOFF,90);
	glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION,spot_direction);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,lmod_ambient);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_NORMALIZE);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST); 
	glClearDepth(1.0);

	glEnable(GL_TEXTURE_2D);

}

void init()
{
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA) ;  // ˫���� RGBA(A��ʾ͸����) �����
	glutInitWindowSize(500,500) ; //���崰��λ�� 
	glutInitWindowPosition(100,100) ; //�������� 
	glutCreateWindow("SPH_test") ; 
	
	glClearColor(0.7,0.7,0.7,1);
    makeSmooth(); // �����
	lightControl();

	
	mycamrea=new camera(0.05,0.05,0.03);
	mycube=new cube(0,0,0,0.06,0.06,0.06);
//	mycube=new cube(0.03,0.03,0.04,0.12,0.12,0.08);
//	mysphere=new sphere(myvector(0.05,0.05,0.01),0.01);
	//mysphere=new sphere(myvector(0.06,0.06,0.08),0.05);
	mysystem=new fluidsystem(mycube,mysphere);

	play=0; 
	count_here=0;
	
}

void reshape(int w,int h) //�״λ��ƺ���Ļ��С����ʱglutReshapeFunc()���øú���
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0,(double)w/(double)h,0.1,500);  
	//  void APIENTRY gluPerspective ( GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar) 
	//�������������������������������ͶӰ�����쳣�����ֵ�����쳣��������Ϊ��
	
	glMatrixMode(GL_MODELVIEW);

	mycamrea->see();
}


void keyboard(unsigned char key,int x,int y)
{
	switch(key)
	{
	case 'a':
		mycamrea->rotate_LR(1);  
		break;
	case 'd':
		mycamrea->rotate_LR(-1); //��������������ƶ�����˰�d����������ʱ����ת����ʵ�����˳ʱ����ת
		break;
	case 'w':
		mycamrea->rotate_UD(1);
		break;
	case 's':
		mycamrea->rotate_UD(-1);
		break;
	case 'k':
		mycamrea->move(-1);
		break;
	case 'l':
		mycamrea->move(1);
		break;
	case 'p':
		play=1;
		break;
	case 'o':
		exit(0);
		break;
	}
	glutPostRedisplay();
}

void CalculateFrameRate()
{
    static float framesPerSecond=0.0f;       //�洢FPS
    static float lastTime=0.0f;       //ά���ϴε�ʱ������
    float currentTime=0.1;//GetTickCount()*0.001f;    
    ++framesPerSecond;
    if( currentTime-lastTime>1.0f )
    {
		lastTime = currentTime;
		printf("Current Frames Per Second: %d\n", int(framesPerSecond));
		framesPerSecond = 0;
    }
}

int main(int argc,char**argv)
{ 
	glutInit(&argc,argv) ; //��ʾģʽ��ʼ�� 
	init();	
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop() ; 
	
	return 0 ;
}
