#include"Rasterization.h"
#include<thread>
#include<mutex>
std::mutex mu;

int draw_line_bresenham(Point2D p1, Point2D p2, ColorRGB color, SDL_Surface * surface)
{
	SDL_LockSurface(surface);
	Uint32 colors = SDL_MapRGB(surface->format, color.R, color.G, color.B);
	Uint32 *pixel = (Uint32*)surface->pixels;
	int pitch = surface->pitch / 4;



	int x, y;
	int dx = p2.x - p1.x,
		dy = p2.y - p1.y;
	int _2dxerr = 0;
	int _2dyerr = 0;

	float err = 0;
	if (abs(dx) >= abs(dy))	// |斜率|<=1
	{
		if (p2.x < p1.x)
		{
			dx = -dx;
			dy = -dy;
			std::swap(p1, p2);
		}
		x = p1.x;
		y = p1.y;

		if (dy > 0 && dx > 0)		//0<斜率<1
		{
			for (; x <= p2.x; x++)
			{
				if (x < 0 || x >= surface->w || y < 0 || y >= surface->h)
				{
					_2dxerr = _2dxerr + 2 * dy;
					if (_2dxerr > dx)
					{
						++y;
						_2dxerr -= 2 * dx;
					}
					continue;
				}
				pixel[pitch * y + x] = colors;
				_2dxerr = _2dxerr + 2 * dy;
				if (_2dxerr > dx)
				{
					++y;
					_2dxerr -= 2 * dx;
				}
			}
		}
		else if (dy < 0 && dx>0)		//-1<斜率<0
		{
			for (; x <= p2.x; x++)
			{
				if (x < 0 || x >= surface->w || y < 0 || y >= surface->h)
				{
					_2dxerr = _2dxerr + 2 * dy;
					if (_2dxerr < -dx)
					{
						--y;
						_2dxerr += 2 * dx;
					}
					continue;
				}
				pixel[pitch * y + x] = colors;
				_2dxerr = _2dxerr + 2 * dy;
				if (_2dxerr < -dx)
				{
					--y;
					_2dxerr += 2 * dx;
				}
			}
		}
		else if (dy == 0 && dx > 0)//斜率为0（平行）
		{
			for (; x <= p2.x; x++)
			{
				if (x < 0 || x >= surface->w || y < 0 || y >= surface->h)
				{
					continue;
				}
				pixel[pitch * y + x] = colors;
			}
		}
		else if (dx == 0 && dy == 0)
		{
			if (x >= 0 || x < surface->w || y >= 0 || y < surface->h)
			{
				pixel[pitch*y + x] = colors;
			}
		}

	}
	else if (abs(dx) < abs(dy))//|斜率|>1
	{
		if (p2.y < p1.y)
		{
			dx = -dx;
			dy = -dy;
			std::swap(p1, p2);
		}
		x = p1.x;
		y = p1.y;

		if (dy > 0 && dx > 0)		//斜率>1
		{
			for (; y <= p2.y; y++)
			{
				if (x < 0 || x >= surface->w || y < 0 || y >= surface->h)
				{
					_2dyerr = _2dyerr + 2 * dx;
					if (_2dyerr > dy)
					{
						++x;
						_2dyerr -= 2 * dy;
					}
					continue;
				}
				pixel[pitch * y + x] = colors;
				_2dyerr = _2dyerr + 2 * dx;
				if (_2dyerr > dy)
				{
					++x;
					_2dyerr -= 2 * dy;
				}

			}
		}
		else if (dy > 0 && dx < 0)		//斜率<-1
		{
			for (; y <= p2.y; y++)
			{
				if (x < 0 || x >= surface->w || y < 0 || y >= surface->h)
				{
					_2dyerr = _2dyerr + 2 * dx;
					if (_2dyerr < -dy)
					{
						--x;
						_2dyerr += 2 * dy;
					}

					continue;
				}
				pixel[pitch * y + x] = colors;
				_2dyerr = _2dyerr + 2 * dx;
				if (_2dyerr < -dy)
				{
					--x;
					_2dyerr += 2 * dy;
				}

				//err = err + (float)dx / dy;
				//if (err < -0.5)
				//{
				//	--x;
				//	err++;
				//}
			}
		}
		else if (dx == 0 && dy > 0)//斜率不存在（垂直）
		{
			for (; y <= p2.y; y++)
			{
				if (x < 0 || x >= surface->w || y < 0 || y >= surface->h)
				{
					continue;
				}
				pixel[pitch * y + x] = colors;
			}
		}
	}

	SDL_UnlockSurface(surface);
	return 1;
}

int draw_triangle_wireframe(Geom_Triangle &tri, SDL_Surface *surface)
{
	if (tri.visible == false)
	{
		//重置其状态
		//以便进入下一帧渲染
		tri.visible = true;
		return -1;
	}

	draw_line_bresenham(tri.vlist[0].trans.toVec2D(), tri.vlist[1].trans.toVec2D(), tri.vlist->color, surface);
	draw_line_bresenham(tri.vlist[0].trans.toVec2D(), tri.vlist[2].trans.toVec2D(), tri.vlist->color, surface);
	draw_line_bresenham(tri.vlist[1].trans.toVec2D(), tri.vlist[2].trans.toVec2D(), tri.vlist->color, surface);
	return 1;
}

int draw_triangle_baryinterp(Geom_Triangle &tri, int filter_flag, SDL_Surface *surface)
{
	//物体可见性判断
	if (tri.visible == false)
	{
		//重置其状态
		//以便进入下一帧渲染
		tri.visible = true;
		return -1;
	}
	ColorRGB c;
	SDL_LockSurface(surface);
	Uint32 *pixel = (Uint32*)surface->pixels;
	int pitch = surface->pitch / 4;


	Point4D p0 = tri.vlist[0].trans,
		p1 = tri.vlist[1].trans,
		p2 = tri.vlist[2].trans;
	p0.z = tri.vlist[0].z;
	p1.z = tri.vlist[1].z;
	p2.z = tri.vlist[2].z;

	//重心插值
	//边界值计算
	int xmax = p0.x > p1.x ? (p0.x > p2.x ? p0.x : p2.x) : (p1.x > p2.x ? p1.x : p2.x);
	int xmin = p0.x < p1.x ? (p0.x < p2.x ? p0.x : p2.x) : (p1.x < p2.x ? p1.x : p2.x);
	int ymax = p0.y > p1.y ? (p0.y > p2.y ? p0.y : p2.y) : (p1.y > p2.y ? p1.y : p2.y);
	int ymin = p0.y < p1.y ? (p0.y < p2.y ? p0.y : p2.y) : (p1.y < p2.y ? p1.y : p2.y);

	float falpha = (p1.y - p2.y)*p0.x + (p2.x - p1.x)*p0.y + p1.x*p2.y - p1.y*p2.x;
	float fbeta = (p2.y - p0.y)*p1.x + (p0.x - p2.x)*p1.y + p2.x*p0.y - p2.y*p0.x;
	float fgamma = (p0.y - p1.y)*p2.x + (p1.x - p0.x)*p2.y + p0.x*p1.y - p0.y*p1.x;

	//左上规则，-1，-1
	float falpha_minus1_minus1 = (p1.y - p2.y)*(-1.0f) + (p2.x - p1.x)*(-1.0f) + p1.x*p2.y - p1.y*p2.x;
	float fbeta_minus1_minus1 = (p2.y - p0.y)*(-1.0f) + (p0.x - p2.x)*(-1.0f) + p2.x*p0.y - p2.y*p0.x;
	float fgamma_minus1_minus1 = (p0.y - p1.y)*(-1.0f) + (p1.x - p0.x)*(-1.0f) + p0.x*p1.y - p0.y*p1.x;

	float u = 0, v = 0;
	for (int y = ymin; y <= ymax; ++y)
		for (int x = xmin; x <= xmax; ++x)
		{
			if (x < 0 || x >= surface->w || y < 0 || y >= surface->h)
				continue;
			//重心系数
			float alpha, beta, gamma;
			beta = ((p2.y - p0.y)*x + (p0.x - p2.x)*y + p2.x*p0.y - p2.y*p0.x) * (1.0f / fbeta);
			alpha = ((p1.y - p2.y)*x + (p2.x - p1.x)*y + p1.x*p2.y - p1.y*p2.x) * (1.0f / falpha);
			gamma = 1 - alpha - beta;
			//判断是否在三角形内
			if (alpha >= 0 && beta >= 0 && gamma >= 0)
			{
				//左上规则判断
				if ((alpha > 0 || falpha * falpha_minus1_minus1 > 0) &&
					(beta > 0 || fbeta * fbeta_minus1_minus1 > 0) &&
					(gamma > 0 || fgamma * fgamma_minus1_minus1 > 0))
				{
					//计算变换前的空间的α、β、γ
					float d = p1.z*p2.z + p2.z*beta*(p0.z - p1.z) + p1.z*gamma*(p0.z - p2.z);
					float _d = 1 / d;
					float beta_hom = p0.z*p2.z*beta *_d;
					float alpha_hom = p1.z*p2.z*alpha * _d;
					float gamma_hom = p0.z*p1.z*gamma * _d;

					//背面消隐判断
					if (alpha_hom >= 0 && beta_hom >= 0 && gamma_hom >= 0)
					{
						if (!tri.texture_active)
							c = tri.vlist[0].color*alpha_hom + tri.vlist[1].color*beta_hom + tri.vlist[2].color*gamma_hom;
						else if (tri.texture_active)
						{
							//插值uv坐标
							u = tri.vlist[0].u*alpha_hom + tri.vlist[1].u*beta_hom + tri.vlist[2].u*gamma_hom;
							v = tri.vlist[0].v*alpha_hom + tri.vlist[1].v*beta_hom + tri.vlist[2].v*gamma_hom;
							if (filter_flag == FILTERMODE_POINTSAMPLE)
								c = tri.texture.get_color_point_sampling(u, v);
							else if (filter_flag == FILTERMODE_BILINEAR)
								c = tri.texture.get_color_bilinear(u, v);
						}
						pixel[pitch*y + x] = SDL_MapRGB(surface->format, c.R, c.G, c.B);
					}

				}
			}
		}
	SDL_UnlockSurface(surface);

	return 1;
}

void draw_triangle_baryinterp_multitread(std::vector<Geom_Triangle> v, int filter_flag, SDL_Surface *surface)
{
	for (auto tri : v)
	{

		draw_triangle_baryinterp(tri, filter_flag, surface);
	}	

}
int draw_object_wireframe(Geom_Object & o, SDL_Surface *surface)
{
	if (!o.visible)
	{
		o.visible = true;
		return -1;
	}
	for (auto &tri : o.plist)
	{
		draw_triangle_wireframe(tri, surface);
	}
	return 0;
}

int draw_object_baryinterp(Geom_Object & o, int filter_flag, bool multithread, SDL_Surface * surface)
{

	if (!o.visible)
	{
		o.visible = true;
		return -1;
	}
	if (!multithread)
	{

		for (auto &tri : o.plist)
		{
			draw_triangle_baryinterp(tri, filter_flag, surface);
		}

	}
	else if (multithread)
	{
		//将plist分成8份
		int partition = round(o.plist.size() / 2.0f);
		//获取头迭代器
		auto beg = o.plist.begin();
		std::vector<Geom_Triangle> vec1(beg, beg + partition),
			vec2(beg + partition, o.plist.end());

		//创建线程
		std::thread t_1(draw_triangle_baryinterp_multitread, vec1, filter_flag, surface),
			t_2(draw_triangle_baryinterp_multitread, vec2, filter_flag, surface);
		t_1.join();
		t_2.join();
	}
	return 0;
}
