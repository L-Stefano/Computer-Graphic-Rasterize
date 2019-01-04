#pragma once
#include"Math3D.h"
#include"SDLINIT.h"
#include"Geometry.h"
#include"Transformation.h"
#include<iostream>
#include<time.h>
#include<vector>
/*宏*/
#define FILTERMODE_BILINEAR 0x0001
#define FILTERMODE_POINTSAMPLE 0x0002

//屏幕空间裁剪
//Bresenham直线算法
int draw_line_bresenham(Point2D p1, Point2D p2, ColorRGB color,SDL_Surface *surface); //运行成功会返回1
//绘制三角形
int draw_triangle_wireframe(Geom_Triangle &tri, SDL_Surface *surface);
//绘制三角形, 重心插值
int draw_triangle_baryinterp(Geom_Triangle &tri, int filter_flag, SDL_Surface *surface);
//绘制物体
int draw_object_wireframe(Geom_Object & o, SDL_Surface *surface);
//绘制物体, 重心插值
int draw_object_baryinterp(Geom_Object & o, int filter_flag,bool multithread, SDL_Surface *surface);
