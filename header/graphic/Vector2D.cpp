/*----------------------------------------------------------------
Copyright (C) 2017 Stefano. All rights reserved.

Implementation file of graphic.h: Vector2D.cpp
------------------------------------------------------------------

!
\file	    Vector2D.cpp
\brief      Implementation file of class Vector2D of graphic.h.
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
Vector2D::Vector2D(double x, double y): x(x), y(y) {}//���캯����ֵ
Vector2D::Vector2D(const Vector2D &a) : x(a.x), y(a.y) {}

//�������캯��
double Vector2D::norm(void)//��ģ
{
	return sqrt((pow((this->x), 2) + (pow((this->y), 2))));
}
void Vector2D::normorlize()//��׼��
{
	double length = this->norm();
	if (length > 0.0f)
	{
		this->x = this->x / length;
		this->y = this->y / length;
	}
}
