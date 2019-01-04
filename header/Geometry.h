#pragma once
#include"Math3D.h"
#include<vector>
#include<iostream>
#include<algorithm>
#include"Image.h"
//顶点
class Geom_Vertex
{
public:
	Point4D world_pos;
	Point4D self_trans;
	Point4D trans;

	//使用该顶点的图元索引
	std::vector<size_t> index_of_plist;

	//用于z-buffer和深度插值
	float z;

	//顶点法向量
	Vector4D normal_vertex;

	ColorRGB color;
	float u, v;

	Geom_Vertex()
	{
		self_trans = world_pos;
	}
	Geom_Vertex(float _x, float _y, float _z, ColorRGB _c);
};
//三角形图元
class Geom_Triangle
{
public:
	Geom_Vertex vlist[3];
	//法向量
	Vector4D normal;
	//面积
	float area;
	//可见?
	bool visible;
	bool texture_active;
	//贴图
	Texture texture;

	Geom_Triangle()
	{
		texture_active = false;
		visible = true;
	}
	inline void update_normal_tri()
	{
		//重新计算法向量
		normal = vector_crossproduct(vlist[1].self_trans - vlist[0].self_trans,
			vlist[2].self_trans - vlist[0].self_trans);
		normal.normalize();
	}
};
//物体
class Geom_Object
{
public:
	Point4D world_pos;
	//所有用到的顶点
	std::vector<Geom_Vertex> vlist;
	//按vlist的索引创建图元
	std::vector<Geom_Triangle> plist;
	//用于视锥剔除(包围球测试)
	float r;
	Point4D center, left, right, up, bottom, front, back;

	//背面消隐的状态值
	bool back_cull;
	bool frustum_cull;

	bool visible;

	Geom_Object()
	{
		r = 0;
		world_pos = Point4D(0, 0, 0);
		//默认背面不消隐
		back_cull = false;
		//默认不进行视锥剔除
		frustum_cull = false;

		visible = true;
	}

	//加入一个顶点到vlist
	inline void add_vlist(const Geom_Vertex &Vertex)
	{
		float r_tmp = Vertex.world_pos.length();
		if (r_tmp > r)
			r = r_tmp;
		vlist.push_back(Vertex);
	}
	inline void print_vlist()
	{
		for (auto i : vlist)
			i.world_pos.print();
	}

	//加入一个图元到plist
	//必须分别指定三个点的索引，按逆时针
	//索引是vlist中点的索引
	//uv1、uv2、uv3按照p1、p2、p3的顺序分别指定
	inline void add_plist(size_t p1, size_t p2, size_t p3, const Texture &texture, const bool &active, const Point2D &uv1, const Point2D &uv2, const Point2D &uv3)
	{
		Geom_Triangle tmp;
		tmp.texture = texture;
		//法向量
		Vector4D normal;

		tmp.vlist[0] = vlist[p1];
		tmp.vlist[1] = vlist[p2];
		tmp.vlist[2] = vlist[p3];
		tmp.vlist[0].u = uv1.x;	tmp.vlist[0].v = uv1.y;
		tmp.vlist[1].u = uv2.x;	tmp.vlist[1].v = uv2.y;
		tmp.vlist[2].u = uv3.x;	tmp.vlist[2].v = uv3.y;
		tmp.texture_active = active;

		//计算法向量
		normal = vector_crossproduct(vlist[p2].world_pos - vlist[p1].world_pos,
			vlist[p3].world_pos - vlist[p1].world_pos);
		tmp.area = normal.length() / 2;
		normal.normalize();
		tmp.normal = normal;

		plist.push_back(tmp);

		//与顶点的图元索引绑定
		vlist[p1].index_of_plist.push_back(plist.size() - 1);
		vlist[p2].index_of_plist.push_back(plist.size() - 1);
		vlist[p3].index_of_plist.push_back(plist.size() - 1);
	}

	inline void update_normal_obj()
	{
		int flag=0;
		//更新法向量
		for (auto &tri : plist)
			tri.update_normal_tri();
		//更新顶点法向量
		for (auto &vertex : vlist)
		{
			for (auto &IOP1 : vertex.index_of_plist)
			{
				//判断共面
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
