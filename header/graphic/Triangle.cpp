/*----------------------------------------------------------------
Copyright (C) 2017 Stefano. All rights reserved.

Implementation file of graphic.h: Triangle.cpp
------------------------------------------------------------------

!
\file	    Triangle.cpp
\brief      Implementation file of class Triangle of graphic.h.
\author     Stefano
\version    1.0.0.171201
\copyright
\sa         https://github.com/L-Stefano/Computer-Graphic-Rasterize/blob/master/header/graphic/Triangle.cpp
\personal website		http://www.stefano.com.cn
!
----------------------------------------------------------------
updates:
----------------------------------------------------------------*/

#include "graphic.h"

Triangle::Triangle(Vector3D p1, Vector3D p2, Vector3D p3) :p1(p1), p2(p2), p3(p3) 
{
	n = crossProduct((p1 - p2), (p3 - p2));
};
Triangle::Triangle(Vector2D p1, Vector2D p2, Vector2D p3) : p1(p1), p2(p2), p3(p3) 
{
	n = crossProduct((p1 - p2), (p3 - p2));
}
Vector3D Triangle::getBarycentriccoordinate(Vector2D a)
{
	Vector3D result;
	double f01= (p1.y - p2.y)*a.x + (p2.x - p1.x)*a.y + p1.x*p2.y - p2.x*p1.y;
	double f12 = (p2.y - p3.y)*a.x + (p3.x - p2.x)*a.y + p2.x*p3.y - p3.x*p2.y;
	double f20 = (p3.y - p1.y)*a.x + (p1.x - p3.x)*a.y + p3.x*p1.y - p1.x*p3.y;
	double f01x3y3 = (p1.y - p2.y)*p3.x + (p2.x - p1.x)*p3.y + p1.x*p2.y - p2.x*p1.y;
	double f12x1y1 = (p2.y - p3.y)*p1.x + (p3.x - p2.x)*p1.y + p2.x*p3.y - p3.x*p2.y;
	double f20x2y2 = (p3.y - p1.y)*p2.x + (p1.x - p3.x)*p2.y + p3.x*p1.y - p1.x*p3.y;
	result.x = f12 / f12x1y1;
	result.y = f20 / f20x2y2;
	result.z = f01 / f01x3y3;
	return result;
}
double Triangle::getArea()
{
	double s = abs(0.5*(crossProduct((p1 - p2), (p3 - p2))).norm());
	return s;
}
;

