/*----------------------------------------------------------------
Copyright (C) 2017 Stefano. All rights reserved.

(mixed color)=α*(front color)+(1-α)*(back color), the equation of mixed color by α.

svpng() is from https://github.com/miloyip/svpng, by Miloyip.

!
\file			generalLine.cpp
\brief        generalLine() is a C++ function for drawing a line with the general form y=kx+b.
\author     Stefano
\version    1.0.0.171130
\copyright
\sa         https://github.com/L-Stefano/Computer-Graphic-Rasterize/edit/master/ALPHA/ALPHA.cpp
!
----------------------------------------------------------------*/

#include "svpng.h"
#include <Windows.h>
#include <math.h>
#include <fstream>
const unsigned W = 256;  //Weight
const unsigned H = 256;  //Height
unsigned char rgb[W * H * 3], *p = rgb;

void main(void) {
	FILE *fp = fopen("rgb.png", "wb");
	unsigned x, y;
	double ALPHA = 0.5; //set value of α

	for (x = 0; x < 256; x++)
		for (y = 0; y < 256; y++)
		{
			*p++ = x;
			*p++ = y;
			*p++ = 255;
		}	//original picture

	p = &rgb[0]; //repoint p to the begin

	for (x = 0; x < 256; x++)
		for (y = 0; y < 256; y++)
		{
			*p++ = *p*ALPHA+(1-ALPHA)*255;
			*p++ = *p*ALPHA + (1 - ALPHA) * 0;
			*p++ =  *p*ALPHA + (1 - ALPHA) * 100;
		} //(mixed color)=α*(front color)+(1-α)*(back color)

	svpng(fp, W, H, rgb, 0);
	fclose(fp);
}