#pragma once
#include <assert.h>
#include <math.h>
#include <algorithm>
#include <iostream>
//=====================================================================
// ����
//=====================================================================
const double PI = 3.141592653589793;
//=====================================================================
// ���ȡ��ǶȻ���
//=====================================================================
inline float rad_to_deg(float rad)
{
	return rad * (180 / PI);
}
inline float deg_to_rad(float deg)
{
	return deg * (PI / 180);
}

//=====================================================================
// ʸ��
//=====================================================================
typedef class Vector2D
{
public:
	union
	{
		float M[2];
		struct
		{
			float x, y;
		};
	};

	/*���캯��*/
	//Ĭ�Ϲ��캯��;
	Vector2D() = default;
	//��ʼ��x, y ,z
	Vector2D(float ix, float iy);
	//�������캯��
	Vector2D(const Vector2D &a);



	//��������
	~Vector2D() = default;

	/*���������*/
	//v1+v2
	inline Vector2D operator +(const Vector2D &v)const
	{
		return Vector2D(this->x + v.x, this->y + v.y);
	}
	inline Vector2D& operator +=(const Vector2D &v)
	{
		this->x += v.x;
		this->y += v.y;
		return *this;
	}
	//v1-v2
	inline Vector2D operator -(const Vector2D &v)const
	{
		return Vector2D(this->x - v.x, this->y - v.y);
	}
	inline Vector2D& operator -=(const Vector2D &v)
	{
		this->x -= v.x;
		this->y -= v.y;
		return *this;
	}
	//-v
	inline Vector2D  operator -() const
	{
		return Vector2D(-x, -y);
	}
	//�������Ա���
	inline Vector2D operator /(const float v)const
	{
		assert(v);
		return Vector2D(this->x / v, this->y / v);
	}
	inline Vector2D& operator /=(const float v)
	{
		assert(v);
		this->x /= v;
		this->y /= v;
		return *this;
	}
	//�������Ա���
	inline Vector2D operator *(const float v)const
	{
		return Vector2D(this->x * v, this->y * v);
	}
	inline Vector2D& operator *=(const float v)
	{
		this->x *= v;
		this->y *= v;
		return *this;
	}
	//�����±������
	inline float& operator[](size_t n)
	{
		return M[n];
	}
	inline const float& operator[](size_t n)const
	{
		return M[n];
	}

	/*����*/
	inline float length() const
	{
		return (float)sqrt(x*x + y * y);
	}

	/*��һ��*/
	inline void normalize()
	{
		float len = this->length();
		if (len != 0.0f)
			(*this) /= len;
	}

	inline void print()
	{
		std::cout << x << std::ends << y << std::endl;
	}

}Point2D;
typedef class Vector3D
{
public:
	union
	{
		float M[3];
		struct
		{
			float x, y, z;
		};
	};

	/*���캯��*/
	//Ĭ�Ϲ��캯��;
	Vector3D() = default;
	//��ʼ��x, y ,z
	Vector3D(float ix, float iy, float iz);
	//�������캯��
	Vector3D(const Vector3D &a);
	//��������
	~Vector3D() = default;

	/*���������*/
	//v1+v2
	inline Vector3D operator +(const Vector3D &v)const
	{
		return Vector3D(this->x + v.x, this->y + v.y, this->z + v.z);
	}
	inline Vector3D& operator +=(const Vector3D &v)
	{
		this->x += v.x;
		this->y += v.y;
		this->z += v.z;
		return *this;
	}
	//v1-v2
	inline Vector3D operator -(const Vector3D &v)const
	{
		return Vector3D(this->x - v.x, this->y - v.y, this->z - v.z);
	}
	inline Vector3D& operator -=(const Vector3D &v)
	{
		this->x -= v.x;
		this->y -= v.y;
		this->z -= v.z;
		return *this;
	}
	//-v
	inline Vector3D  operator -() const
	{
		return Vector3D(-x, -y, -z);
	}
	//�������Ա���
	inline Vector3D operator /(const float v)const
	{
		assert(v);
		return Vector3D(this->x / v, this->y / v, this->z / v);
	}
	inline Vector3D& operator /=(const float v)
	{
		assert(v);
		this->x /= v;
		this->y /= v;
		this->z /= v;
		return *this;
	}
	//�������Ա���
	inline Vector3D operator *(const float v)const
	{
		return Vector3D(this->x * v, this->y * v, this->z * v);
	}
	inline Vector3D& operator *=(const float v)
	{
		this->x *= v;
		this->y *= v;
		this->z *= v;
		return *this;
	}
	//�����±������
	inline float& operator[](size_t n)
	{
		return M[n];
	}
	inline const float& operator[](size_t n)const
	{
		return M[n];
	}

	/*����*/
	inline float length() const
	{
		return (float)sqrt(x*x + y * y + z * z);
	}

	/*��һ��*/
	inline void normalize()
	{
		float len = this->length();
		if (len != 0.0f)
			(*this) /= len;
	}

	inline void print()
	{
		std::cout << x << std::ends << y << std::ends << z << std::endl;
	}

}Point3D;
typedef class Vector4D
{
public:
	union
	{
		float M[4];
		struct
		{
			float x, y, z, w;
		};
	};

	/*���캯��*/
	//Ĭ�Ϲ��캯��;
	Vector4D();
	//��ʼ��x, y ,z
	Vector4D(float ix, float iy, float iz, float iw = 1);

	//ת����Vector2D
	inline Vector2D toVec2D()
	{
		return Vector2D(x, y);
	}

	//�������캯��
	Vector4D(const Vector4D &a);
	//��������
	~Vector4D() = default;

	/*���������*/
	//v1+v2
	inline Vector4D operator +(const Vector4D &v)const
	{
		return Vector4D(this->x + v.x, this->y + v.y, this->z + v.z, 1);
	}
	inline Vector4D& operator +=(const Vector4D &v)
	{
		this->x += v.x;
		this->y += v.y;
		this->z += v.z;
		return *this;
	}
	//v1-v2
	inline Vector4D operator -(const Vector4D &v)const
	{
		return Vector4D(this->x - v.x, this->y - v.y, this->z - v.z, 1);
	}
	inline Vector4D& operator -=(const Vector4D &v)
	{
		this->x -= v.x;
		this->y -= v.y;
		this->z -= v.z;
		return *this;
	}
	//-v
	inline Vector4D  operator -() const
	{
		return Vector4D(-x, -y, -z, w);
	}
	//�������Ա���
	inline Vector4D operator /(const float v)const
	{
		assert(v);
		return Vector4D(this->x / v, this->y / v, this->z / v, w);
	}
	inline Vector4D& operator /=(const float v)
	{
		assert(v);
		this->x /= v;
		this->y /= v;
		this->z /= v;
		return *this;
	}
	//�������Ա���
	inline Vector4D operator *(const float v)const
	{
		return Vector4D(this->x * v, this->y * v, this->z * v, w);
	}
	inline Vector4D& operator *=(const float v)
	{
		this->x *= v;
		this->y *= v;
		this->z *= v;
		return *this;
	}
	//�����±������
	inline float& operator[](size_t n)
	{
		return M[n];
	}
	inline const float& operator[](size_t n)const
	{
		return M[n];
	}
	//�����ж�
	inline bool operator == (const Vector4D &v)const
	{
		if ((x == v.x)&&(y == v.y)&&(z == v.z))
			return true;
		else
			return false;
	}
	/*����*/
	inline float length() const
	{
		return sqrtf(x*x + y * y + z * z);
	}

	/*��һ��*/
	inline void normalize()
	{
		float len = this->length();
		if (len != 0.0f)
			(*this) /= len;

	}



	inline void print()
	{
		std::cout << x << std::ends << y << std::ends << z << std::ends << w << std::endl;
	}
}Point4D;

//���
inline float vector_dotproduct(const Vector2D &v1, const Vector2D &v2)
{
	return v1.x*v2.x + v1.y*v2.y;
}
inline float vector_dotproduct(const Vector3D &v1, const Vector3D &v2)
{
	return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}
inline float vector_dotproduct(const Vector4D &v1, const Vector4D &v2)
{
	return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

//���
inline Vector3D vector_crossproduct(const Vector3D &v1, const Vector3D &v2)
{
	return -Vector3D(v1.y*v2.z - v1.z*v2.y, v1.z*v2.x - v1.x*v2.z, v1.x*v2.y - v1.y*v2.x);
}
inline Vector4D vector_crossproduct(const Vector4D &v1, const Vector4D &v2)
{
	return -Vector4D(v1.y*v2.z - v1.z*v2.y, v1.z*v2.x - v1.x*v2.z, v1.x*v2.y - v1.y*v2.x);
}

// ����
inline float vector_length(Vector2D &v)
{
	return (float)sqrt(v.x*v.x + v.y*v.y);
}
inline float vector_length(Vector3D &v)
{
	return (float)sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}
inline float vector_length(Vector4D &v)
{
	return (float)sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}

// ʸ����һ��
inline void vector_normalize(Vector2D &v)
{
	float length = vector_length(v);
	if (length != 0.0f)
		v /= length;
}
inline void vector_normalize(Vector3D &v)
{
	float length = vector_length(v);
	if (length != 0.0f)
		v /= length;
}
inline void vector_normalize(Vector4D &v)
{
	float length = vector_length(v);
	if (length != 0.0f)
		v /= length;

}

//����
inline float vector_distance(const Vector4D &v1, const Vector4D &v2)
{
	return(sqrtf(powf(v1.length(), 2) +powf(v2.length(), 2)));
}

//�нǣ��Ƕ���)
inline float vector_angle(const Vector2D &v1, const Vector2D &v2)
{
	return rad_to_deg(acosf(vector_dotproduct(v1, v2) / (v1.length()*v2.length())));
}
//������
inline float vector_angle(const Vector3D &v1, const Vector3D &v2)
{
	return acosf(vector_dotproduct(v1, v2) / (v1.length()*v2.length()));
}
//������
inline float vector_angle(const Vector4D &v1, const Vector4D &v2)
{
	return acosf(vector_dotproduct(v1, v2) / (v1.length()*v2.length()));
}

//=====================================================================
// ����
//=====================================================================

//��ά��ξ���
class Matrix4X4
{
public:
	union
	{
		float m[4][4];
		struct
		{
			float M00, M01, M02, M03;
			float M10, M11, M12, M13;
			float M20, M21, M22, M23;
			float M30, M31, M32, M33;
		};
	};

	Matrix4X4();

	//��ʼ������
	Matrix4X4(
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33);

	//M1+M2
	inline Matrix4X4 operator +(const Matrix4X4 &mat)const
	{
		Matrix4X4 result;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
			{
				result.m[i][j] = this->m[i][j] + mat.m[i][j];
			}
		return result;
	}
	inline Matrix4X4& operator +=(const Matrix4X4 &mat)
	{
		Matrix4X4 result;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
			{
				this->m[i][j] + mat.m[i][j];
			}
		return *this;
	}
	//M1-M2
	inline Matrix4X4 operator -(const Matrix4X4 &mat)const
	{
		Matrix4X4 result;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
			{
				result.m[i][j] = this->m[i][j] - mat.m[i][j];
			}
		return result;
	}
	inline Matrix4X4& operator -=(const Matrix4X4 &mat)
	{
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
			{
				this->m[i][j] - mat.m[i][j];
			}
		return *this;
	}
	//M1*M2(�������)
	inline Matrix4X4 operator *(const Matrix4X4 &mat)const
	{
		Matrix4X4 result;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
			{
				result.m[i][j] =
					this->m[i][0] * mat.m[0][j] +
					this->m[i][1] * mat.m[1][j] +
					this->m[i][2] * mat.m[2][j] +
					this->m[i][3] * mat.m[3][j];
			}
		return result;
	}
	inline Matrix4X4& operator *=(const Matrix4X4 &mat)
	{
		*this = this->operator*(mat);
		return *this;
	}

	//����
	inline void set_zero()
	{
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				m[i][j] = 0;
	}
	//�õ�λ����
	inline void set_identity()
	{
		set_zero();
		M00 = M11 = M22 = M33 = 1.0f;
	}
	//��ƽ�ƾ���
	inline void set_translation(float dx, float dy, float dz)
	{
		set_identity();
		M30 = dx;
		M31 = dy;
		M32 = dz;
	}
	//�����ž���
	inline void set_scale(float sx, float sy, float sz)
	{
		set_identity();
		M00 = sx;
		M11 = sy;
		M22 = sz;
	}
	//����ת����(������A��תTheta�Ƕ�)
	inline void set_rotate(Vector4D A, float theta)
	{
		set_identity();
		A.normalize();

		float sin_theta = sinf(deg_to_rad(theta));
		float cos_theta = cosf(deg_to_rad(theta));

		//����������ʱ����ֵ���
		if (abs(sin_theta) < 10E-7) 
			sin_theta = 0.0f;
		if (abs(cos_theta) < 10E-7)
			cos_theta = 0.0f;

		M00 = cos_theta + (1 - cos_theta)*A.x*A.x; M01 = (1 - cos_theta)*A.x*A.y + sin_theta * A.z; M02 = (1 - cos_theta)*A.x*A.z - sin_theta * A.y;
		M10 = (1 - cos_theta)*A.x*A.y - sin_theta * A.z; M11 = cos_theta + (1 - cos_theta)*A.y*A.y; M12 = (1 - cos_theta)*A.y*A.z + sin_theta * A.x;
		M20 = (1 - cos_theta)*A.x*A.z + sin_theta * A.y; M21 = (1 - cos_theta)*A.y*A.z - sin_theta * A.x; M22 = cos_theta + (1 - cos_theta)*A.z*A.z;
	}

	//����̨����ʾMatrix
	inline void print()
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				std::cout << m[i][j] << std::ends;
			}
			std::cout << std::endl;
		}
	}

	inline bool empty()
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (m[i][j] != 0)
					return false;
			}
		}
		return true;
	}
};

//����*����(�����µľ���)
Matrix4X4 matrix_scale(const Matrix4X4 &mat, float scale);
//Ӧ�þ���任������(�����µ�4D����)(��������˾���)(p'=p*M)
Vector4D matrix_applyToVector(const Vector4D &v, const Matrix4X4 &mat);

//=====================================================================
// ��ɫ
//=====================================================================
class ColorRGB
{
public:
	union
	{
		int M[3];
		struct
		{
			int R, G, B;
		};
	};
	struct
	{
		float R_ratio, G_ratio, B_ratio;
	};

	/*���캯��*/
	//Ĭ�Ϲ��캯��;
	ColorRGB() = default;
	//��ʼ��R, G ,B
	ColorRGB(int ir, int ig, int ib);
	ColorRGB(float ir_ratio, float ig_ratio, float ib_ratio);

	//�������캯��
	ColorRGB(const ColorRGB &a);
	//��������
	~ColorRGB() = default;

	/*���������*/
	//c1+c2
	inline ColorRGB operator +(const ColorRGB &v)const
	{
		return ColorRGB(std::min(this->R + v.R,255), std::min(this->G + v.G,255), std::min(this->B + v.B,255));
	}
	//c1-c2
	inline ColorRGB operator -(const ColorRGB &v)const
	{
		return ColorRGB( this->R - v.R, this->G - v.G, this->B - v.B);
	}
	//-v
	inline ColorRGB  operator -() const
	{
		return ColorRGB(-R, -G, -B);
	}
	//���Ա���
	inline ColorRGB operator /(const float v)const
	{
		assert(v);
		return ColorRGB(this->R_ratio / v, this->G_ratio / v, this->B_ratio / v);
	}
	//��ɫ���ƣ��ұ�����������ɫ��
	inline ColorRGB operator *(const float &v)const
	{
		float R_ratio_result = this->R_ratio * v, G_ratio_result = this->G_ratio* v, B_ratio_result = this->B_ratio* v;
		if ((R_ratio_result > 255) || (G_ratio_result  > 255) || B_ratio_result  > 255)
			throw std::range_error("The component of color has reached max value.");
		else
		{
			return ColorRGB(R_ratio_result, G_ratio_result, B_ratio_result);
		}
	}
	//��ɫ����(����ɫ��������ɫ)
	inline ColorRGB operator *(const ColorRGB &c)const
	{
		return ColorRGB(c.R_ratio*this->R, c.G_ratio*this->G, c.B_ratio*this->B);
	}
	inline ColorRGB& operator *=(const ColorRGB &c)
	{
		this->R *= c.R_ratio;
		this->G *= c.G_ratio;
		this->B *= c.B_ratio;
		return *this;
	}
	//�����±������
	inline int& operator[](size_t n)
	{
		return M[n];
	}
	inline const float& operator[](size_t n)const
	{
		return M[n];
	}
	inline void print()
	{
		std::cout << R << std::ends << G << std::ends << B << std::endl;
	}
};