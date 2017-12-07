/*----------------------------------------------------------------
Copyright (C) 2017 Stefano. All rights reserved.

Implementation file of graphic.h: RGB.cpp
------------------------------------------------------------------

!
\file	    RGB.cpp
\brief      Implementation file of class RGB of graphic.h.
\author     Stefano
\version    1.0.0.171201
\copyright
\sa         https://github.com/L-Stefano/Computer-Graphic-Rasterize/blob/master/header/graphic/RGB.cpp
\personal website		http://www.stefano.com.cn
!
----------------------------------------------------------------
updates:
----------------------------------------------------------------*/
#include"graphic.h"

RGB::RGB() {};//Ĭ�Ϲ��캯��
RGB::RGB(BYTE r, BYTE g, BYTE b) :r(r), g(g), b(b) {};//���ع��캯����0-255����
RGB::RGB(float r, float g, float b) //���ع��캯����0.0f-1.0f������
{
	if (r > 1.0f || g > 1.0f || b > 1.0f)
		throw "The range of value is 0.0-1.0";
	else
	{
		RGB::r = (BYTE)(255 * r + 0.5);
		RGB::g = (BYTE)(255 * g + 0.5);
		RGB::b = (BYTE)(255 * b + 0.5);
	}
};
RGB::RGB(RGB&a) :r(a.r), g(a.g), b(a.b) {}

;//���ؿ������캯��

