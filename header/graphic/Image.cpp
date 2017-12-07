/*----------------------------------------------------------------
Copyright (C) 2017 Stefano. All rights reserved.

Implementation file of graphic.h: Image.cpp
------------------------------------------------------------------

!
\file	    Image.cpp
\brief      Implementation file of class Rasterize of graphic.h.
\author     Stefano
\version    1.0.0.171201
\copyright
\sa         https://github.com/L-Stefano/Computer-Graphic-Rasterize/blob/master/header/graphic/Image.cpp
\personal website		http://www.stefano.com.cn
!
----------------------------------------------------------------
updates:
----------------------------------------------------------------*/
#include"graphic.h"
#include"svpng.h"

void Image::exprortPNG(char * name)//The formal parameter, name, is the file name you are going to save.
{
	FILE *fp;
	fopen_s(&fp, name, "wb");
	svpng(fp, W, H, rgb, 0);
	fclose(fp);
}
