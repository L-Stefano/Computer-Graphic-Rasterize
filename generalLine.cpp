
/*----------------------------------------------------------------
Copyright (C) 2017 Stefano. All rights reserved.

generalLine(), accomplished the funchtion which could draw a single line.
with the general form y=kx.
due to the complexity of multiplication 'kx', this method is not advocating use.

svpng() is from https://github.com/miloyip/svpng, by Miloyip.

! \file	setPixel.cpp
\brief      setPixel() is a C++ function for drawing a pixel.
\author     Stefano
\version    1.0.0.171105
\copyright
\sa         https://github.com/L-Stefano/Computer-Graphic-Rasterize/blob/master/generalLine.cpp
!
----------------------------------------------------------------*/

#include "svpng.h"
#include <math.h>
const unsigned W = 256;  //Weight
const unsigned H = 256;  //Height
unsigned char rgb[W * H * 3], *p = rgb;

void setPixel(int x, int y)  //x and y are coordinate which you want to draw.
{
	int index = 3 * ((W*y) - (W - x) - 1);  //To find the index of coordinate which need to draw.
	p = &rgb[index];  //Point the pointer to the previous of index.
	*p++ = 255;  /* R */
	*p++ = 255;  /* G */
	*p++ = 255;  /* B */
}

void generalLine(int x1, int y1, int x2, int y2)  //Using general form y=kx+b to rasterize a line. Note that x1<=x2 y1<=y2.
{
	double k = (y2 - y1)*1.0 / (x2 - x1);  //Find the Slope
	int y = y1;
	for (int x = x1; x < x2; x++)  
	{
		y =(int)( k*x);  //For y=kx, plug each 'kx' into y.
		setPixel(x, y);
	}
}

void main(void) {
	FILE *fp = fopen("rgb.png", "wb");

	generalLine(20, 50, 200, 255);

	svpng(fp, W, H, rgb, 0);
	fclose(fp);
}
