#ifndef _PARTICLE_
#define _PARTICLE_

#include "myvector.h"

class particle 
{
public:
	myvector location;  //λ��
	myvector speed; //�ٶ�
	myvector speed_equal; // �˿��ٶȺ���һ���ٶȵľ�ֵ
	myvector a_sp; //���ٶ�
	double density; //�ܶ�
	double pressure; //ѹ��
	
	particle();
	particle(double x,double y,double z);
	particle(const particle& part); //�������캯������������const���ʵ�ͬ������
	~particle();
	
	void drawParticle();
	void drawParticle(double d_max,double d_min);
	
	void reSet();
	void calPressure();
	void calLoactionAndSpeed(double tim,double l,double w,double h);
};

#endif

