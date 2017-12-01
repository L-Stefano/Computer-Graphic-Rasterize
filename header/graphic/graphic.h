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

#ifndef MATH
#include<math.h>
#include<cmath>
#define MATH
#endif // !MATH

//class Vector2D
	class Vector2D
	{
	public:
		double x, y;
		Vector2D();//默认构造函数
		Vector2D(double, double);//构造函数初始化分量
		Vector2D(const Vector2D & a);//拷贝构造函数

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
		float dx = a.x - b.x;
		float dy = a.y - b.y;
		return sqrt(dx*dx + dy*dy);
	}
	///标量左乘（类内的另一个重载函数为右乘）
	inline Vector2D operator *(float k, const Vector2D &v)
	{
		return Vector2D(k*v.x, k*v.y);
	}


//class Vector3D

	class Vector3D
	{
	public:
		double x, y, z;
		Vector3D();//默认构造函数
		Vector3D(double, double, double);//构造函数初始化分量
		Vector3D(const Vector3D & a);//拷贝构造函数

		inline Vector3D & Vector3D::operator=(const Vector3D & rhs) { x = rhs.x, y = rhs.y,z=rhs.z; return *this; }//重载赋值
		inline Vector3D Vector3D::operator+(const Vector3D & rhs) { return Vector3D(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z); }//向量相加
		inline Vector3D Vector3D::operator-(const Vector3D & rhs) { return Vector3D(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z); }//向量相减
		inline Vector3D operator/(double a) const { return Vector3D(x / a, y / a, z / a); }//标量除法
		inline Vector3D operator*(double a) const { return Vector3D(x*a, y*a, z*a); }//标量乘积
		inline double Vector3D::operator*(const Vector3D & rhs) { return this->x * rhs.x + this->y * rhs.y+this->z*rhs.z; }//向量点积
		inline bool operator ==(const Vector3D &a)const { return x == a.x&&y == a.y&&z == a.z; }//重载==
		inline bool operator !=(const Vector3D &a) const { return x != a.x || y != a.y || z!=a.z; }//重载!=
		inline Vector3D &operator +=(const Vector3D &a) { x += a.x, y += a.y, z += a.z; return *this; }//重载+=
		inline Vector3D &operator -=(const Vector3D &a) { x -= a.x, y -= a.y, z -= a.z; return *this; }//重载-=
		inline Vector3D &operator *=(double a) { x *= a, y *= a, z *= a;; return *this; }//重载*=
		inline Vector3D &operator /=(double a) { double oneOverA = 1.0f / a; x *= oneOverA, y *= oneOverA, z *= oneOverA; return *this; };//重载/=																					
		inline Vector3D crossProduct(const Vector3D&a, const Vector3D&b) {return Vector3D(a.y*b.z - a.z*b.y,a.z*b.x - a.x*b.z,a.x*b.y - a.y*b.x);};//向量叉积
																														   
		void normorlize();	//标准化
		double norm(void);//求模长
	};
	///求向量a与向量b之间的距离，返回double
	inline double  distance(const Vector3D &a, const Vector3D &b)
	{
		double dx = a.x - b.x;
		double dy = a.y - b.y;
		double dz = a.z - b.z;
		return sqrt(dx*dx + dy*dy+dz*dz);
	}
	///标量左乘（类内的另一个重载函数为右乘）
	inline Vector3D operator *(float k, const Vector3D &v)
	{
		return Vector3D(k*v.x, k*v.y, k*v.z);
	}


#endif // !GRAPHIC_H
