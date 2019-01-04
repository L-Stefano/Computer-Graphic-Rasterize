#include "SDLINIT.h"
//定义静态成员变量
SDL_Window* Window::mWindow = nullptr;
SDL_Renderer* Window::mRenderer = nullptr;
SDL_Surface * Window::mSurface = nullptr;
SDL_Event Window::mEvent;

extern camera_UVN camera;
extern transform_t trans;
extern Geom_Object object;

//用于保存鼠标偏移量
int mousexdown_rotate;
int mouseydown_rotate;
int mousexup_rotate;
int mouseyup_rotate;
int mousexrel_rotate, mouseyrel_rotate;
int z_rotate=0;

void Window::Init(int W, int H, unsigned __int32 Rendererflags)
{
	//初始化SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
		throw std::runtime_error("SDL Init Failed");
	//创建窗口
	if (!(mWindow = SDL_CreateWindow("Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, W, H, SDL_WINDOW_SHOWN)))
		throw std::runtime_error("Window Create Failed");
	//创建渲染器
	if (!(mRenderer = SDL_CreateRenderer(mWindow, -1, Rendererflags)))
		throw std::runtime_error("Renderer Create Failed");

}

void Window::Quit()
{
	SDL_Quit();
}

void Window::Destroy()
{
	SDL_DestroyWindow(mWindow);
	SDL_DestroyRenderer(mRenderer);
	SDL_FreeSurface(mSurface);
}

void Window::CreateSurface()
{
	if (!(mSurface = SDL_GetWindowSurface(mWindow)))
		throw std::runtime_error("Surface Create Failed");
}

//返回1代表退出
//返回0代表未处理事件
int Window::EventProc()
{
	while (SDL_PollEvent(&Window::mEvent))
	{
		//switch (mEvent.key.keysym.sym) :
		//	Window::Quit();
		//break;
		switch (mEvent.type)
		{
		case SDL_KEYDOWN:
			switch (mEvent.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				Window::Quit();
				return 1;
				break;
			case SDLK_UP:
				camera.cam_pos.z +=0.1;
				camera.lookat.z += 0.1;
				break;
			case SDLK_DOWN:
				camera.cam_pos.z -=0.1;		
				camera.lookat.z -= 0.1;
				break;
			case SDLK_LEFT:
				z_rotate -= 10;
				break;
			case SDLK_RIGHT:
				z_rotate += 10;
				break;
			case SDLK_KP_6:
				camera.lookat.x += 0.1;
				camera.cam_pos.x += 0.1;
				break;
			case SDLK_KP_4:
				camera.lookat.x -= 0.1;
				camera.cam_pos.x -= 0.1;
				break;
			case SDLK_KP_8:	
				camera.lookat.y += 0.1;
				camera.cam_pos.y += 0.1;
				break;
			case SDLK_KP_2:
				camera.lookat.y -= 0.1;
				camera.cam_pos.y -= 0.1;
				break;
			case SDLK_b:
				if (object.back_cull)
					object.back_cull = false;
				else
					object.back_cull = true;
				break;
			case SDLK_o:
				if (object.frustum_cull)
					object.frustum_cull = false;
				else
					object.frustum_cull = true;
				break;
			}
			break;
		case SDL_QUIT:
			Window::Quit();
			return 1;
			break;
		//case SDL_MOUSEBUTTONUP:
		//	if (mEvent.button.button == SDL_BUTTON_LEFT)
		//	{
		//		mousexup = mEvent.motion.x;
		//		mouseyup = mEvent.motion.y;

		//	}
		//	break;
		case SDL_MOUSEBUTTONDOWN:
			if (mEvent.button.button == SDL_BUTTON_LEFT)
			{
				mousexdown_rotate = mousexup_rotate;
				mouseydown_rotate = mouseyup_rotate;
			}

			break;
		case SDL_MOUSEMOTION:
			mousexup_rotate = mEvent.motion.x;
			mouseyup_rotate = mEvent.motion.y;
			if (mEvent.button.button == SDL_BUTTON_LEFT)
			{
				mousexrel_rotate = mEvent.motion.x - mousexdown_rotate;
				mouseyrel_rotate = mEvent.motion.y - mouseydown_rotate;
			}		

			break;
		}
	}
	trans.Object_self(object,1, 1, 1, Vector4D(0, 1, 0), mousexrel_rotate % 360, Vector4D(1, 0, 0), mouseyrel_rotate % 360, Vector4D(0, 0, 1), z_rotate % 360);
	camera.camera_update();
	return 0;
}

