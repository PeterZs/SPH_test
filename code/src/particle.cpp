#include <stdio.h>
#include <stdlib.h>
//#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include <vector>
#include "physic.h"
#include "myvector.h"
#include "particle.h"

using namespace std;

particle::particle()
{
	;
}

particle::particle(double x,double y,double z) 
{
	location.set(x,y,z);
}
//�β�����������ã������ڴ��з���ռ䣬�����ǲ��ǻ����������ͻ����࣬����������ã���ֻ��ʵ��һ�ݴ����ڴ��У��ββ�����ռ�
particle::particle(const particle& part)  //�������캯������������const���ʵ�ͬ������  const��֤�����ں������޸�ԭ������
{
	location=myvector(part.location);
	speed=myvector(part.speed);
}

particle::~particle()
{
	;
}

void particle::drawParticle()
{
	if(density>=physic::threshold)
	{
		double r=physic::r_smoothCore/6;
		glColor3d(0,0,1);
		glPushMatrix();
		glTranslated(location.x,location.y,location.z);
		glutSolidSphere(r,30,30);
    	glPopMatrix();
	}	
}


void particle::drawParticle(double d_max,double d_min)
{
	double percentage=(density-d_min)/(d_max-d_min);
	int key=floor(percentage*7.0);
	if(key==0)
	{
		printf("%lf\n",density);
	}
	glBegin(GL_POINTS);
	glColor3dv(physic::color[key]);
	glVertex3d(location.x,location.y,location.z);
	glEnd();
}

void particle::reSet() //�ܶ����¼���  ѹ���ͼ��ٶȾ������ܶ������Ժ����ֵ���¼��� ���ٶ����ó�ֻ��ϵͳ�������ٶ�
{
	density=0.0; 
	a_sp=myvector(0,0,0);
}

void particle::calPressure()
{
	pressure=physic::gasK*(density-physic::staticDensity);
}

void particle::calLoactionAndSpeed(double tim,double l,double w,double h)
{
	double speed_limit_square=physic::speedLimiting*physic::speedLimiting;
	
	//�ٶ�����
	double a_sp_2 = a_sp.len_sq();
	if(a_sp_2>speed_limit_square)
	{
		a_sp*= physic::speedLimiting/sqrt(a_sp_2);
	}	
	
	//X��
	double diff=0.005-location.x;
	if (diff>0) 
	{
		myvector norm=myvector(1,0,0);
		double adj=physic::stiffness*diff-physic::dampening*norm.dot(speed_equal);
		a_sp+=(adj*norm);			
	}
	
	diff=0.005-(l-location.x);	
	if (diff>0) 
	{
		myvector norm=myvector(-1,0,0);
		double adj=physic::stiffness*diff-physic::dampening*norm.dot(speed_equal);
		a_sp+=(adj*norm);	
	}
	
	//Y��
	diff=0.005-location.y;
	if (diff>0) 
	{
		myvector norm=myvector(0,1,0);
		double adj=physic::stiffness*diff-physic::dampening*norm.dot(speed_equal);
		a_sp+=(adj*norm);					
	}
	
	diff=0.005-(w-location.y);	
	if (diff>0) 
	{
		myvector norm=myvector(0,-1,0);
		double adj=physic::stiffness*diff-physic::dampening*norm.dot(speed_equal);
		a_sp+=(adj*norm);	
	}
	
	//Z��
	diff=0.012-location.z;
	if(diff>0) 
	{
		myvector norm=myvector(0,0,1);
		double adj=physic::stiffness*diff-physic::dampening*norm.dot(speed_equal);
		a_sp+=(adj*norm);						
	}
	
	diff=0.012-(h-location.z);	
	if(diff>0) 
	{
		myvector norm=myvector(0,0,-1);
		double adj=physic::stiffness*diff-physic::dampening*norm.dot(speed_equal);
		a_sp+=(adj*norm);		
	}

	a_sp+=physic::a_gravity;
	//�������ַ�
	myvector speed_next;
	speed_next=speed+tim*a_sp;
	speed_equal=(speed+speed_next)*0.5;
	speed=speed_next;
	location+=speed*tim;
	
	location.x=max(0.00000000001,location.x); location.x=min(location.x,l-0.00000000001);
	location.y=max(0.00000000001,location.y); location.y=min(location.y,w-0.00000000001);
	location.z=max(0.00000000001,location.z); location.z=min(location.z,h-0.00000000001);
	
}
