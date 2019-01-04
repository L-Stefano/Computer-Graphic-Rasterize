#pragma once
#include<SDL.h>
#include<iostream>
#include"Transformation.h"

class Window {
public:
	/*--��ʼ��SDL������������Ⱦ��(SDL_Renderer)
	--W H:���ڿ��
	--Rendererflags:��Ⱦ���ı�ʶ*/
	static void Init(int W, int H, unsigned __int32 Rendererflags);
	//�˳�SDL
	static void Quit();
	//������Դ
	static void Destroy();
	//��������
	static void CreateSurface();
	//�¼�����
	static int EventProc();

	static SDL_Event mEvent;
	static SDL_Window* mWindow;
	static SDL_Renderer* mRenderer;
	static SDL_Surface *mSurface;
};
