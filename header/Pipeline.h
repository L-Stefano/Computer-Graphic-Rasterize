#pragma once
#include"Math3D.h"
#include "Geometry.h"
#include<iostream>
//=====================================================================
// 摄像机
//=====================================================================

//UVN模型
class Camera_UVN
{
private:
	float distance;//相机距视点的距离
	float r;//绕轴某个圆的半径
public:
	Vector4D lookat;
	Vector4D u, v, n;
	Vector4D cam_pos;//相机位置
	float far_z, near_z;//远近裁切面
	float FOV_of_horizon;//视场角
	int viewport_width, viewport_height;//屏幕大小；
	float aspect;
	float d;

	Camera_UVN() = default;
	//初始化相机
	Camera_UVN(const Vector4D &at, const Vector4D &pos, float farz, float nearz, int W, int H, float fov_of_h = 90);

	inline void camera_rotate_self_axis(const Vector4D &axis1 = Vector4D(0, 0, 0), const float &theta1 = 0,
		const Vector4D &axis2 = Vector4D(0, 0, 0), const float &theta2 = 0,
		const Vector4D &axis3 = Vector4D(0, 0, 0), const float &theta3 = 0)
	{
		Matrix4X4 rotate1, rotate2, rotate3;
		rotate1.set_identity();
		rotate2.set_identity();
		rotate3.set_identity();

		rotate1.set_rotate(axis1, theta1);
		rotate2.set_rotate(axis2, theta2);
		rotate3.set_rotate(axis3, theta3);

		n = matrix_applyToVector(n, rotate1*rotate2*rotate3);
		n.normalize();
		lookat = n + cam_pos;
	}

	//更新相机
	inline void camera_update()
	{
		n = lookat - cam_pos;
		u = vector_crossproduct(n, Vector4D(0, 1, 0));
		v = vector_crossproduct(u, n);
		n.normalize();
		v.normalize();
		u.normalize();

		distance = vector_distance(cam_pos, lookat);
		d = 0.5f*(viewport_width - 1)*1.0f / tanf(deg_to_rad(FOV_of_horizon*0.5f));
	}

};

//=====================================================================
// 坐标变换
//=====================================================================
class Transform_t
{
public:
	Matrix4X4 Object, World, Camera, Screen;

	Transform_t();

	//局部变换
	void Object_self(Geom_Object &o, const float &sx = 1, const float &sy = 1, const float &sz = 1,
		const Vector4D &axis1 = Vector4D(0, 0, 0), const float &theta1 = 0,
		const Vector4D &axis2 = Vector4D(0, 0, 0), const float &theta2 = 0,
		const Vector4D &axis3 = Vector4D(0, 0, 0), const float &theta3 = 0);
	//局部->世界
	void Object_to_World(Geom_Object &o);
	//世界坐标系中进行背面消隐和物体剔除
	//背面消隐
	void back_cull(Geom_Object &o, const Camera_UVN camera);
	//物体剔除
	void frustum_cull(Geom_Object &o, const Camera_UVN camera);
	//世界->相机
	void World_to_Camera(Geom_Object &o, const Camera_UVN &camera);
	//相机->透视
	void Camera_to_Perspective_to_Screen(Geom_Object &o, const Camera_UVN &camera);

	//不包含局部变换
	void pipeline_object(Geom_Object &o, const Camera_UVN &camera);
	void pipeline_renderlist(Render_List &render_list, const Camera_UVN &camera);
};
////=====================================================================
//// 光照计算
////=====================================================================
////在世界坐标中进行计算
////Lambert漫反射模型
//inline void shading_calculate(Geom_Object &o, Light_List light_list)
//{
//	ColorRGB i_total_ambient(0, 0, 0);
//	//计算环境光
//	for (auto &ambient : light_list.ambient_light_list)
//		if (ambient.active)
//			i_total_ambient += ambient.intensity_light * o.material.ka;
//	//对每个顶点计算散射光
//	for (auto &vertices : o.vlist)
//	{
//		ColorRGB i_total_diffuse(0, 0, 0);
//		//计算平行光
//		for (auto &infinitelight : light_list.infinite_light_list)
//		{
//			if (infinitelight.active)
//			{
//				//散射项夹角的余弦
//				float cos_angle = vector_dotproduct((-infinitelight.direction), vertices.normal_vertex);
//				if (cos_angle > 0)
//					i_total_diffuse += infinitelight.intensity_light * o.material.kd*cos_angle;
//			}
//		}
//		//计算点光源
//		for (auto &pointlight : light_list.point_light_list)
//		{
//			if (pointlight.active)
//			{
//				//光源与顶点的距离
//				float distance = vector_distance(pointlight.position, vertices.world_trans);
//				i_total_diffuse += (pointlight.intensity_light / (pointlight.kc + pointlight.kl*distance + pointlight.kq*distance*distance))*o.material.kd;
//			}
//		}
//		//计算聚光灯
//		for (auto &spotlight : light_list.spotlight_list)
//		{
//			if (spotlight.active)
//			{
//				//散射项夹角的余弦
//				float dotproduct = vector_dotproduct(spotlight.direction, vertices.normal_vertex);
//				//光源与顶点的距离
//				float distance = vector_distance(spotlight.position, vertices.world_trans);
//				//聚光灯朝向与顶点的所成夹角的度数
//				float angle_of_lightdir_vertex = vector_angle(spotlight.direction, vertices.world_trans - spotlight.position);
//				if (dotproduct > 0)
//					if (angle_of_lightdir_vertex > spotlight.penumbra)//位于半影外
//						continue;
//					else if (angle_of_lightdir_vertex < spotlight.umbra)//位于本影内
//						i_total_diffuse += (spotlight.intensity_light / (spotlight.kc + spotlight.kl*distance + spotlight.kq*distance*distance))*o.material.kd*dotproduct;
//					else if (angle_of_lightdir_vertex > spotlight.umbra&&angle_of_lightdir_vertex < spotlight.penumbra)//位于本影半影之间
//						i_total_diffuse += ((spotlight.intensity_light / (spotlight.kc + spotlight.kl*distance + spotlight.kq*distance*distance))*
//						(powf(cosf(angle_of_lightdir_vertex) - cosf(spotlight.penumbra), spotlight.pf) / (cosf(spotlight.umbra) - cosf(spotlight.penumbra))))*o.material.kd*dotproduct;
//			}
//		}
//		vertices.diffuse_total = i_total_diffuse;
//		vertices.ambient_total = i_total_ambient;
//	}
//	for (auto &tri : o.plist)
//	{
//		tri.vlist[0].ambient_total = o.vlist[tri.p[0]].ambient_total;
//		tri.vlist[0].diffuse_total = o.vlist[tri.p[0]].diffuse_total;
//		tri.vlist[1].ambient_total = o.vlist[tri.p[1]].ambient_total;
//		tri.vlist[1].diffuse_total = o.vlist[tri.p[1]].diffuse_total;
//		tri.vlist[2].ambient_total = o.vlist[tri.p[2]].ambient_total;
//		tri.vlist[2].diffuse_total = o.vlist[tri.p[2]].diffuse_total;
//	}
//}