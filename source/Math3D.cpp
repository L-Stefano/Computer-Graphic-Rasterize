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

Vector4D::Vector4D(float ix, float iy, float iz, float iw) : x(ix), y(iy), z(iz) { if (iw != 0 || iw != 1)w = 1; }

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
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result[i] = v.x*mat.m[0][i] + v.y*mat.m[1][i] + v.z *mat.m[2][i] + v.w *mat.m[3][i];
		}
	}
	return result;
}

ColorRGB::ColorRGB(int ir, int ig, int ib)
{
	if ((ir < 0 || ir>255) || (ig < 0 || ig>255) || (ib < 0 || ib>255))
		throw std::logic_error("Wrong Value of RGB");
	R = ir;
	G = ig;
	B = ib;
	R_ratio = (float)R / 255;
	G_ratio = (float)G / 255;
	B_ratio = (float)B / 255;
}

ColorRGB::ColorRGB(float ir_ratio, float ig_ratio, float ib_ratio)
{
	if ((ir_ratio < 0 || ir_ratio>1) || (ig_ratio < 0 || ig_ratio>1) || (ib_ratio < 0 || ib_ratio>1))
		throw std::logic_error("Wrong Value of RGB");
	R_ratio = ir_ratio;
	G_ratio = ig_ratio;
	B_ratio = ib_ratio;
	R = ir_ratio * 255;
	G = ig_ratio * 255;
	B = ib_ratio * 255;
}


ColorRGB::ColorRGB(const ColorRGB & a)
{
	this->R = a.R;
	this->G = a.G;
	this->B = a.B;
	this->R_ratio = a.R_ratio;
	this->G_ratio = a.G_ratio;
	this->B_ratio = a.B_ratio;
}
