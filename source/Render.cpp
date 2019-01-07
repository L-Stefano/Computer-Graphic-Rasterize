#include<thread>
#include<iostream>
#include<time.h>
#include<vector>

#include"Math3D.h"
#include"SDLINIT.h"
#include"Geometry.h"
#include"Pipeline.h"
#include"Render.h"
#include"Shading.h"
//z_buffer
float z_buffer[Width*Height] = { 0 };

int draw_line_bresenham(Point2D p1, Point2D p2, ColorRGB color, SDL_Surface * surface)
{
	SDL_LockSurface(surface);
	Uint32 colors = SDL_MapRGB(surface->format, color.R_ratio*255.0f, color.G_ratio*255.0f, color.B_ratio*255.0f);
	Uint32 *pixel = (Uint32*)surface->pixels;
	int pitch = surface->pitch / 4;



	int x, y;
	int dx = p2.x - p1.x,
		dy = p2.y - p1.y;
	int _2dxerr = 0;
	int _2dyerr = 0;

	float err = 0;
	if (abs(dx) >= abs(dy))	// |б��|<=1
	{
		if (p2.x < p1.x)
		{
			dx = -dx;
			dy = -dy;
			std::swap(p1, p2);
		}
		x = p1.x;
		y = p1.y;

		if (dy > 0 && dx > 0)		//0<б��<1
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
		else if (dy < 0 && dx>0)		//-1<б��<0
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
		else if (dy == 0 && dx > 0)//б��Ϊ0��ƽ�У�
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
	else if (abs(dx) < abs(dy))//|б��|>1
	{
		if (p2.y < p1.y)
		{
			dx = -dx;
			dy = -dy;
			std::swap(p1, p2);
		}
		x = p1.x;
		y = p1.y;

		if (dy > 0 && dx > 0)		//б��>1
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
		else if (dy > 0 && dx < 0)		//б��<-1
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
		else if (dx == 0 && dy > 0)//б�ʲ����ڣ���ֱ��
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
		//������״̬
		//�Ա������һ֡��Ⱦ
		tri.visible = true;
		return -1;
	}

	draw_line_bresenham(tri.vlist[0].trans.toVec2D(), tri.vlist[1].trans.toVec2D(), tri.vlist->color, surface);
	draw_line_bresenham(tri.vlist[0].trans.toVec2D(), tri.vlist[2].trans.toVec2D(), tri.vlist->color, surface);
	draw_line_bresenham(tri.vlist[1].trans.toVec2D(), tri.vlist[2].trans.toVec2D(), tri.vlist->color, surface);
	return 1;
}

int draw_triangle_baryinterp(Geom_Object &o, Geom_Triangle &tri, int filter_flag, const Light_List &light_list, const Camera_UVN & camera, SDL_Surface *surface)
{
	//����ɼ����ж�
	if (tri.visible == false)
	{
		//������״̬
		//�Ա������һ֡��Ⱦ
		tri.visible = true;
		return -1;
	}
	ColorRGB c;
	SDL_LockSurface(surface);
	Uint32 *pixel = (Uint32*)surface->pixels;
	int pitch = surface->pitch / 4;

	//�����������������Ļ����
	Point4D p0 = tri.vlist[0].trans,
		p1 = tri.vlist[1].trans,
		p2 = tri.vlist[2].trans;
	//��z-buffer��͸�ӽ׶�)��zֵд��
	p0.z = tri.vlist[0].z;
	p1.z = tri.vlist[1].z;
	p2.z = tri.vlist[2].z;
	//�����������������������
	//�������ص����������ֵ
	Point4D p0_world = tri.vlist[0].world_trans,
		p1_world = tri.vlist[1].world_trans,
		p2_world = tri.vlist[2].world_trans;
	//��������������Ķ��㷨��
	//�������صķ��������ֵ
	Vector4D p0_normal = o.vlist[tri.p[0]].normal_vertex;
	Vector4D p1_normal = o.vlist[tri.p[1]].normal_vertex;
	Vector4D p2_normal = o.vlist[tri.p[2]].normal_vertex;

	//���Ĳ�ֵ
	//�߽�ֵ����
	int xmax = p0.x > p1.x ? (p0.x > p2.x ? p0.x : p2.x) : (p1.x > p2.x ? p1.x : p2.x);
	int xmin = p0.x < p1.x ? (p0.x < p2.x ? p0.x : p2.x) : (p1.x < p2.x ? p1.x : p2.x);
	int ymax = p0.y > p1.y ? (p0.y > p2.y ? p0.y : p2.y) : (p1.y > p2.y ? p1.y : p2.y);
	int ymin = p0.y < p1.y ? (p0.y < p2.y ? p0.y : p2.y) : (p1.y < p2.y ? p1.y : p2.y);

	float falpha = (p1.y - p2.y)*p0.x + (p2.x - p1.x)*p0.y + p1.x*p2.y - p1.y*p2.x;
	float fbeta = (p2.y - p0.y)*p1.x + (p0.x - p2.x)*p1.y + p2.x*p0.y - p2.y*p0.x;
	float fgamma = (p0.y - p1.y)*p2.x + (p1.x - p0.x)*p2.y + p0.x*p1.y - p0.y*p1.x;

	//���Ϲ���-1��-1
	float falpha_minus1_minus1 = (p1.y - p2.y)*(-1.0f) + (p2.x - p1.x)*(-1.0f) + p1.x*p2.y - p1.y*p2.x;
	float fbeta_minus1_minus1 = (p2.y - p0.y)*(-1.0f) + (p0.x - p2.x)*(-1.0f) + p2.x*p0.y - p2.y*p0.x;
	float fgamma_minus1_minus1 = (p0.y - p1.y)*(-1.0f) + (p1.x - p0.x)*(-1.0f) + p0.x*p1.y - p0.y*p1.x;

	//��ֵ�����������
	float u = 0, v = 0;
	//��ֵ���zֵ
	float z = 0;
	//��ֵ�����Ĺ�����Ϣ
	ColorRGB intensity_total;
	//ÿ�����ز�ֵ�õ��Ŀռ�����
	Point4D pixel_pos_in_world;
	//ÿ�����ز�ֵ�õ��ķ�����
	Vector4D pixel_normal_in_world;
	for (int y = ymin; y <= ymax; ++y)
		for (int x = xmin; x <= xmax; ++x)
		{
			if (x < 0 || x >= surface->w || y < 0 || y >= surface->h)
				continue;
			//����ϵ��
			float alpha, beta, gamma;
			beta = ((p2.y - p0.y)*x + (p0.x - p2.x)*y + p2.x*p0.y - p2.y*p0.x) * (1.0f / fbeta);
			alpha = ((p1.y - p2.y)*x + (p2.x - p1.x)*y + p1.x*p2.y - p1.y*p2.x) * (1.0f / falpha);
			gamma = 1 - alpha - beta;
			//�ж��Ƿ�����������
			if (alpha >= 0 && beta >= 0 && gamma >= 0)
			{
				//���Ϲ����ж�
				if ((alpha > 0 || falpha * falpha_minus1_minus1 > 0) &&
					(beta > 0 || fbeta * fbeta_minus1_minus1 > 0) &&
					(gamma > 0 || fgamma * fgamma_minus1_minus1 > 0))
				{
					//����任ǰ�Ŀռ�Ħ����¡���
					float d = p1.z*p2.z + p2.z*beta*(p0.z - p1.z) + p1.z*gamma*(p0.z - p2.z);
					float _d = 1 / d;
					float beta_hom = p0.z*p2.z*beta *_d;
					float alpha_hom = p1.z*p2.z*alpha * _d;
					float gamma_hom = p0.z*p1.z*gamma * _d;

					//���������ж�
					if (alpha_hom >= 0 && beta_hom >= 0 && gamma_hom >= 0)
					{
						if (!tri.texture_active)//����Ƭ�޲���
							c = tri.vlist[0].color*alpha_hom + tri.vlist[1].color*beta_hom + tri.vlist[2].color*gamma_hom;
						else if (tri.texture_active)//����Ƭ�в���
						{
							//z��ֵ
							//����ջ��z-buffer
							z = p0.z * alpha_hom + p1.z * beta_hom + p2.z * gamma_hom;
							if (z <= z_buffer[y*Width+x] )
							{
								z_buffer[y*Width + x] = z;
							}
							else if (z_buffer[y*Width + x] == -1.0f)
							{
								z_buffer[y*Width + x] = z;
							}
							else if (z > z_buffer[y*Width + x])
							{
								continue;
							}


							//��ֵuv����
							u = tri.vlist[0].u*alpha_hom + tri.vlist[1].u*beta_hom + tri.vlist[2].u*gamma_hom;
							v = tri.vlist[0].v*alpha_hom + tri.vlist[1].v*beta_hom + tri.vlist[2].v*gamma_hom;
							//���ղ�ֵ
							//ambient_total=tri.vlist[0].ambient_total*alpha_hom + tri.vlist[1].ambient_total*beta_hom + tri.vlist[2].ambient_total*gamma_hom;
							//diffuse_total = tri.vlist[0].diffuse_total*alpha_hom + tri.vlist[1].diffuse_total*beta_hom + tri.vlist[2].diffuse_total*gamma_hom;
							//�����ֵ
							pixel_pos_in_world = p0_world * alpha_hom + p1_world * beta_hom + p2_world * gamma_hom;
							//��������ֵ
							pixel_normal_in_world = p0_normal * alpha_hom + p1_normal * beta_hom + p2_normal * gamma_hom;
							pixel_normal_in_world.normalize();
							//���ռ���
							intensity_total = shading_calculate(o, tri, pixel_pos_in_world, pixel_normal_in_world, camera, light_list);


							if (filter_flag == FILTERMODE_POINTSAMPLE)
								c = tri.texture.get_color_point_sampling(u, v);
							else if (filter_flag == FILTERMODE_BILINEAR)
								c = tri.texture.get_color_bilinear(u, v);

							c = c * intensity_total;
						}
						pixel[pitch*y + x] = SDL_MapRGB(surface->format, c.R_ratio*255.0f, c.G_ratio*255.0f, c.B_ratio*255.0f);
					}

				}
			}
		}
	SDL_UnlockSurface(surface);

	return 1;
}

void draw_triangle_baryinterp_multitread(Geom_Object &o, std::vector<Geom_Triangle> v, int filter_flag, const Light_List &light_list, const Camera_UVN & camera, SDL_Surface *surface)
{
	for (auto tri : v)
	{
		draw_triangle_baryinterp(o, tri, filter_flag, light_list, camera, surface);
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

int draw_object_baryinterp(Geom_Object & o, int filter_flag, const Light_List &light_list, bool multithread, const Camera_UVN & camera, SDL_Surface * surface)
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
			draw_triangle_baryinterp(o, tri, filter_flag, light_list, camera, surface);
		}

	}
	else if (multithread)
	{
		//��plist�ֳ�8��
		int partition = round(o.plist.size() / 2.0f);
		//��ȡͷ������
		auto beg = o.plist.begin();
		std::vector<Geom_Triangle> vec1(beg, beg + partition),
			vec2(beg + partition, o.plist.end());

		//�����߳�
		std::thread t_1(draw_triangle_baryinterp_multitread, std::ref(o), vec1, filter_flag, std::ref(light_list), std::ref(camera), surface),
			t_2(draw_triangle_baryinterp_multitread, std::ref(o), vec2, filter_flag, std::ref(light_list), std::ref(camera), surface);
		t_1.join();
		t_2.join();
	}
	return 0;
}
int draw_object_baryinterp_multithread(std::vector<Geom_Object> vec, int filter_flag, const Light_List &light_list, bool multithread, const Camera_UVN & camera, SDL_Surface * surface)
{
	for (auto &o : vec)
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
				draw_triangle_baryinterp(o, tri, filter_flag, light_list, camera, surface);
			}

		}
		else if (multithread)
		{
			//��plist�ֳ�8��
			int partition = round(o.plist.size() / 2.0f);
			//��ȡͷ������
			auto beg = o.plist.begin();
			std::vector<Geom_Triangle> vec1(beg, beg + partition),
				vec2(beg + partition, o.plist.end());

			//�����߳�
			std::thread t_1(draw_triangle_baryinterp_multitread, std::ref(o), vec1, filter_flag, std::ref(light_list), std::ref(camera), surface),
				t_2(draw_triangle_baryinterp_multitread, std::ref(o), vec2, filter_flag, std::ref(light_list), std::ref(camera), surface);
			t_1.join();
			t_2.join();
		}
	}
	return 0;
}

int draw_render_list(Render_List &render_list, int filter_flag, const Light_List &light_list, bool multithread, const Camera_UVN & camera, SDL_Surface *surface)
{
	for (auto &i : z_buffer)
		i = -1.0;

	if (!multithread)
	{
		for (auto &obj : render_list.object_list)
			draw_object_baryinterp(obj, filter_flag, light_list, multithread, camera, surface);
	}
	else if (multithread)
	{
		//��plist�ֳ�8��
		int partition = round(render_list.object_list.size() / 2.0f);
		//��ȡͷ������
		auto beg = render_list.object_list.begin();
		std::vector<Geom_Object> vec1(beg, beg + partition),
			vec2(beg + partition, render_list.object_list.end());

		//�����߳�
		std::thread t_3(draw_object_baryinterp_multithread, vec1, filter_flag, std::ref(light_list), multithread, std::ref(camera), surface),
			t_4(draw_object_baryinterp_multithread, vec2, filter_flag, std::ref(light_list), multithread, std::ref(camera), surface);
		t_3.join();
		t_4.join();
	}

	return 0;
}

//=====================================================================
// ���ռ���
//=====================================================================
//�Ե������ؽ��м���
//Phongģ��
//�����ܹ���ǿ��
inline ColorRGB shading_calculate(Geom_Object &o, const Geom_Triangle &tri, const Point4D &pixel_pos_in_world, const Vector4D &pixel_normal_in_world, const Camera_UVN &camera, const Light_List &light_list)
{
	ColorRGB i_total_ambient(0.0f, 0.0f, 0.0f);
	ColorRGB i_total_diffuse(0.0f, 0.0f, 0.0f);
	ColorRGB i_total_specular(0.0f, 0.0f, 0.0f);
	ColorRGB i_total(0.0f, 0.0f, 0.0f);
	//�ӵ�����(�ӿռ��ָ�������)
	Vector4D  view_vec = (camera.cam_pos - pixel_pos_in_world);
	view_vec.normalize();
#pragma region ���㻷����
	//���㻷����
	for (auto &ambient : light_list.ambient_light_list)
		if (ambient.active)
			i_total_ambient += ambient.intensity_light * o.material.ka;
#pragma endregion
#pragma region �����������뾵���
	//����ƽ�й�
	for (auto &infinitelight : light_list.infinite_light_list)
	{
		if (infinitelight.active)
		{
			//���Դ�Ĺ���ǿ��
			ColorRGB infinitelight_intensity_total(0.0f, 0.0f, 0.0f);
			//ɢ����нǵ�����
			float dotproduct = vector_dotproduct((-infinitelight.direction), tri.normal);
			if (dotproduct > 0.0f)
				infinitelight_intensity_total = infinitelight.intensity_light*dotproduct;
			/*--ɢ���--*/
			i_total_diffuse += infinitelight_intensity_total * o.material.kd;
			/*--�����--*/
		}
	}
	//������Դ
	for (auto &pointlight : light_list.point_light_list)
	{
		if (pointlight.active)
		{
			//��������
			Vector4D incident_vec = (pointlight.position - pixel_pos_in_world);
			incident_vec.normalize();
			//��������
			Vector4D reflec_vec = pixel_normal_in_world * (vector_dotproduct(pixel_normal_in_world, incident_vec) * 2.0f) - incident_vec;
			reflec_vec.normalize();

			//���Դ�Ĺ���ǿ��
			ColorRGB pointlight_intensity_total(0.0f, 0.0f, 0.0f);
			//��Դ�붥��ľ���
			float distance = vector_distance(pointlight.position, pixel_pos_in_world);
			pointlight_intensity_total = (pointlight.intensity_light / (pointlight.kc + pointlight.kl*distance + pointlight.kq*distance*distance));

			/*--ɢ���--*/
			i_total_diffuse += pointlight_intensity_total * o.material.kd;
			/*--�����--*/
			i_total_specular += o.material.ks*pointlight_intensity_total*powf(std::max(0.0f, vector_dotproduct(reflec_vec, view_vec)), o.material.power)*(vector_dotproduct(pixel_normal_in_world, incident_vec) > 0.0f ? 1.0f : 0.0f);
		}
	}
	//����۹��
	for (auto &spotlight : light_list.spotlight_list)
	{
		if (spotlight.active)
		{
			//�۹�ƵĹ���ǿ��
			ColorRGB spotlight_intensity_total(0.0f, 0.0f, 0.0f);
			//ɢ����нǵ�����
			float dotproduct = vector_dotproduct(-spotlight.direction, pixel_normal_in_world);
			//��Դ�붥��ľ���
			float distance = vector_distance(spotlight.position, pixel_pos_in_world);
			//�۹�Ƴ����붥������ɼнǵĶ���
			float angle_of_lightdir_vertex = vector_angle(spotlight.direction, pixel_pos_in_world - spotlight.position);
			if (dotproduct > 0)
				if (angle_of_lightdir_vertex > spotlight.penumbra*0.5f)//λ�ڰ�Ӱ��
					continue;
				else if (angle_of_lightdir_vertex < spotlight.umbra*0.5f)//λ�ڱ�Ӱ��
					spotlight_intensity_total = (spotlight.intensity_light / (spotlight.kc + spotlight.kl*distance + spotlight.kq*distance*distance));
				else if (angle_of_lightdir_vertex > spotlight.umbra*0.5f&&angle_of_lightdir_vertex < spotlight.penumbra*0.5f)//λ�ڱ�Ӱ��Ӱ֮��
					spotlight_intensity_total = ((spotlight.intensity_light / (spotlight.kc + spotlight.kl*distance + spotlight.kq*distance*distance))*
					(powf(cosf(angle_of_lightdir_vertex) - cosf(spotlight.penumbra*0.5f), spotlight.pf) / (cosf(spotlight.umbra*0.5f) - cosf(spotlight.penumbra*0.5f))));
			/*-----------
				ɢ���
			-----------*/
			i_total_diffuse += spotlight_intensity_total * o.material.kd*dotproduct;
			/*-----------
				�����
			-----------*/

		}
	}

#pragma endregion
#pragma region ���㾵���


#pragma endregion
	i_total = i_total_ambient + i_total_diffuse + i_total_specular;;
	if (i_total.R_ratio > 1.0f) i_total.R_ratio = 1.0f;
	if (i_total.G_ratio > 1.0f)i_total.G_ratio = 1.0f;
	if (i_total.B_ratio > 1.0f)i_total.B_ratio = 1.0f;
	return i_total;

}

