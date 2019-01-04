#pragma once
#include"Math3D.h"
#include "Geometry.h"
#include<iostream>
//=====================================================================
// 摄像机
//=====================================================================

//UVN模型
class camera_UVN
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

	camera_UVN() = default;
	//初始化相机
	camera_UVN(const Vector4D &at, const Vector4D &pos, float farz, float nearz, int W, int H, float fov_of_h = 90);

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

	//inline void camera_rotate_object_axis(const Vector4D &axis1 = Vector4D(0, 0, 0), const float &theta1 = 0,
	//	const Vector4D &axis2 = Vector4D(0, 0, 0), const float &theta2 = 0,
	//	const Vector4D &axis3 = Vector4D(0, 0, 0), const float &theta3 = 0)
	//{
	//	Matrix4X4 rotate1, rotate2, rotate3;
	//	rotate1.set_identity();
	//	rotate2.set_identity();
	//	rotate3.set_identity();

	//	rotate1.set_rotate(axis1, theta1);
	//	rotate2.set_rotate(axis2, theta2);
	//	rotate3.set_rotate(axis3, theta3);

	//	n = matrix_applyToVector(n, rotate1*rotate2*rotate3);
	//	n.normalize();
	//	cam_pos = lookat - n;
	//	cam_pos.normalize();
	//	cam_pos *= distance;
	//}	


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
// 流水线：坐标变换
//=====================================================================
class transform_t
{
public:
	Matrix4X4 Object, World, Camera, Screen;

	transform_t();

	//局部变换
	void Object_self(Geom_Object &o,const float &sx = 1, const float &sy = 1, const float &sz = 1,
		const Vector4D &axis1 = Vector4D(0, 0, 0), const float &theta1 = 0,
		const Vector4D &axis2 = Vector4D(0, 0, 0), const float &theta2 = 0,
		const Vector4D &axis3 = Vector4D(0, 0, 0), const float &theta3 = 0);
	//局部->世界
	void Object_to_World(Geom_Object &o);
	//世界坐标系中进行背面消隐和物体剔除
	//背面消隐
	void back_cull(Geom_Object &o, const camera_UVN camera);
	//物体剔除
	void frustum_cull(Geom_Object &o, const camera_UVN camera);
	//世界->相机
	void World_to_Camera(Geom_Object &o,const camera_UVN &camera);
	//相机->透视
	void Camera_to_Perspective_to_Screen(Geom_Object &o,const camera_UVN &camera);

};
