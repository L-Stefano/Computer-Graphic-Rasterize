/*----------------------------------------------------------------
Copyright (C) 2017 Stefano. All rights reserved.

generalLine(), accomplished the funchtion which could draw a single line.
With the general form y=kx+b(In PNG is 'y=kx-b').
Due to the complexity of multiplication 'kx', this method is not advocating use.

svpng() is from https://github.com/miloyip/svpng, by Miloyip.

! 
\file	    generalLine.cpp
\brief      generalLine() is a C++ function for drawing a line with the general form y=kx+b.
\author     Stefano
\version    1.0.3.171108
\copyright
\sa         https://github.com/L-Stefano/Computer-Graphic-Rasterize/blob/master/generalLine.cpp
!
----------------------------------------------------------------
In addition, it is necessary to note that the pixel distribution of the X coordinate axis is uniform, but it is not the same for the Y axis. (Solved in 1.0.3.171108)
----------------------------------------------------------------*/

#include "svpng.h"
#include <Windows.h>
#include <math.h>
const unsigned W = 256;  //Weight
const unsigned H = 256;  //Height
unsigned char rgb[W * H * 3], *p = rgb;

struct color { unsigned char R, G, B; };

void setPixel(int x, int y,color color)  //x and y are coordinate which you want to draw.
{
	int index = abs((int)(3 * ((W*y) - (W - x) - 1)));  //To find the index of coordinate which need to draw.
	p = &rgb[index];  //Point the pointer to the previous of index.
	*p++ = color.R;  /* R */
	*p++ = color.G;  /* G */
	*p++ = color.B;  /* B */
}

void generalLine(int x1, int y1, int x2, int y2,color color)  //Using general form y=kx+b to rasterize a line. Note that x1<=x2 y1<=y2.
{
	double k = (y2 - y1)*1.0 / (x2 - x1);  //Find the Slope
	double b = (y2*x1 - y1*x2) / (x2 - x1);  //Find the Intercept 
	int y = y1, x = x1;
	if (k <= 0)
	{
		for (int x = x1; x < x2; x++)
		{
			y = (int)(k*x*1.0 - b);   //For y=kx, plug each 'kx' into y. 
										   //Due to the PNG's coded format, of which y-axis is contrary to the standard Y-axis, the 'y=kx-b' is compliant.
			setPixel(x, (int)(y+0.5), color);  //The intent to integer y+0.5 is make the line more close to where it is.(if y>((yi+1-yi)/2)), equals yi+1, otherwise equals yi)
		}
	}
	else if (k > 0)
	{
		for (int y = y1; y < y2; y++)
		{
			x = (int)((y+b)/k);   //For y=kx, plug each 'kx' into y. 
									  //Due to the PNG's coded format, of which y-axis is contrary to the standard Y-axis, the 'y=kx-b' is compliant.
			setPixel((int)(x + 0.5), y, color);  //x+0.5 ditto
		}
	}

}

void main(void) {
	FILE *fp = fopen("rgb.png", "wb");
	unsigned x, y;
	color RGB{255,255,255};

	for (x = 0; x < 256; x++)
		for (y = 0; y < 256 ; y++)
		{
			*p++ = 0;
			*p++ = 0;
			*p++ = 0;
		}

	generalLine(10, 200, 200, 100, RGB);
	generalLine(42, 41, 122, 200, RGB);

	svpng(fp, W, H, rgb, 0);
	fclose(fp);
}
