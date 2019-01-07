#pragma once
/*常量*/
const int Width = 800;//实际坐标范围[0,W-1]
const int Height = 600;//实际坐标范围[0,H-1]
/*宏*/
#define FILTERMODE_BILINEAR 0x0001
#define FILTERMODE_POINTSAMPLE 0x0002
/*z-buffer*/
extern float z_buffer[];

//屏幕空间裁剪
//Bresenham直线算法
int draw_line_bresenham(Point2D p1, Point2D p2, ColorRGB color, SDL_Surface *surface); //运行成功会返回1
//绘制三角形
int draw_triangle_wireframe(Geom_Triangle &tri, SDL_Surface *surface);
//绘制三角形, 重心插值
int draw_triangle_baryinterp(Geom_Object &o, Geom_Triangle &tri, int filter_flag, const Light_List &light_list, const Camera_UVN & camera, SDL_Surface *surface);
void draw_triangle_baryinterp_multitread(Geom_Object &o, std::vector<Geom_Triangle> v, int filter_flag, const Light_List &light_list, const Camera_UVN & camera, SDL_Surface *surface);
//绘制物体
int draw_object_wireframe(Geom_Object &o, SDL_Surface *surface);
//绘制物体, 重心插值
int draw_object_baryinterp(Geom_Object &o, int filter_flag, const Light_List &light_list, bool multithread, const Camera_UVN & camera, SDL_Surface *surface);
int draw_object_baryinterp_multithread(std::vector<Geom_Object>  vec, int filter_flag, const Light_List &light_list, bool multithread, const Camera_UVN & camera, SDL_Surface * surface);
//渲染列表
int draw_render_list(Render_List &render_list, int filter_flag, const Light_List &light_list, bool multithread, const Camera_UVN & camera, SDL_Surface *surface);
//=====================================================================
// 光照计算
//=====================================================================
//在世界坐标中进行计算
//Lambert漫反射模型
inline ColorRGB shading_calculate(Geom_Object &o, const Geom_Triangle &tri, const Point4D &pixel_pos_in_world, const Vector4D &pixel_normal_in_world, const Camera_UVN &camera, const Light_List &light_list);