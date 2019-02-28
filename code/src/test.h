#ifndef _TEST_
#define _TEST_

#include "camera.h"
#include "cube.h"
#include "sphere.h"
#include "fluidsystem.h"

camera* mycamrea;
cube* mycube;
sphere* mysphere;
fluidsystem* mysystem;
int  play;
int count_here;

void CalculateFrameRate();
void keyboard(unsigned char key,int x,int y);
void reshape(int w,int h); //�״λ��ƺ���Ļ��С����ʱglutReshapeFunc()���øú���
void init();
void makeSmooth();
void display(void);
void saveBmp(const char* name,int width,int height,unsigned char* data);
void saveSceneImage();
void lightControl();

#endif

