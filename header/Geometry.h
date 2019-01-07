#pragma once
#include<vector>
#include<iostream>
#include<algorithm>
#include"Math3D.h"
#include"Shading.h"
#include"Image.h"
//����
class Geom_Vertex
{
public:
	Point4D local_pos;
	Point4D self_trans;
	Point4D world_trans;
	Point4D trans;

	//ʹ�øö����ͼԪ����
	std::vector<size_t> index_of_plist;

	//����z-buffer����Ȳ�ֵ
	//͸�ӽ׶ε�zֵ
	float z;

	//���㷨����
	Vector4D normal_vertex;
	//�������ǿ��(Gouraud)
	ColorRGB ambient_total, diffuse_total;

	ColorRGB color;
	float u, v;

	Geom_Vertex()
	{
		self_trans = local_pos;
	}
	Geom_Vertex(float _x, float _y, float _z, ColorRGB _c);
};
//������ͼԪ
class Geom_Triangle
{
public:
	//���������õĶ�������	
	std::vector<size_t> p;
	Geom_Vertex vlist[3];
	//������
	Vector4D normal;
	//���
	float area;
	//�ɼ�?
	bool visible;
	bool texture_active;
	//��ͼ
	Texture texture;

	Geom_Triangle()
	{
		texture_active = false;
		visible = true;
	}
	inline void update_normal_tri()
	{
		//���¼��㷨����
		normal = vector_crossproduct(vlist[1].self_trans - vlist[0].self_trans,
			vlist[2].self_trans - vlist[0].self_trans);
		normal.normalize();
	}
};
//����
class Geom_Object
{
public:
	Point4D world_pos;
	//�����õ��Ķ���
	std::vector<Geom_Vertex> vlist;
	//��vlist����������ͼԪ
	std::vector<Geom_Triangle> plist;
	//������׶�޳�(��Χ�����)
	float r;
	Point4D center, left, right, up, bottom, front, back;
	//�������
	Material material;

	//����������״ֵ̬
	bool back_cull;
	bool frustum_cull;

	bool visible;

	Geom_Object()
	{
		r = 0;
		world_pos = Point4D(0, 0, 0);
		//Ĭ�ϱ��治����
		back_cull = false;
		//Ĭ�ϲ�������׶�޳�
		frustum_cull = false;

		visible = true;
	}

	//����һ�����㵽vlist
	inline void add_vlist(const Geom_Vertex &Vertex)
	{
		float r_tmp = Vertex.local_pos.length();
		if (r_tmp > r)
			r = r_tmp;
		vlist.push_back(Vertex);
	}
	inline void print_vlist()
	{
		for (auto i : vlist)
			i.local_pos.print();
	}

	//����һ��ͼԪ��plist
	//����ֱ�ָ�������������������ʱ��
	//������vlist�е������
	//uv1��uv2��uv3����p0��p1��p2��˳��ֱ�ָ��
	inline void add_plist(size_t p0, size_t p1, size_t p2, const Texture &texture, const bool &active, const Point2D &uv1, const Point2D &uv2, const Point2D &uv3)
	{
		Geom_Triangle tmp;
		tmp.texture = texture;
		//������
		Vector4D normal;

		tmp.vlist[0] = vlist[p0];
		tmp.vlist[1] = vlist[p1];
		tmp.vlist[2] = vlist[p2];
		tmp.vlist[0].u = uv1.x;	tmp.vlist[0].v = uv1.y;
		tmp.vlist[1].u = uv2.x;	tmp.vlist[1].v = uv2.y;
		tmp.vlist[2].u = uv3.x;	tmp.vlist[2].v = uv3.y;
		tmp.p.push_back(p0);
		tmp.p.push_back(p1);
		tmp.p.push_back(p2);

		tmp.texture_active = active;

		//���㷨����
		normal = vector_crossproduct(vlist[p1].local_pos - vlist[p0].local_pos,
			vlist[p2].local_pos - vlist[p0].local_pos);
		tmp.area = normal.length() / 2;
		normal.normalize();
		tmp.normal = normal;

		plist.push_back(tmp);

		//�붥���ͼԪ������
		vlist[p0].index_of_plist.push_back(plist.size() - 1);
		vlist[p1].index_of_plist.push_back(plist.size() - 1);
		vlist[p2].index_of_plist.push_back(plist.size() - 1);
	}

	inline void update_normal_obj()
	{
		int flag=0;
		//���·�����
		for (auto &tri : plist)
			tri.update_normal_tri();
		//���¶��㷨����
		for (auto &vertex : vlist)
		{
			for (auto &IOP1 : vertex.index_of_plist)
			{
				//�жϹ���
				Vector4D tmp = plist[IOP1].normal;
				auto it = find(vertex.index_of_plist.begin(), vertex.index_of_plist.end(), IOP1)+1;
				for (it; it != vertex.index_of_plist.end(); it++)
				{
					if (tmp == plist[*it].normal)
					{
						flag = 1;
						break;
					}
				}
				if (flag)
				{
					flag = 0;
					continue;
				}
				vertex.normal_vertex += plist[IOP1].normal*plist[IOP1].area;
			}
			vertex.normal_vertex.normalize();
		}

	}
};
//��Ⱦ�б�
class Render_List
{
public:
	std::vector<Geom_Object> object_list;
	
	inline void add_vlist(const Geom_Object &object)
	{
		object_list.push_back(object);
	}
};