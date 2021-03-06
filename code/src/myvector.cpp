#ifndef _MYVECTOR_
#define _MYVECTOR_

#include <math.h>
class myvector
{
public :
  double x,y,z;
  myvector():x(0),y(0),z(0){}
  myvector(const myvector&a):x(a.x),y(a.y),z(a.z){}
  myvector(double x,double y,double z):x(x),y(y),z(z){}
  ~myvector() {}
  void set(double x,double y,double z)
  {
    this->x=x;
    this->y=y;
    this->z=z;
  }
  myvector& operator=(const myvector& a)
  {
    this->x=a.x; this->y=a.y; this->z=a.z; 
    return *this;
  }

  myvector& operator+=(double a)
  {
    this->x+=a; this->y+=a; this->z+=a;
    return *this;
  }

  myvector& operator-=(double a)
  {
    this->x-=a; this->y-=a; this->z-=a;
    return *this;
  }

  myvector& operator*=(double a)
  {
    this->x*=a; this->y*=a; this->z*=a;
    return *this;
  }

  myvector& operator/=(double a)
  {
    this->x/=a; this->y/=a; this->z/=a;
    return *this;
  }

  myvector& operator+=(const myvector& a)
  {
    this->x+=a.x; this->y+=a.y; this->z+=a.z;
    return  *this;
  }

  myvector& operator-=(const myvector& a)
  {
    this->x-=a.x; this->y-=a.y; this->z-=a.z;
    return  *this;
  }
	
  double dot(const myvector& a) 
  {
    return this->x*a.x+this->y*a.y+this->z*a.z;
  }
	
  double len_sq(void)
  {
    return x*x+y*y+z*z;
  }
	
  void normalize(void)
  {
    double len_sq=x*x+y*y+z*z;
    if(len_sq!=0.0) 
      {
	double len=sqrt(len_sq);
	x/=len; y/=len; z/=len;
      }
  }
};

inline myvector operator + (const myvector& a, const myvector& b)
{
  return myvector(a.x+b.x, a.y+b.y, a.z+b.z);
}

inline myvector operator - (const myvector& a, const myvector& b)
{
  return myvector(a.x-b.x, a.y-b.y, a.z-b.z);
}

inline myvector operator * (double s, const myvector& a)
{
  return myvector(s*a.x, s*a.y, s*a.z);
}

#endif
