/*----------------------------------------------------------------
Copyright (C) 2017 Stefano. All rights reserved.

Implementation file of graphic.h: Rasterize.cpp
------------------------------------------------------------------

!
\file	    Rasterize.cpp
\brief      Implementation file of class Rasterize of graphic.h.
\author     Stefano
\version    1.0.0.171201
\copyright
\sa         https://github.com/L-Stefano/Computer-Graphic-Rasterize/blob/master/header/graphic/Rasterize.cpp
\personal website		http://www.stefano.com.cn
!
----------------------------------------------------------------
updates:
----------------------------------------------------------------*/
#include"graphic.h"


//
//void Rasterize::setWidth(int width) { this->Width = width; }//设置图片分辨率的宽
//void Rasterize::setHeight(int height) { this->Height = height; }//设置图片分辨率的高
//
//void Rasterize::replaceTo
//{
//	unsigned long long total = 0;
//	for (img=&img[0]; total < Width*Height; img++,total++)
//	{
//		*p++ = img->r;  /* R */
//		*p++ = img->g;  /* G */
//		*p++ = img->b;  /* B */
//	}
//}
//
//Rasterize::Rasterize(const int W, const int H):Width(W),Height(H)
//{
//}
//
//Rasterize::~Rasterize()
//{
//}

//
//void Rasterize::setWidth(int width) { this->Width = width; }//设置图片分辨率的宽
//void Rasterize::setHeight(int height) { this->Height = height; }//设置图片分辨率的高
//
//void Rasterize::replaceToByteArr()
//{
//	unsigned long long total = 0;
//	for (img=&img[0]; total < Width*Height; img++,total++)
//	{
//		*p++ = img->r;  /* R */
//		*p++ = img->g;  /* G */
//		*p++ = img->b;  /* B */
//	}
//}
//
//Rasterize::Rasterize(const int W, const int H):Width(W),Height(H)
//{
//}
//
//Rasterize::~Rasterize()
//{
//}

/*-------------------
Set single pixel
-------------------*/

Rasterize Rasterize::operator=(const Rasterize &) { return Rasterize(); }

Rasterize::Rasterize(BYTE *rgb, BYTE *prgb)
{
	this->rgb = rgb;
	this->prgb = prgb;
}

void Rasterize::setPixel(int x, int y, RGB color)  //x and y are coordinate which you want to draw.
{
	int index = abs((int)(3 * ((W*(y+1)) - (W - x - 1) - 1))); //To find the index of coordinate which need to draw.
	prgb = &rgb[index];  //Point the pointer to the previous of index.
	*prgb++ = color.r;  /* R */
	*prgb++ = color.g;  /* G */
	*prgb++ = color.b;  /* B */
}
void Rasterize::setPixel(Vector2D p, RGB color)  //x and y are coordinate which you want to draw.
{
	int index = abs((int)(3 * ((W*(p.y+1)) - (W - p.x-1) - 1)));  //To find the index of coordinate which need to draw.
	prgb = &rgb[index];  //Point the pointer to the previous of index.
	*prgb++ = color.r;  /* R */
	*prgb++ = color.g;  /* G */
	*prgb++ = color.b;  /* B */
}

/*-------------------
Using general line equation to draw a single line.
-------------------*/

void Rasterize::generalLine(int x1, int y1, int x2, int y2, RGB color)  //Using general form y=kx+b to rasterize a line. Note that x1<=x2 y1<=y2.
{
	if (x1 > x2) //if x1>x2, swap p1 and p2.
	{
		std::swap(x1, x2);
		std::swap(y1, y2);
	}
	else if (x1 == x2)
		for (int y = y1; y <= y2; y++)
			setPixel(Vector2D(x1, y), color);

	double k = (y2 - y1)*1.0 / (x2 - x1);  //Find the Slope
	double b = (y2*x1 - y1*x2) / (x2 - x1);  //Find the Intercept 
	int y = y1, x = x1;
	if (k <= 0)
	{
		for (int x = x1; x < x2; x++)
		{
			y = (int)(k*x*1.0 - b);   //For y=kx, plug each 'kx' into y. 
									  //Due to the PNG's coded format, of which y-axis is contrary to the standard Y-axis, the 'y=kx-b' is compliant.
			setPixel(x, (int)(y + 0.5), color);  //The intent to integer y+0.5 is make the line more close to where it is.(if y>((yi+1-yi)/2)), equals yi+1, otherwise equals yi)
		}
	}
	else if (k > 0)
	{
		for (int y = y1; y < y2; y++)
		{
			x = (int)((y + b) / k);   //For y=kx, plug each 'kx' into y. 
									  //Due to the PNG's coded format, of which y-axis is contrary to the standard Y-axis, the 'y=kx-b' is compliant.
			setPixel((int)(x + 0.5), y, color);  //x+0.5 ditto
		}
	}

}
void Rasterize::generalLine(Vector2D p1, Vector2D p2, RGB color)
{
	if (p1.x > p2.x) //if p1.x>p2.x, swap p1 and p2.
	{
		std::swap(p1.x, p2.x);
		std::swap(p1.y, p2.y);
	}
	else if (p1.x ==p2.x)
		for (int y = p1.y; y <= p2.y; y++)
			setPixel(Vector2D(p1.x, y), color);

	double k = (p2.y - p1.y)*1.0 / (p2.x - p1.x);  //Find the Slope
	double b = (p2.y*p1.x - p1.y*p2.x) / (p2.x - p1.x);  //Find the Intercept 
	int y = p1.y, x = p1.x;
	if (k <= 0)
	{
		for (int x = p1.x; x < p2.x; x++)
		{
			y = (int)(k*x*1.0 - b);   //For y=kx, plug each 'kx' into y. 
									  //Due to the PNG's coded format, of which y-axis is contrary to the standard Y-axis, the 'y=kx-b' is compliant.
			setPixel(x, (int)(y + 0.5), color);  //The intent to integer y+0.5 is make the line more close to where it is.(if y>((yi+1-yi)/2)), equals yi+1, otherwise equals yi)
		}
	}
	else if (k > 0)
	{
		for (int y = p1.y; y < p2.y; y++)
		{
			x = (int)((y + b) / k);   //For y=kx, plug each 'kx' into y. 
									  //Due to the PNG's coded format, of which y-axis is contrary to the standard Y-axis, the 'y=kx-b' is compliant.
			setPixel((int)(x + 0.5), y, color);  //x+0.5 ditto
		}
	}

}

/*-------------------
Using mid line algorithm to draw a single line.
-------------------*/

void Rasterize::midLine(int x1, int y1, int x2, int y2, RGB color)
{
	if (x1 > x2) //if x1>x2, swap p1 and p2.
	{
		std::swap(x1, x2);
		std::swap(y1, y2);
	}
	if (x1 == x2)
		for (int y = y1; y <= y2; y++)
			setPixel(Vector2D(x1, y), color);
	else if (x1 != x2)
	{
		double k = (-y2 + y1)*1.0 / (x2 - x1);  //Find the Slope
		int y, x;

		if (k >= 0 && k <= 1)
		{
			x = x1, y = y1;
			for (x; x <= x2; x++)
			{
				setPixel(x, y, color);
				if ((2 * (y1 - y2)*(x + 1) + (x2 - x1)*(2 * y - 1) + 2 * x1*y2 - 2 * x2*y1) >= 0)
					y = y - 1;
			}
		}
		else if (k < 0 && k >= -1)
		{
			x = x1, y = y1;
			for (x; x <= x2; x++)
			{
				setPixel(x, y, color);
				if ((2 * (y1 - y2)*(x + 1) + (x2 - x1)*(2 * y + 1) + 2 * x1*y2 - 2 * x2*y1) <= 0)
					y = y + 1;
			}

		}
		else if (k > 1)
		{
			x = x2; y = y2;
			for (y; y <= y1; y++)
			{
				setPixel(x, y, color);
				if (((y1 - y2)*(2 * x - 1) + 2 * (x2 - x1)*(y + 1) + 2 * x1*y2 - 2 * x2*y1) >= 0)
					x = x - 1;
			}
		}
		else if (k < -1)
		{
			x = x1; y = y1;
			for (y; y <= y2; y++)
			{
				setPixel(x, y, color);
				if (((y1 - y2)*(2 * x + 1) + 2 * (x2 - x1)*(y + 1) + 2 * x1*y2 - 2 * x2*y1) >= 0)
					x = x + 1;

			}


			//if (k >= 0 && k < 1)
			//{
			//	int d = 2 * (y1 - y2)*(x1 + 1) + (x2 - x1)*(2 * y1 + 1) + 2 * x1*y2 - 2 * x2*y1;
			//	for (x; x <= x2; x++)
			//	{
			//		setPixel(x, y, color);
			//		if (d < 0)
			//		{
			//			y = y + 1;
			//			d = d + 2 * (x2 - x1) + 2 * (y1 - y2);
			//		}
			//		else
			//			d = d + 2 * (y1 - y2);
			//	}
			//}
			//else
			//	throw "k";
		}
	}
}
void Rasterize::midLine(Vector2D p1, Vector2D p2, RGB color)
{
	if (p1.x > p2.x) //if p1.x>p2.x, swap p1 and p2.
	{
		std::swap(p1.x, p2.x);
		std::swap(p1.y, p2.y);
	}
	if (p1.x == p2.x)
		for (int y = p1.y; y <= p2.y; y++)
			setPixel(Vector2D(p1.x, y), color);
	else if (p1.x != p2.x)
	{
		double k = (-p2.y + p1.y)*1.0 / (p2.x - p1.x);  //Find the Slope
		int y, x;

		if (k >= 0 && k <= 1)
		{
			x = p1.x, y = p1.y;
			for (x; x <= p2.x; x++)
			{
				setPixel(x, y, color);
				if ((2 * (p1.y - p2.y)*(x + 1) + (p2.x - p1.x)*(2 * y - 1) + 2 * p1.x*p2.y - 2 * p2.x*p1.y) >= 0)
					y = y - 1;
			}
		}
		else if (k < 0 && k >= -1)
		{
			x = p1.x, y = p1.y;
			for (x; x <= p2.x; x++)
			{
				setPixel(x, y, color);
				if ((2 * (p1.y - p2.y)*(x + 1) + (p2.x - p1.x)*(2 * y + 1) + 2 * p1.x*p2.y - 2 * p2.x*p1.y) <= 0)
					y = y + 1;
			}

		}
		else if (k > 1)
		{
			x = p2.x; y = p2.y;
			for (y; y <= p1.y; y++)
			{
				setPixel(x, y, color);
				if (((p1.y - p2.y)*(2 * x - 1) + 2 * (p2.x - p1.x)*(y + 1) + 2 * p1.x*p2.y - 2 * p2.x*p1.y) >= 0)
					x = x - 1;
			}
		}
		else if (k < -1)
		{
			x = p1.x; y = p1.y;
			for (y; y <= p2.y; y++)
			{
				setPixel(x, y, color);
				if (((p1.y - p2.y)*(2 * x + 1) + 2 * (p2.x - p1.x)*(y + 1) + 2 * p1.x*p2.y - 2 * p2.x*p1.y) >= 0)
					x = x + 1;

			}


		}
	}
}

/*-------------------
Using parameter equation to draw a single line.
-------------------*/
void Rasterize::paraLine(int x1,int y1, int x2,int y2, RGB cp1, RGB cp2)
{
	double k = (-y2 + y1)*1.0 / (x2 - x1);  //Find the Slope
	RGB resultRGB;
	if (k >= -1 && k <= 1)
	{
		if (x1 > x2) //if x1>x2, swap p1 and p2.
		{
			std::swap(x1, x2);
			std::swap(y1, y2);
		}
		for (int x = x1, y = y1; x <= x2; x++)
		{
			double t = (x - x1)*1.0f / (x2 - x1);
			y = y1 - t*(y1 - y2);
			resultRGB = (1 - t)*cp1 + t*cp2;
			setPixel(x, (int)(y + 0.5), resultRGB);
		}
	}
	if (k > 1 || k < -1)
	{
		if (y1 > y2) //if x1>x2, swap p1 and p2.
		{
			std::swap(x1, x2);
			std::swap(y1, y2);
		}
		for (int x = x1, y = y1; y <= y2; y++)
		{
			double t = (y - y1)*1.0f / (y2 - y1);
			x = x1 - t*(x1 - x2);
			resultRGB = (1 - t)*cp1 + t*cp2;
			setPixel((int)(x + 0.5), y, resultRGB);
		}
	}
}
void Rasterize::paraLine(Vector2D p1, Vector2D p2, RGB cp1, RGB cp2)
{
	double k = (-p2.y + p1.y)*1.0 / (p2.x - p1.x);  //Find the Slope
	RGB resultRGB;
	if (k >= -1 && k <= 1)
	{
		if (p1.x > p2.x)
			std::swap(p1, p2);
		for (int x = p1.x, y = p1.y; x <= p2.x; x++)
		{
			double t = (x - p1.x)*1.0f / (p2.x - p1.x);
			y = p1.y - t*(p1.y - p2.y);
			resultRGB = (1 - t)*cp1 + t*cp2;
			setPixel(x, (int)(y + 0.5),resultRGB);
		}
	}
	if (k > 1 || k < -1)
	{
		if (p1.y > p2.y)
			std::swap(p1, p2);
		for (int x = p1.x, y = p1.y; y <= p2.y; y++)
		{
			double t = (y - p1.y)*1.0f / (p2.y - p1.y);
			x = p1.x - t*(p1.x- p2.x);
			resultRGB = (1 - t)*cp1 + t*cp2;
			setPixel((int)(x+0.5),y, resultRGB);
		}
	}
}
