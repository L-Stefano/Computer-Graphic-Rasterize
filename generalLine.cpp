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
\version    1.0.2.171107
\copyright
\sa         https://github.com/L-Stefano/Computer-Graphic-Rasterize/blob/master/generalLine.cpp
!
----------------------------------------------------------------
In addition, it is necessary to note that the pixel distribution of the X coordinate axis is uniform, 
but it is not the same for the Y axis.
----------------------------------------------------------------*/

#include "svpng.h"
#include <math.h>
const unsigned W = 256;  //Weight
const unsigned H = 256;  //Height
unsigned char rgb[W * H * 3], *p = rgb;

void setPixel(int x, int y)  //x and y are coordinate which you want to draw.
{
	int index = abs(3 * ((W*y) - (W - x) - 1));  //To find the index of coordinate which need to draw.
	p = &rgb[index];  //Point the pointer to the previous of index.
	*p++ = 255;  /* R */
	*p++ = 255;  /* G */
	*p++ = 255;  /* B */
}

void generalLine(int x1, int y1, int x2, int y2)  //Using general form y=kx+b to rasterize a line. Note that x1<=x2 y1<=y2.
{
	double k = (y2 - y1)*1.0 / (x2 - x1);  //Find the Slope
	double b = (y2*x1 - y1*x2) / (x2 - x1);  //Find the Intercept 
	int y = y1;
	for (int x = x1; x < x2; x++)  
	{
		y =(int)(k*x*1.0-b);   //For y=kx, plug each 'kx' into y. 
									   //Due to the PNG's coded format, of which y-axis is contrary to the standard Y-axis, the 'y=kx-b' is compliant.
		setPixel(x, y);
	}
}

void main(void) {
	FILE *fp = fopen("rgb.png", "wb");
	unsigned x, y;
	for (x = 0; x < 256; x++)
		for (y = 0; y < 256 ; y++)
		{
			*p++ = 30;
			*p++ = 0;
			*p++ = 21;
		}

	generalLine(10, 200, 200, 100);
	generalLine(42, 41, 122,200);

	svpng(fp, W, H, rgb, 0);
	fclose(fp);
}
