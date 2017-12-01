/*----------------------------------------------------------------
Copyright (C) 2017 Stefano. All rights reserved.

Implementation file of graphic.h: Vector3D.cpp
------------------------------------------------------------------

!
\file	    graphic.h
\brief      Implementation file of graphic.h: Vector3D.cpp
\author     Stefano
\version    1.0.0.171201
\copyright
\sa         https://github.com/L-Stefano/Computer-Graphic-Rasterize/blob/master/header/graphic/Vector3D.cpp
\personal website		http://www.stefano.com.cn
!
----------------------------------------------------------------
updates:
----------------------------------------------------------------*/

#include "graphic.h"
Vector3D::Vector3D() {}//默认构造函数
Vector3D::Vector3D(double a, double b, double c):x(a),y(b),z(c){}//构造函数
Vector3D::Vector3D(const Vector3D & a) : x(a.x), y(a.y), z(a.z) {}//拷贝构造函数
void Vector3D::normorlize()//标准化
{
	double length = this->norm();
	if (length > 0.0f)
	{
		this->x = this->x / length;
		this->y = this->y / length;
		this->z = this->z / length;
	}
}
double Vector3D::norm(void)//求模
{
	return sqrt((pow((this->x), 2) + pow((this->y), 2) + pow((this->z), 2)));
}
