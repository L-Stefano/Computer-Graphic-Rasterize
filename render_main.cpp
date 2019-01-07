#include <SDL.h>
#include<iostream>
#include<random>
#include<time.h>
#include<string>

#include"SDLINIT.h"
#include"Image.h"
#include"Math3D.h"
#include"Shading.h"
#include"Render.h"
#include"Geometry.h"
#include"Pipeline.h"

using namespace std;
const SDL_Rect r{ 0,0,Width,Height };//清屏用
float FPS = 0;
int index=0;//用于FPS的采样周期
string fps;

//初始化函数
void init();

Camera_UVN camera(Vector4D(0, 0, 0), Vector4D(0, 2, -2), 200,2, Width - 1, Height - 1,105);
Geom_Object object;
Render_List render_list;
Transform_t trans;
Light_List light_list;

int SDL_main(int argc, char** argv)
{
	init();
	while (true)//事件循环（渲染核心）
	{
		float s = clock();

		if (Window::EventProc() == 1)
			break;

		//变换流水线
		//局部坐标变换在消息处理中执行
		trans.pipeline_renderlist(render_list,camera);
		//主渲染

		SDL_FillRect(Window::mSurface, &r, 0x000000);
		draw_render_list(render_list,FILTERMODE_POINTSAMPLE,light_list, true, camera, Window::mSurface);

		SDL_UpdateWindowSurface(Window::mWindow);
		SDL_Delay(0);

		float e = clock();
		//显示FPS
		if (!(index++ == 6))
		{
			FPS += 1000.0f / (e - s);
		}
		else if (index == 7)
		{
			FPS += 1000.0f / (e - s);
			FPS /= 7.0f;
			fps = "FPS: " + to_string(floorf(FPS));
			SDL_SetWindowTitle(Window::mWindow, fps.c_str());
			FPS = 0;
			index = 0;
		}
	}

	SDL_Quit();
	return 0;
}
void init()
{
	//窗口初始化
	Window::Init(Width, Height, SDL_RENDERER_ACCELERATED);
	Window::CreateSurface();

	//读取纹理
	Texture side, top;
	side.load_png(".\\Textures\\gold_block.png");
	top.load_png(".\\Textures\\gold_block.png");

	//正方体的全部顶点
	object.add_vlist(Geom_Vertex(-1, -1, -1, ColorRGB(1.0f ,1.0f, 0.0f)));// 0
	object.add_vlist(Geom_Vertex(1, -1, -1, ColorRGB(1.0f, 1.0f, 1.0f)));// 1
	object.add_vlist(Geom_Vertex(1, -1, 1, ColorRGB(0.0f, 1.0f, 1.0f)));// 2
	object.add_vlist(Geom_Vertex(-1, -1, 1, ColorRGB(0.0f, 0.5f, 0.78f)));// 3
	object.add_vlist(Geom_Vertex(-1, 1, -1, ColorRGB(1.0f, 0.0f, 0.0f)));// 4
	object.add_vlist(Geom_Vertex(1, 1, -1, ColorRGB(0.47f, 0.47f, 0.47f)));// 5
	object.add_vlist(Geom_Vertex(1, 1, 1, ColorRGB(0.99f, 0.5f, 0.4f)));// 6
	object.add_vlist(Geom_Vertex(-1, 1, 1, ColorRGB(0.0f, 1.0f, 0.0f)));// 7
	//添加物体面片
	object.add_plist(0, 2, 1, top, true, Point2D(0, 0), Point2D(side.width - 1, side.height - 1), Point2D(side.width - 1, 0));// 0 //bottom
	object.add_plist(2, 0, 3, top, true, Point2D(side.width - 1, side.height - 1), Point2D(0, 0), Point2D(0, side.height - 1));// 1 //bottom
	object.add_plist(4, 5, 7, top, true, Point2D(0, side.height - 1), Point2D(side.width - 1, side.height - 1), Point2D(0, 0));// 2 //top
	object.add_plist(5, 6, 7, top, true, Point2D(side.width - 1, side.height - 1), Point2D(side.width - 1, 0), Point2D(0, 0));// 3 //top
	object.add_plist(5, 1, 2, side, true, Point2D(0, 0), Point2D(0, side.height - 1), Point2D(side.width - 1, side.height - 1));// 4
	object.add_plist(2, 6, 5, side, true, Point2D(side.width - 1, side.height - 1), Point2D(side.width - 1, 0), Point2D(0, 0));// 5
	object.add_plist(0, 4, 7, side, true, Point2D(side.width - 1, side.height - 1), Point2D(side.width - 1, 0), Point2D(0, 0));// 6
	object.add_plist(7, 3, 0, side, true, Point2D(0, 0), Point2D(0, side.height - 1), Point2D(side.width - 1, side.height - 1));// 7
	object.add_plist(0, 1, 4, side, true, Point2D(0, side.height - 1), Point2D(side.width - 1, side.height - 1), Point2D(0, 0));// 8
	object.add_plist(4, 1, 5, side, true, Point2D(0, 0), Point2D(side.width - 1, side.height - 1), Point2D(side.width - 1, 0));// 9
	object.add_plist(3, 7, 6, side, true, Point2D(side.width - 1, side.height - 1), Point2D(side.width - 1, 0), Point2D(0, 0));// 10
	object.add_plist(6, 2, 3, side, true, Point2D(0, 0), Point2D(0, side.height - 1), Point2D(side.width - 1, side.height - 1));// 11
		//材质定义
	object.material = Material("NONE", SHADE_MODE_GOURAUD, ColorRGB(1.0f, 1.0f, 1.0f), ColorRGB(0.97f, 0.97f, 0.97f), ColorRGB(1.0f, 1.0f, 1.0f), 16.0f);
	object.back_cull = true;
	object.frustum_cull = true;

	object.world_pos = Point4D(-1, 0, 0);
	render_list.add_vlist(object);
	object.world_pos = Point4D(-1, 0, 2.5);
	render_list.add_vlist(object);
	object.world_pos = Point4D(1.2, 0, 0);
	render_list.add_vlist(object);
	object.world_pos = Point4D(1.2, 0, 2.5);
	render_list.add_vlist(object);

	//光源
	light_list.add_ambient_light(Ambient_Light(ColorRGB(1.0f, 1.0f, 1.0f), ColorRGB(0.025f, 0.025f, 0.025f), true));
	light_list.add_infinite_light(Infinite_Light(Vector4D(0.3,1, 0.5), ColorRGB(0.2f, 0.7f, 1.0f), ColorRGB(0.7f, 0.7f, 0.7f), true));
	light_list.add_point_light(Point_Light(Vector4D(1, 1.5, -1.5), ColorRGB(1.0f, 0.55f, 0.15f), ColorRGB(1.0f, 1.0f, 1.0f), 0.3f, 0.25f, 1.2f, true));
	light_list.add_point_light(Point_Light(Vector4D(-1, 1.5, 1.5), ColorRGB(0.57f, 0.5f, 1.0f), ColorRGB(1.0f, 1.0f, 1.0f), 0.5f, 0.85f, 1.3f, true));
	//light_list.add_spotlight(Spotlight(Vector4D(0.5, 2.0, 0.5), Vector4D(-1, -1, -1), 0, 70, ColorRGB(0.78f, 0.9f, 0.64f), ColorRGB(1.0f, 1.0f, 1.0f), 1.0f, 0.23f, 1.0f, 0.0004f, true));
	light_list.add_point_light(Point_Light(Vector4D(0, 1.5, 0.5), ColorRGB(0.5f, 0.7f, 0.8f), ColorRGB(1.0f, 1.0f, 1.0f), 0.74f, 0.475f, 1.523f, true));

}