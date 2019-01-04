#pragma once
#include<SDL.h>
#include<iostream>
#include"Transformation.h"

class Window {
public:
	/*--初始化SDL，创建窗口渲染器(SDL_Renderer)
	--W H:窗口宽高
	--Rendererflags:渲染器的标识*/
	static void Init(int W, int H, unsigned __int32 Rendererflags);
	//退出SDL
	static void Quit();
	//销毁资源
	static void Destroy();
	//创建表面
	static void CreateSurface();
	//事件处理
	static int EventProc();

	static SDL_Event mEvent;
	static SDL_Window* mWindow;
	static SDL_Renderer* mRenderer;
	static SDL_Surface *mSurface;
};
