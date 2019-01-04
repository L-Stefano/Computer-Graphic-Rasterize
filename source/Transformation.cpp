#include "Transformation.h"

camera_UVN::camera_UVN(const Vector4D & at, const Vector4D & pos, float farz, float nearz, int W, int H, float v_of_h)
{
	//距离
	distance = vector_distance(pos, at);

	lookat = at;
	cam_pos = pos;
	n = lookat - cam_pos;
	u = vector_crossproduct(n, Vector4D(0, 1, 0));
	v = vector_crossproduct(u, n);
	n.normalize();
	v.normalize();
	u.normalize();

	viewport_width = W;
	viewport_height = H;
	aspect = (float)viewport_width / viewport_height;

	far_z = farz;
	near_z = nearz;

	FOV_of_horizon = v_of_h;
	d = 0.5f*(viewport_width - 1)*1.0f / tanf(deg_to_rad(FOV_of_horizon*0.5f));
}
transform_t::transform_t()
{
	Object.set_identity();
}
//局部变换
void transform_t::Object_self(Geom_Object &o, const float &sx, const float &sy, const float &sz,
	const Vector4D &axis1, const float &theta1,
	const Vector4D &axis2, const float &theta2,
	const Vector4D &axis3, const float &theta3)
{
	//计算矩阵
	Matrix4X4 scale, rotate1, rotate2, rotate3;
	rotate1.set_identity();
	rotate2.set_identity();
	rotate3.set_identity();

	scale.set_scale(sx, sy, sz);
	rotate1.set_rotate(axis1, theta1);
	rotate2.set_rotate(axis2, theta2);
	rotate3.set_rotate(axis3, theta3);

	Object = scale * rotate1 * rotate2 * rotate3;

	//应用变换
	for (auto &tri : o.plist)
	{
		for (auto &vertexs : tri.vlist)
		{
			vertexs.trans = matrix_applyToVector(vertexs.world_pos, Object);
			vertexs.self_trans = vertexs.trans;
		}
	}
	o.update_normal_obj();
}
//局部->世界
void transform_t::Object_to_World(Geom_Object &o)
{
	//计算矩阵
	World.set_translation(o.world_pos.x, o.world_pos.y, o.world_pos.z);
	//应用变换
	for (auto &tri : o.plist)
	{
		for (auto &vertexs : tri.vlist)
		{
			vertexs.trans = matrix_applyToVector(vertexs.trans, World);
			vertexs.self_trans = matrix_applyToVector(vertexs.self_trans, World);
		}
	}
}

void transform_t::back_cull(Geom_Object & o, const camera_UVN camera)
{
	if (!o.back_cull)
		return;
	for (Geom_Triangle &i : o.plist)
	{
		if (vector_dotproduct(camera.cam_pos - i.vlist[0].self_trans, i.normal) <= 0)
			i.visible = false;
		else if (vector_dotproduct(camera.cam_pos - i.vlist[0].self_trans, i.normal) > 0)
			i.visible = true;
	}
}

void transform_t::frustum_cull(Geom_Object & o, const camera_UVN camera)
{
	if (!o.frustum_cull)
		return;
	Matrix4X4 Camera_for_frustum_cull;
	//计算矩阵
	Camera_for_frustum_cull.set_identity();
	Camera_for_frustum_cull.M00 = camera.u.x; Camera_for_frustum_cull.M01 = camera.v.x; Camera_for_frustum_cull.M02 = camera.n.x;
	Camera_for_frustum_cull.M10 = camera.u.y; Camera_for_frustum_cull.M11 = camera.v.y; Camera_for_frustum_cull.M12 = camera.n.y;
	Camera_for_frustum_cull.M20 = camera.u.z; Camera_for_frustum_cull.M21 = camera.v.z; Camera_for_frustum_cull.M22 = camera.n.z;
	Camera_for_frustum_cull.M30 = -vector_dotproduct(camera.cam_pos, camera.u);
	Camera_for_frustum_cull.M31 = -vector_dotproduct(camera.cam_pos, camera.v);
	Camera_for_frustum_cull.M32 = -vector_dotproduct(camera.cam_pos, camera.n);

	o.center = matrix_applyToVector(o.world_pos, Camera_for_frustum_cull);
	o.left = o.center - Vector4D(o.r, 0, 0);
	o.right = o.center + Vector4D(o.r, 0, 0);
	o.up = o.center + Vector4D(0, o.r, 0);
	o.bottom = o.center - Vector4D(0, o.r, 0);
	o.front = o.center + Vector4D(0, 0, o.r);
	o.back = o.center - Vector4D(0, 0, o.r);

	//X和Y
	//分别是左右裁切面和上下裁切面
	//测试各个点是否在的范围
	float X, Y;
	//利用了相似三角形
	X = camera.viewport_width*0.5f*o.center.z / camera.d;
	Y = camera.viewport_height*0.5f*o.center.z / camera.d;

	if ((o.right.x < -X) || (o.left.x > X) || (o.bottom.y > Y) || (o.up.y < -Y) || (o.front.z < camera.near_z) || (o.back.z > camera.far_z))
		o.visible = false;
}

//世界->相机
void transform_t::World_to_Camera(Geom_Object &o, const camera_UVN &camera)
{
	//物体可见性判断
	if (!o.visible)
	{
		return;
	}
	//计算矩阵
	Camera.set_identity();
	Camera.M00 = camera.u.x; Camera.M01 = camera.v.x; Camera.M02 = camera.n.x;
	Camera.M10 = camera.u.y; Camera.M11 = camera.v.y; Camera.M12 = camera.n.y;
	Camera.M20 = camera.u.z; Camera.M21 = camera.v.z; Camera.M22 = camera.n.z;
	Camera.M30 = -vector_dotproduct(camera.cam_pos, camera.u);
	Camera.M31 = -vector_dotproduct(camera.cam_pos, camera.v);
	Camera.M32 = -vector_dotproduct(camera.cam_pos, camera.n);


	//应用变换
	for (auto &tri : o.plist)
	{
		//背面可见性判断
		if (!tri.visible)
		{
			continue;
		}
		for (auto &vertexs : tri.vlist)
		{
			vertexs.trans = matrix_applyToVector(vertexs.trans, Camera);
		}
	}
}
//相机->透视
void transform_t::Camera_to_Perspective_to_Screen(Geom_Object &o, const camera_UVN &camera)
{
	//物体可见性判断
	if (!o.visible)
	{
		return;
	}
	//计算矩阵
	Screen.set_identity();
	Screen.M00 = camera.d;
	Screen.M11 = -camera.d * camera.aspect;
	Screen.M23 = 1;
	Screen.M20 = 0.5f*camera.viewport_width - 0.5;
	Screen.M21 = 0.5f*camera.viewport_height - 0.5;
	Screen.M33 = 0;

	//应用变换
	for (auto &tri : o.plist)
	{
		//背面可见性判断
		if (!tri.visible)
		{
			continue;
		}
		for (auto &vertexs : tri.vlist)
		{
			vertexs.trans = matrix_applyToVector(vertexs.trans, Screen);
			vertexs.z = vertexs.trans.z;
			vertexs.trans /= vertexs.trans.w;
		}
	}
}