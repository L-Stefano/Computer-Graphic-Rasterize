#pragma once
#include <assert.h>
#include <math.h>
#include <algorithm>
#include <iostream>
//=====================================================================
// 常量
//=====================================================================
const double PI = 3.141592653589793;
//=====================================================================
// 弧度、角度换算
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
// 矢量
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

	/*构造函数*/
	//默认构造函数;
	Vector2D() = default;
	//初始化x, y ,z
	Vector2D(float ix, float iy);
	//拷贝构造函数
	Vector2D(const Vector2D &a);



	//析构函数
	~Vector2D() = default;

	/*运算符重载*/
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
	//向量除以标量
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
	//向量乘以标量
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
	//重载下标运算符
	inline float& operator[](size_t n)
	{
		return M[n];
	}
	inline const float& operator[](size_t n)const
	{
		return M[n];
	}

	/*长度*/
	inline float length() const
	{
		return (float)sqrt(x*x + y * y);
	}

	/*归一化*/
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

	/*构造函数*/
	//默认构造函数;
	Vector3D() = default;
	//初始化x, y ,z
	Vector3D(float ix, float iy, float iz);
	//拷贝构造函数
	Vector3D(const Vector3D &a);
	//析构函数
	~Vector3D() = default;

	/*运算符重载*/
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
	//向量除以标量
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
	//向量乘以标量
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
	//重载下标运算符
	inline float& operator[](size_t n)
	{
		return M[n];
	}
	inline const float& operator[](size_t n)const
	{
		return M[n];
	}

	/*长度*/
	inline float length() const
	{
		return (float)sqrt(x*x + y * y + z * z);
	}

	/*归一化*/
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

	/*构造函数*/
	//默认构造函数;
	Vector4D();
	//初始化x, y ,z
	Vector4D(float ix, float iy, float iz, float iw = 1);

	//转换到Vector2D
	inline Vector2D toVec2D()
	{
		return Vector2D(x, y);
	}

	//拷贝构造函数
	Vector4D(const Vector4D &a);
	//析构函数
	~Vector4D() = default;

	/*运算符重载*/
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
	//向量除以标量
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
	//向量乘以标量
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
	//重载下标运算符
	inline float& operator[](size_t n)
	{
		return M[n];
	}
	inline const float& operator[](size_t n)const
	{
		return M[n];
	}
	//等性判断
	inline bool operator == (const Vector4D &v)const
	{
		if ((x == v.x)&&(y == v.y)&&(z == v.z))
			return true;
		else
			return false;
	}
	/*长度*/
	inline float length() const
	{
		return sqrtf(x*x + y * y + z * z);
	}

	/*归一化*/
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

//点积
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

//叉积
inline Vector3D vector_crossproduct(const Vector3D &v1, const Vector3D &v2)
{
	return -Vector3D(v1.y*v2.z - v1.z*v2.y, v1.z*v2.x - v1.x*v2.z, v1.x*v2.y - v1.y*v2.x);
}
inline Vector4D vector_crossproduct(const Vector4D &v1, const Vector4D &v2)
{
	return -Vector4D(v1.y*v2.z - v1.z*v2.y, v1.z*v2.x - v1.x*v2.z, v1.x*v2.y - v1.y*v2.x);
}

// 长度
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

// 矢量归一化
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

//距离
inline float vector_distance(const Vector4D &v1, const Vector4D &v2)
{
	return(sqrtf(powf(v1.length(), 2) +powf(v2.length(), 2)));
}

//夹角（角度制)
inline float vector_angle(const Vector2D &v1, const Vector2D &v2)
{
	return rad_to_deg(acosf(vector_dotproduct(v1, v2) / (v1.length()*v2.length())));
}
//弧度制
inline float vector_angle(const Vector3D &v1, const Vector3D &v2)
{
	return acosf(vector_dotproduct(v1, v2) / (v1.length()*v2.length()));
}
//弧度制
inline float vector_angle(const Vector4D &v1, const Vector4D &v2)
{
	return acosf(vector_dotproduct(v1, v2) / (v1.length()*v2.length()));
}

//=====================================================================
// 矩阵
//=====================================================================

//四维齐次矩阵
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

	//初始化矩阵
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
	//M1*M2(矩阵相乘)
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

	//置零
	inline void set_zero()
	{
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				m[i][j] = 0;
	}
	//置单位矩阵
	inline void set_identity()
	{
		set_zero();
		M00 = M11 = M22 = M33 = 1.0f;
	}
	//置平移矩阵
	inline void set_translation(float dx, float dy, float dz)
	{
		set_identity();
		M30 = dx;
		M31 = dy;
		M32 = dz;
	}
	//置缩放矩阵
	inline void set_scale(float sx, float sy, float sz)
	{
		set_identity();
		M00 = sx;
		M11 = sy;
		M22 = sz;
	}
	//置旋转矩阵(绕向量A旋转Theta角度)
	inline void set_rotate(Vector4D A, float theta)
	{
		set_identity();
		A.normalize();

		float sin_theta = sinf(deg_to_rad(theta));
		float cos_theta = cosf(deg_to_rad(theta));

		//消除等于零时的数值误差
		if (abs(sin_theta) < 10E-7) 
			sin_theta = 0.0f;
		if (abs(cos_theta) < 10E-7)
			cos_theta = 0.0f;

		M00 = cos_theta + (1 - cos_theta)*A.x*A.x; M01 = (1 - cos_theta)*A.x*A.y + sin_theta * A.z; M02 = (1 - cos_theta)*A.x*A.z - sin_theta * A.y;
		M10 = (1 - cos_theta)*A.x*A.y - sin_theta * A.z; M11 = cos_theta + (1 - cos_theta)*A.y*A.y; M12 = (1 - cos_theta)*A.y*A.z + sin_theta * A.x;
		M20 = (1 - cos_theta)*A.x*A.z + sin_theta * A.y; M21 = (1 - cos_theta)*A.y*A.z - sin_theta * A.x; M22 = cos_theta + (1 - cos_theta)*A.z*A.z;
	}

	//控制台中显示Matrix
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

//矩阵*标量(返回新的矩阵)
Matrix4X4 matrix_scale(const Matrix4X4 &mat, float scale);
//应用矩阵变换到向量(返回新的4D向量)(行向量左乘矩阵)(p'=p*M)
Vector4D matrix_applyToVector(const Vector4D &v, const Matrix4X4 &mat);

//=====================================================================
// 颜色
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

	/*构造函数*/
	//默认构造函数;
	ColorRGB() = default;
	//初始化R, G ,B
	ColorRGB(int ir, int ig, int ib);
	ColorRGB(float ir_ratio, float ig_ratio, float ib_ratio);

	//拷贝构造函数
	ColorRGB(const ColorRGB &a);
	//析构函数
	~ColorRGB() = default;

	/*运算符重载*/
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
	//除以标量
	inline ColorRGB operator /(const float v)const
	{
		assert(v);
		return ColorRGB(this->R_ratio / v, this->G_ratio / v, this->B_ratio / v);
	}
	//颜色调制（右标量调制左颜色）
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
	//颜色调制(右颜色调制左颜色)
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
	//重载下标运算符
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