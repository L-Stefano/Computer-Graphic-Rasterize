#pragma once
/*----------------------------------------------------------------
Copyright (C) 2017 Stefano. All rights reserved.
Vector2D: Addition, Subtract, Dot product, Scalar multiplication, Boolean Comparison, Normorlize, Length(norm),Distance of 2 2d vector.
implementation file: Vector2D.cpp
Vector3D: Addition, Subtract, Dot product, Scalar multiplication, Cross product,Boolean Comparison, Normorlize, Length(norm), Distance of 2 3d vector.
implementation file: Vector3D.cpp
RGB:
hVector:
image:
transform:
matrix:
----------------------------------------------------------------
svpng() is from https://github.com/miloyip/svpng, by Miloyip.
----------------------------------------------------------------
!
\file	    graphic.h
\brief      A header of Computer Graphic Math which inludes classes Vector2D Vector3D hVector RGB image transform etc.
\author     Stefano
\version    1.0.0.171201
\copyright
\sa         https://github.com/L-Stefano/Computer-Graphic-Rasterize/blob/master/header/graphic/graphic.h
\personal website		http://www.stefano.com.cn
!
----------------------------------------------------------------
updates:
----------------------------------------------------------------*/
#ifndef GRAPHIC_H
#define GRAPHIC_H
/*-------------------
headers
-------------------*/

#ifndef MATH
#include<math.h>
#include<cmath>
#include <iostream>
#define MATH
#endif // !MATH



/*-------------------
global constant
-------------------*/

#define BYTE unsigned char 
const unsigned W = 256;  //Weight
const unsigned H = 256;  //Height

/*-------------------
class Vector2D
-------------------*/

class Vector2D
{
public:
	double x, y;
	Vector2D();//Ĭ�Ϲ��캯��
	Vector2D(double, double);//���캯����ʼ������
	Vector2D(const Vector2D &);//�������캯��


	inline Vector2D & Vector2D::operator=(const Vector2D & rhs) { x = rhs.x, y = rhs.y; return *this; }//���ظ�ֵ
	inline Vector2D Vector2D::operator+(const Vector2D & rhs) { return Vector2D(this->x + rhs.x, this->y + rhs.y); }//�������
	inline Vector2D Vector2D::operator-(const Vector2D & rhs) { return Vector2D(this->x - rhs.x, this->y - rhs.y); }//�������
	inline Vector2D operator/(double a) const { return Vector2D(x / a, y / a); }//��������
	inline Vector2D operator*(double a) const { return Vector2D(x*a, y*a); }//�����˻�
	inline double Vector2D::operator*(const Vector2D & rhs) { return this->x * rhs.x + this->y * rhs.y; }//�������
	inline bool operator ==(const Vector2D &a)const { return x == a.x&&y == a.y; }//����==
	inline bool operator !=(const Vector2D &a) const { return x != a.x || y != a.y; }//����!=
	inline Vector2D &operator +=(const Vector2D &a) { x += a.x, y += a.y; return *this; }//����+=
	inline Vector2D &operator -=(const Vector2D &a) { x -= a.x, y -= a.y; return *this; }//����-=
	inline Vector2D &operator *=(double a) { x *= a, y *= a; return *this; }//����*=
	inline Vector2D &operator /=(double a) { double oneOverA = 1.0f / a; x *= oneOverA, y *= oneOverA; return *this; };//����/=

	void normorlize();	//��׼��
	double norm(void);//��ģ��
};
///������a������b֮��ľ��룬����double
inline double  distance(const Vector2D &a, const Vector2D &b)
{
	double dx = a.x - b.x;
	double dy = a.y - b.y;
	return sqrt(dx*dx + dy*dy);
}
///������ˣ����ڵ���һ�����غ���Ϊ�ҳˣ�
inline Vector2D operator *(float k, const Vector2D &v)
{
	return Vector2D(k*v.x, k*v.y);
}

/*-------------------
class Vector3D
-------------------*/

class Vector3D
{
public:
	double x, y, z;
	Vector3D();//Ĭ�Ϲ��캯��
	Vector3D(double, double, double);//���캯����ʼ������
	Vector3D(const Vector3D &);//�������캯��
	Vector3D(const Vector2D &);//�������캯��

	inline Vector3D & Vector3D::operator=(const Vector3D & rhs) { x = rhs.x, y = rhs.y, z = rhs.z; return *this; }//���ظ�ֵ

	inline Vector3D Vector3D::operator+(const Vector3D & rhs) { return Vector3D(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z); }//�������
	inline Vector3D Vector3D::operator-(const Vector3D & rhs) { return Vector3D(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z); }//�������
	inline Vector3D operator/(double a) const { return Vector3D(x / a, y / a, z / a); }//��������
	inline Vector3D operator*(double a) const { return Vector3D(x*a, y*a, z*a); }//�����˻�
	inline double Vector3D::operator*(const Vector3D & rhs) { return this->x * rhs.x + this->y * rhs.y + this->z*rhs.z; }//�������
	inline bool operator ==(const Vector3D &a)const { return x == a.x&&y == a.y&&z == a.z; }//����==
	inline bool operator !=(const Vector3D &a) const { return x != a.x || y != a.y || z != a.z; }//����!=
	inline Vector3D &operator +=(const Vector3D &a) { x += a.x, y += a.y, z += a.z; return *this; }//����+=
	inline Vector3D &operator -=(const Vector3D &a) { x -= a.x, y -= a.y, z -= a.z; return *this; }//����-=
	inline Vector3D &operator *=(double a) { x *= a, y *= a, z *= a;; return *this; }//����*=
	inline Vector3D &operator /=(double a) { double oneOverA = 1.0f / a; x *= oneOverA, y *= oneOverA, z *= oneOverA; return *this; };//����/=																					

	void normorlize();	//��׼��
	double norm(void);//��ģ��
};
///������a������b֮��ľ��룬����double
inline Vector3D crossProduct(const Vector3D&a, const Vector3D&b) { return Vector3D(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x); };//�������

inline double distance(const Vector3D &a, const Vector3D &b)
{
	double dx = a.x - b.x;
	double dy = a.y - b.y;
	double dz = a.z - b.z;
	return sqrt(dx*dx + dy*dy + dz*dz);
}
///������ˣ����ڵ���һ�����غ���Ϊ�ҳˣ�
inline Vector3D operator *(float k, const Vector3D &v)
{
	return Vector3D(k*v.x, k*v.y, k*v.z);
}

/*-------------------
class RGB
-------------------*/

class RGB
{
	public:
	BYTE r, g, b;
	RGB();
	RGB(BYTE, BYTE, BYTE);
	RGB(float, float, float);
	RGB(RGB&);
	inline RGB & operator=(const RGB & rhs) { r = rhs.r, g = rhs.g, b = rhs.b; return *this; }//���ظ�ֵ

	inline RGB operator+(const RGB& rhs) { return RGB((BYTE)(this->r + rhs.r), this->g + rhs.g, this->b + rhs.b); }//����+�����
	inline RGB operator-(const RGB& rhs) { return RGB((BYTE)(this->r - rhs.r), this->g - rhs.g, this->b - rhs.b); }//����+�����
	inline RGB operator/(double a) const { return RGB((BYTE)(this->r / a), this->g / a, this->b / a); }//��������
	inline RGB operator*(double a) const { return RGB((BYTE)(this->r *a), this->g*a, this->b*a); }//�����˻�
	inline RGB& operator +=(const RGB &rhs) { this->r += rhs.r, this->g += rhs.g, this->b += rhs.b; return *this; }//����+=
	inline RGB& operator -=(const RGB &rhs) { this->r += rhs.r, this->g += rhs.g, this->b += rhs.b; }//����-=
	inline RGB &operator *=(double a) { this->r *= a, this->g *= a, this->b *= a; return *this; }//����*=
	inline RGB &operator /=(double a) { double oneOverA = 1.0f / a; this->r *= oneOverA, this->g *= oneOverA, this->b *= oneOverA; return *this; }//����/=			
	inline void operator ()(BYTE r, BYTE g, BYTE b) { this->r = r, this->g = g, this->b = b; }//����()
};
///ֱ�Ӽ���alpha��Ϻ������ֵ
inline RGB alphaMix(RGB cf, RGB cb, double alpha)
{
	if (alpha >= 0.0f&&alpha <= 1.0f)
		return cf*alpha + cb*(1 - alpha);
	else
		throw "alphaȡֵ��ΧΪ0.0-1.0";

}
///������ˣ����ڵ���һ�����غ���Ϊ�ҳˣ�
inline RGB operator *(float k, const RGB &v)
{
	return RGB((BYTE)(k*v.r), (BYTE)(k*v.g), (BYTE)(k*v.b));
}

/*-------------------
class Rasterize
-------------------*/

class Rasterize
{
private:
	Rasterize operator=(const Rasterize &);
	Rasterize(Rasterize&);
	BYTE *rgb, *prgb;
public:
	Rasterize() = default;
	Rasterize(BYTE*,BYTE*);
	//image(image&);

	void setPixel(int , int , RGB );//���õ�������
	void setPixel(Vector2D, RGB);//���õ�������

	void generalLine(int , int , int , int , RGB );//һ�㷽�̻���ֱ�ߣ�����ȡ��
	void generalLine(Vector2D p1,Vector2D p2, RGB);//һ�㷽�̻���ֱ�ߣ�����ȡ��

	void midLine(int, int, int, int, RGB);	//������ʽֱ�߷��̵��е��㷨
	void midLine(Vector2D p1, Vector2D p2, RGB color);	//������ʽֱ�߷��̵��е��㷨

	void paraLine(int x1, int y1, int x2, int y2, RGB cp1, RGB cp2);//���ڲ�������ֱ�߻���
	void paraLine(Vector2D, Vector2D, RGB, RGB);//���ڲ�������ֱ�߻���

};
/*-------------------
class Triangle
-------------------*/

class Triangle
{
private:
	Vector3D p1, p2, p3,n; //�����ε�������ͷ�����
public:
	friend class Rasterize;
	Triangle(Vector3D p1, Vector3D p2, Vector3D p3);//���캯��
	Triangle(Vector2D p1, Vector2D p2, Vector2D p3);//���캯����ע�⣺����û��Ĭ�Ϲ��캯����

	Vector3D getBarycentriccoordinate(Vector2D);
	double getArea();

	
};


/*-------------------
class Image
-------------------*/
class Image
{
public:
	BYTE rgb[W * H * 3], *prgb = rgb;
	Image() = default;
	//image(image&);

	void exprortPNG(char * name);//���PNGͼƬ
};
#endif // !GRAPHIC_H