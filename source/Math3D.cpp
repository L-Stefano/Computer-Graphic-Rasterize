#include "Math3D.h"
Vector2D::Vector2D(float ix, float iy) : x(ix), y(iy) {}
Vector2D::Vector2D(const Vector2D & a) : x(a.x), y(a.y) {}

Vector3D::Vector3D(float ix, float iy, float iz) : x(ix), y(iy), z(iz) {}
Vector3D::Vector3D(const Vector3D & a) : x(a.x), y(a.y), z(a.z) {}

Vector4D::Vector4D()
{
	x = y = z = 0;
	w = 1;
}

Vector4D::Vector4D(float ix, float iy, float iz, float iw)
{ 
	if (iw != 0 || iw != 1)
		w = 1;
	else
		w = iw;
	x = ix;
	y = iy;
	z = iz;

}

Vector4D::Vector4D(const Vector4D & a) : x(a.x), y(a.y), z(a.z), w(a.w) {}


Matrix4X4::Matrix4X4()
{
	set_zero();
}

Matrix4X4::Matrix4X4(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33)
{
	M00 = m00; M01 = m01; M02 = m02; M03 = m03;
	M10 = m10; M11 = m11; M12 = m12; M13 = m13;
	M20 = m20; M21 = m21; M22 = m22; M23 = m23;
	M30 = m30; M31 = m31; M32 = m32; M33 = m33;
}

//矩阵*标量(返回新的矩阵)
Matrix4X4 matrix_scale(const Matrix4X4 & mat, float scale)
{
	Matrix4X4 result;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result.m[i][j] = mat.m[i][j] * scale;
		}
	}
	return result;
}

//应用矩阵变换到向量(返回新的4D向量)(行向量左乘矩阵)(p'=p*M)
Vector4D matrix_applyToVector(const Vector4D & v, const Matrix4X4 & mat)
{
	Vector4D result;

		for (int j = 0; j < 4; j++)
		{
			result.x = v.x*mat.m[0][0] + v.y*mat.m[1][0] + v.z *mat.m[2][0] + v.w *mat.m[3][0];
			result.y = v.x*mat.m[0][1] + v.y*mat.m[1][1] + v.z *mat.m[2][1] + v.w *mat.m[3][1];
			result.z = v.x*mat.m[0][2] + v.y*mat.m[1][2] + v.z *mat.m[2][2] + v.w *mat.m[3][2];
			result.w = v.x*mat.m[0][3] + v.y*mat.m[1][3] + v.z *mat.m[2][3] + v.w *mat.m[3][3];
		}
	
	return result;
}

ColorRGB::ColorRGB(float ir_ratio, float ig_ratio, float ib_ratio)
{
	if (ir_ratio > 1) R_ratio = 1;
	if (ir_ratio > 1) G_ratio = 1;
	if (ir_ratio > 1) B_ratio = 1;
	R_ratio = ir_ratio;
	G_ratio = ig_ratio;
	B_ratio = ib_ratio;
}


ColorRGB::ColorRGB(const ColorRGB & a)
{
	this->R_ratio = a.R_ratio;
	this->G_ratio = a.G_ratio;
	this->B_ratio = a.B_ratio;
}
