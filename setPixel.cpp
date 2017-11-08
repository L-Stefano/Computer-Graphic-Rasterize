
/*----------------------------------------------------------------
Copyright (C) 2017 Stefano. All rights reserved.

setpixel(), accomplished the funchtion which could draw a single pixel.

svpng() is from https://github.com/miloyip/svpng, by Miloyip.

! \file	setPixel.cpp
\brief      setPixel() is a C++ function for drawing a pixel.
\author     Stefano
\version    1.0.0.171105
\copyright
\sa         https://github.com/L-Stefano/Computer-Graphic-Rasterize/blob/master/setPixel.cpp
!
----------------------------------------------------------------*/

#include "svpng.h"
const unsigned W=256;  //Weight
const unsigned H=256;  //Height
unsigned char rgb[W * H * 3], *p = rgb;

void setPixel(int x, int y)  //x and y are coordinate which you want to draw.
{
	int index = 3 * ((W*y) - (W - x) - 1);  //To find the index of coordinate which need to draw.
	p = &rgb[index];  //Point the pointer to the last of index.
	*p++ = 255;  /* R */
	*p++ = 255;  /* G */
	*p++ = 255;  /* B */
}

void main(void) {
	FILE *fp = fopen("rgb.png", "wb");

	setPixel(200, 122); 

	svpng(fp, W, H, rgb, 0);
	fclose(fp);
}
