#ifndef _PHYSIC_
#define _PHYSIC_

#include "myvector.h"
class physic
{
public:
	static const double stiffness; //ǽ��Ӳ��ϵ��
	static const double dampening; //ǽ�Ļس�ϵ��
	static const  double speedLimiting; //�ٶ�����
	static const double r_smoothCore; //�⻬�˰뾶   
	static const double staticDensity; //ˮ�ľ�̬�ܶ�  
	static const double staticViscosity; //ճ��ϵ��   
	static const double gasK; //�������巽�̳���K     
	static const double particleMass; //��������    
	static const myvector a_gravity; //�������ٶ�
	static const double pi;
    static const double color[7][3]; //�ʺ���ɫֵ
	static const double  threshold; //��ֵ�����ж��Ƿ���ˮ�� trick

};

#endif