#pragma once
#include"Math3D.h"
#include "Geometry.h"
#include<iostream>
//=====================================================================
// �����
//=====================================================================

//UVNģ��
class camera_UVN
{
private:
	float distance;//������ӵ�ľ���
	float r;//����ĳ��Բ�İ뾶
public:
	Vector4D lookat;
	Vector4D u, v, n;
	Vector4D cam_pos;//���λ��
	float far_z, near_z;//Զ��������
	float FOV_of_horizon;//�ӳ���
	int viewport_width, viewport_height;//��Ļ��С��
	float aspect;
	float d;

	camera_UVN() = default;
	//��ʼ�����
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


	//�������
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
// ��ˮ�ߣ�����任
//=====================================================================
class transform_t
{
public:
	Matrix4X4 Object, World, Camera, Screen;

	transform_t();

	//�ֲ��任
	void Object_self(Geom_Object &o,const float &sx = 1, const float &sy = 1, const float &sz = 1,
		const Vector4D &axis1 = Vector4D(0, 0, 0), const float &theta1 = 0,
		const Vector4D &axis2 = Vector4D(0, 0, 0), const float &theta2 = 0,
		const Vector4D &axis3 = Vector4D(0, 0, 0), const float &theta3 = 0);
	//�ֲ�->����
	void Object_to_World(Geom_Object &o);
	//��������ϵ�н��б��������������޳�
	//��������
	void back_cull(Geom_Object &o, const camera_UVN camera);
	//�����޳�
	void frustum_cull(Geom_Object &o, const camera_UVN camera);
	//����->���
	void World_to_Camera(Geom_Object &o,const camera_UVN &camera);
	//���->͸��
	void Camera_to_Perspective_to_Screen(Geom_Object &o,const camera_UVN &camera);

};
