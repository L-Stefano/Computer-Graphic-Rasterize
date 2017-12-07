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
	Vector2D();//默认构造函数
	Vector2D(double, double);//构造函数初始化分量
	Vector2D(const Vector2D &);//拷贝构造函数


	inline Vector2D & Vector2D::operator=(const Vector2D & rhs) { x = rhs.x, y = rhs.y; return *this; }//重载赋值
	inline Vector2D Vector2D::operator+(const Vector2D & rhs) { return Vector2D(this->x + rhs.x, this->y + rhs.y); }//向量相加
	inline Vector2D Vector2D::operator-(const Vector2D & rhs) { return Vector2D(this->x - rhs.x, this->y - rhs.y); }//向量相减
	inline Vector2D operator/(double a) const { return Vector2D(x / a, y / a); }//标量除法
	inline Vector2D operator*(double a) const { return Vector2D(x*a, y*a); }//标量乘积
	inline double Vector2D::operator*(const Vector2D & rhs) { return this->x * rhs.x + this->y * rhs.y; }//向量点积
	inline bool operator ==(const Vector2D &a)const { return x == a.x&&y == a.y; }//重载==
	inline bool operator !=(const Vector2D &a) const { return x != a.x || y != a.y; }//重载!=
	inline Vector2D &operator +=(const Vector2D &a) { x += a.x, y += a.y; return *this; }//重载+=
	inline Vector2D &operator -=(const Vector2D &a) { x -= a.x, y -= a.y; return *this; }//重载-=
	inline Vector2D &operator *=(double a) { x *= a, y *= a; return *this; }//重载*=
	inline Vector2D &operator /=(double a) { double oneOverA = 1.0f / a; x *= oneOverA, y *= oneOverA; return *this; };//重载/=

	void normorlize();	//标准化
	double norm(void);//求模长
};
///求向量a与向量b之间的距离，返回double
inline double  distance(const Vector2D &a, const Vector2D &b)
{
	double dx = a.x - b.x;
	double dy = a.y - b.y;
	return sqrt(dx*dx + dy*dy);
}
///标量左乘（类内的另一个重载函数为右乘）
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
	Vector3D();//默认构造函数
	Vector3D(double, double, double);//构造函数初始化分量
	Vector3D(const Vector3D &);//拷贝构造函数
	Vector3D(const Vector2D &);//拷贝构造函数

	inline Vector3D & Vector3D::operator=(const Vector3D & rhs) { x = rhs.x, y = rhs.y, z = rhs.z; return *this; }//重载赋值

	inline Vector3D Vector3D::operator+(const Vector3D & rhs) { return Vector3D(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z); }//向量相加
	inline Vector3D Vector3D::operator-(const Vector3D & rhs) { return Vector3D(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z); }//向量相减
	inline Vector3D operator/(double a) const { return Vector3D(x / a, y / a, z / a); }//标量除法
	inline Vector3D operator*(double a) const { return Vector3D(x*a, y*a, z*a); }//标量乘积
	inline double Vector3D::operator*(const Vector3D & rhs) { return this->x * rhs.x + this->y * rhs.y + this->z*rhs.z; }//向量点积
	inline bool operator ==(const Vector3D &a)const { return x == a.x&&y == a.y&&z == a.z; }//重载==
	inline bool operator !=(const Vector3D &a) const { return x != a.x || y != a.y || z != a.z; }//重载!=
	inline Vector3D &operator +=(const Vector3D &a) { x += a.x, y += a.y, z += a.z; return *this; }//重载+=
	inline Vector3D &operator -=(const Vector3D &a) { x -= a.x, y -= a.y, z -= a.z; return *this; }//重载-=
	inline Vector3D &operator *=(double a) { x *= a, y *= a, z *= a;; return *this; }//重载*=
	inline Vector3D &operator /=(double a) { double oneOverA = 1.0f / a; x *= oneOverA, y *= oneOverA, z *= oneOverA; return *this; };//重载/=																					

	void normorlize();	//标准化
	double norm(void);//求模长
};
///求向量a与向量b之间的距离，返回double
inline Vector3D crossProduct(const Vector3D&a, const Vector3D&b) { return Vector3D(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x); };//向量叉积

inline double distance(const Vector3D &a, const Vector3D &b)
{
	double dx = a.x - b.x;
	double dy = a.y - b.y;
	double dz = a.z - b.z;
	return sqrt(dx*dx + dy*dy + dz*dz);
}
///标量左乘（类内的另一个重载函数为右乘）
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
	inline RGB & operator=(const RGB & rhs) { r = rhs.r, g = rhs.g, b = rhs.b; return *this; }//重载赋值

	inline RGB operator+(const RGB& rhs) { return RGB((BYTE)(this->r + rhs.r), this->g + rhs.g, this->b + rhs.b); }//重载+运算符
	inline RGB operator-(const RGB& rhs) { return RGB((BYTE)(this->r - rhs.r), this->g - rhs.g, this->b - rhs.b); }//重载+运算符
	inline RGB operator/(double a) const { return RGB((BYTE)(this->r / a), this->g / a, this->b / a); }//标量除法
	inline RGB operator*(double a) const { return RGB((BYTE)(this->r *a), this->g*a, this->b*a); }//标量乘积
	inline RGB& operator +=(const RGB &rhs) { this->r += rhs.r, this->g += rhs.g, this->b += rhs.b; return *this; }//重载+=
	inline RGB& operator -=(const RGB &rhs) { this->r += rhs.r, this->g += rhs.g, this->b += rhs.b; }//重载-=
	inline RGB &operator *=(double a) { this->r *= a, this->g *= a, this->b *= a; return *this; }//重载*=
	inline RGB &operator /=(double a) { double oneOverA = 1.0f / a; this->r *= oneOverA, this->g *= oneOverA, this->b *= oneOverA; return *this; }//重载/=			
	inline void operator ()(BYTE r, BYTE g, BYTE b) { this->r = r, this->g = g, this->b = b; }//重载()
};
///直接计算alpha混合后的像素值
inline RGB alphaMix(RGB cf, RGB cb, double alpha)
{
	if (alpha >= 0.0f&&alpha <= 1.0f)
		return cf*alpha + cb*(1 - alpha);
	else
		throw "alpha取值范围为0.0-1.0";

}
///标量左乘（类内的另一个重载函数为右乘）
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

	void setPixel(int , int , RGB );//设置单点像素
	void setPixel(Vector2D, RGB);//设置单点像素

	void generalLine(int , int , int , int , RGB );//一般方程绘制直线（不可取）
	void generalLine(Vector2D p1,Vector2D p2, RGB);//一般方程绘制直线（不可取）

	void midLine(int, int, int, int, RGB);	//基于隐式直线方程的中点算法
	void midLine(Vector2D p1, Vector2D p2, RGB color);	//基于隐式直线方程的中点算法

	void paraLine(int x1, int y1, int x2, int y2, RGB cp1, RGB cp2);//基于参数方程直线绘制
	void paraLine(Vector2D, Vector2D, RGB, RGB);//基于参数方程直线绘制

};
/*-------------------
class Triangle
-------------------*/

class Triangle
{
private:
	Vector3D p1, p2, p3,n; //三角形的三个点和法向量
public:
	friend class Rasterize;
	Triangle(Vector3D p1, Vector3D p2, Vector3D p3);//构造函数
	Triangle(Vector2D p1, Vector2D p2, Vector2D p3);//构造函数（注意：本类没有默认构造函数）

	Vector3D getBarycentriCcoordinate(Vector2D);//获取重心坐标系的重心坐标
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

	void exprortPNG(char * name);//输出PNG图片
};
#endif // !GRAPHIC_H
