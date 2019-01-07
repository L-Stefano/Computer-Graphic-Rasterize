#pragma once
/*����*/
const int Width = 800;//ʵ�����귶Χ[0,W-1]
const int Height = 600;//ʵ�����귶Χ[0,H-1]
/*��*/
#define FILTERMODE_BILINEAR 0x0001
#define FILTERMODE_POINTSAMPLE 0x0002
/*z-buffer*/
extern float z_buffer[];

//��Ļ�ռ�ü�
//Bresenhamֱ���㷨
int draw_line_bresenham(Point2D p1, Point2D p2, ColorRGB color, SDL_Surface *surface); //���гɹ��᷵��1
//����������
int draw_triangle_wireframe(Geom_Triangle &tri, SDL_Surface *surface);
//����������, ���Ĳ�ֵ
int draw_triangle_baryinterp(Geom_Object &o, Geom_Triangle &tri, int filter_flag, const Light_List &light_list, const Camera_UVN & camera, SDL_Surface *surface);
void draw_triangle_baryinterp_multitread(Geom_Object &o, std::vector<Geom_Triangle> v, int filter_flag, const Light_List &light_list, const Camera_UVN & camera, SDL_Surface *surface);
//��������
int draw_object_wireframe(Geom_Object &o, SDL_Surface *surface);
//��������, ���Ĳ�ֵ
int draw_object_baryinterp(Geom_Object &o, int filter_flag, const Light_List &light_list, bool multithread, const Camera_UVN & camera, SDL_Surface *surface);
int draw_object_baryinterp_multithread(std::vector<Geom_Object>  vec, int filter_flag, const Light_List &light_list, bool multithread, const Camera_UVN & camera, SDL_Surface * surface);
//��Ⱦ�б�
int draw_render_list(Render_List &render_list, int filter_flag, const Light_List &light_list, bool multithread, const Camera_UVN & camera, SDL_Surface *surface);
//=====================================================================
// ���ռ���
//=====================================================================
//�����������н��м���
//Lambert������ģ��
inline ColorRGB shading_calculate(Geom_Object &o, const Geom_Triangle &tri, const Point4D &pixel_pos_in_world, const Vector4D &pixel_normal_in_world, const Camera_UVN &camera, const Light_List &light_list);