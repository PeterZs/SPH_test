#ifndef _VERTEX_DATA_
#define _VERTEX_DATA_

#include "myvector.h"

class vertex_data
{
public:
	myvector vertex;
	myvector normal_vector; //������
	double  csComponent; //��ɫ�����
	double cs; //�ܵ���ɫ�����
	int mark; //�����жϱ���ֵ����С
	vertex_data();
	~vertex_data();

};

#endif