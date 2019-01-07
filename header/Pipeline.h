#pragma once
#include"Math3D.h"
#include "Geometry.h"
#include<iostream>
//=====================================================================
// �����
//=====================================================================

//UVNģ��
class Camera_UVN
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

	Camera_UVN() = default;
	//��ʼ�����
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
// ����任
//=====================================================================
class Transform_t
{
public:
	Matrix4X4 Object, World, Camera, Screen;

	Transform_t();

	//�ֲ��任
	void Object_self(Geom_Object &o, const float &sx = 1, const float &sy = 1, const float &sz = 1,
		const Vector4D &axis1 = Vector4D(0, 0, 0), const float &theta1 = 0,
		const Vector4D &axis2 = Vector4D(0, 0, 0), const float &theta2 = 0,
		const Vector4D &axis3 = Vector4D(0, 0, 0), const float &theta3 = 0);
	//�ֲ�->����
	void Object_to_World(Geom_Object &o);
	//��������ϵ�н��б��������������޳�
	//��������
	void back_cull(Geom_Object &o, const Camera_UVN camera);
	//�����޳�
	void frustum_cull(Geom_Object &o, const Camera_UVN camera);
	//����->���
	void World_to_Camera(Geom_Object &o, const Camera_UVN &camera);
	//���->͸��
	void Camera_to_Perspective_to_Screen(Geom_Object &o, const Camera_UVN &camera);

	//�������ֲ��任
	void pipeline_object(Geom_Object &o, const Camera_UVN &camera);
	void pipeline_renderlist(Render_List &render_list, const Camera_UVN &camera);
};
////=====================================================================
//// ���ռ���
////=====================================================================
////�����������н��м���
////Lambert������ģ��
//inline void shading_calculate(Geom_Object &o, Light_List light_list)
//{
//	ColorRGB i_total_ambient(0, 0, 0);
//	//���㻷����
//	for (auto &ambient : light_list.ambient_light_list)
//		if (ambient.active)
//			i_total_ambient += ambient.intensity_light * o.material.ka;
//	//��ÿ���������ɢ���
//	for (auto &vertices : o.vlist)
//	{
//		ColorRGB i_total_diffuse(0, 0, 0);
//		//����ƽ�й�
//		for (auto &infinitelight : light_list.infinite_light_list)
//		{
//			if (infinitelight.active)
//			{
//				//ɢ����нǵ�����
//				float cos_angle = vector_dotproduct((-infinitelight.direction), vertices.normal_vertex);
//				if (cos_angle > 0)
//					i_total_diffuse += infinitelight.intensity_light * o.material.kd*cos_angle;
//			}
//		}
//		//������Դ
//		for (auto &pointlight : light_list.point_light_list)
//		{
//			if (pointlight.active)
//			{
//				//��Դ�붥��ľ���
//				float distance = vector_distance(pointlight.position, vertices.world_trans);
//				i_total_diffuse += (pointlight.intensity_light / (pointlight.kc + pointlight.kl*distance + pointlight.kq*distance*distance))*o.material.kd;
//			}
//		}
//		//����۹��
//		for (auto &spotlight : light_list.spotlight_list)
//		{
//			if (spotlight.active)
//			{
//				//ɢ����нǵ�����
//				float dotproduct = vector_dotproduct(spotlight.direction, vertices.normal_vertex);
//				//��Դ�붥��ľ���
//				float distance = vector_distance(spotlight.position, vertices.world_trans);
//				//�۹�Ƴ����붥������ɼнǵĶ���
//				float angle_of_lightdir_vertex = vector_angle(spotlight.direction, vertices.world_trans - spotlight.position);
//				if (dotproduct > 0)
//					if (angle_of_lightdir_vertex > spotlight.penumbra)//λ�ڰ�Ӱ��
//						continue;
//					else if (angle_of_lightdir_vertex < spotlight.umbra)//λ�ڱ�Ӱ��
//						i_total_diffuse += (spotlight.intensity_light / (spotlight.kc + spotlight.kl*distance + spotlight.kq*distance*distance))*o.material.kd*dotproduct;
//					else if (angle_of_lightdir_vertex > spotlight.umbra&&angle_of_lightdir_vertex < spotlight.penumbra)//λ�ڱ�Ӱ��Ӱ֮��
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