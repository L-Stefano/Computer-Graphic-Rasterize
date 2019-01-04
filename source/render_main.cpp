#include <SDL.h>
#include<iostream>
#include<random>
#include<time.h>
#include<string>

#include<SDL_ttf.h>
#include"SDLINIT.h"
#include"Image.h"
#include"Math3D.h"
#include"Rasterization.h"
#include"Geometry.h"
#include"Transformation.h"

using namespace std;
/*����*/
const int Width = 800;//ʵ�����귶Χ[0,W-1]
const int Height = 600;//ʵ�����귶Χ[0,H-1]
const SDL_Rect r{ 0,0,Width,Height };//������
float FPS = 0;
int index=0;//����FPS�Ĳ�������
string fps;

//��ʼ�������
camera_UVN camera(Vector4D(0, 0, 0), Vector4D(1.15, 1.2, -1.2), 200,2, Width - 1, Height - 1,105);
//��ʼ������
Geom_Object object;
//��ʼ���任��ˮ��
transform_t trans;

int SDL_main(int argc, char** argv)
{
	Window::Init(Width, Height, SDL_RENDERER_ACCELERATED);
	Window::CreateSurface();

	//��ȡpng
	Texture side, top;
	side.load_png(".\\Textures\\Grid.png");
	top.load_png(".\\Textures\\Grid.png");

	//�������ȫ������
	object.add_vlist(Geom_Vertex(-1, -1, -1, ColorRGB(255, 255, 0)));// 0
	object.add_vlist(Geom_Vertex(1, -1, -1, ColorRGB(255,255, 255)));// 1
	object.add_vlist(Geom_Vertex(1, -1, 1, ColorRGB(0, 255, 255)));// 2
	object.add_vlist(Geom_Vertex(-1, -1, 1, ColorRGB(135, 144, 200)));// 3
	object.add_vlist(Geom_Vertex(-1, 1, -1, ColorRGB(255, 0, 0)));// 4
	object.add_vlist(Geom_Vertex(1, 1, -1, ColorRGB(122, 122,122)));// 5
	object.add_vlist(Geom_Vertex(1, 1, 1, ColorRGB(246, 135, 144)));// 6
	object.add_vlist(Geom_Vertex(-1, 1, 1, ColorRGB(0, 255, 0)));// 7
	//���������Ƭ
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
	object.back_cull = false;
	object.frustum_cull = true;



	ColorRGB c(100, 100, 3);
	c = c*2.0f;
	c.print();


	while (true)//�¼�ѭ������Ⱦ���ģ�
	{
		float s = clock();

		if (Window::EventProc() == 1)
			break;

		//�任��ˮ��
		//�ֲ�����任����Ϣ������ִ��
		trans.Object_to_World(object);
		trans.back_cull(object, camera);
		trans.frustum_cull(object, camera);
		trans.World_to_Camera(object, camera);
		trans.Camera_to_Perspective_to_Screen(object, camera);
		//����Ⱦ

		SDL_FillRect(Window::mSurface, &r, 0x000000);
		draw_object_baryinterp(object,FILTERMODE_BILINEAR, true,Window::mSurface);
		SDL_UpdateWindowSurface(Window::mWindow);
		SDL_Delay(0);

		float e = clock();
		//��ʾFPS
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