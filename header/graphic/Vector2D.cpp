/*----------------------------------------------------------------
Copyright (C) 2017 Stefano. All rights reserved.

Implementation file of graphic.h: Vector2D.cpp
------------------------------------------------------------------

!
\file	    graphic.h
\brief      Implementation file of graphic.h: Vector2D.cpp
\author     Stefano
\version    1.0.0.171201
\copyright
\sa         https://github.com/L-Stefano/Computer-Graphic-Rasterize/blob/master/header/graphic/Vector2D.cpp
\personal website		http://www.stefano.com.cn
!
----------------------------------------------------------------
updates:
----------------------------------------------------------------*/

#include "graphic.h"
Vector2D::Vector2D(){}
Vector2D::Vector2D(double x, double y): x(x), y(y) {}//构造函数传值
Vector2D::Vector2D(const Vector2D & a) : x(a.x), y(a.y) {}//拷贝构造函数
double Vector2D::norm(void)//求模
{
	return sqrt((pow((this->x), 2) + (pow((this->y), 2))));
}
void Vector2D::normorlize()//标准化
{
	double length = this->norm();
	if (length > 0.0f)
	{
		this->x = this->x / length;
		this->y = this->y / length;
	}
}
