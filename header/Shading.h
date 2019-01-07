#pragma once
#include"Math3D.h"
#include<vector>
//=====================================================================
// 材质
//=====================================================================
//着色模式;
constexpr int SHADE_MODE_GOURAUD = 0x0001;
constexpr int SHADE_MODE_PHONG = 0x0002;
constexpr int SHADE_MODE_BLINN_PHONG = 0x0003;
class Material
{
public:
	const char* name; // 材质名称
	int shading_mode; // 着色模式

	ColorRGB ka, // 环境光反射系数
		kd, // 漫反射系数
		ks; // 镜面反射系数
	float power; // 镜面反射指数

	Material() = default;
	//初始化材质
	Material(const char* _name, int _shading_mode, ColorRGB _kambient, ColorRGB _kdiffuse, ColorRGB _kspecular, float _powerspecular) :name(_name)
	{
		shading_mode = _shading_mode;
		ka = _kambient;
		kd = _kdiffuse;
		ks = _kspecular;
		power = _powerspecular;
	}

};

//=====================================================================
// 光源
//=====================================================================
//环境光
class Ambient_Light
{
private:
	ColorRGB color; // 光源颜色
	ColorRGB intensity; // 光照强度
public:
	ColorRGB intensity_light;
	bool active;

	Ambient_Light(const ColorRGB &_color, const ColorRGB &_intensity = ColorRGB(1.0f, 1.0f, 1.0f), bool _active = true) :color(_color), intensity(_intensity)
	{
		intensity_light = color * intensity;
		active = _active;
	}
};

//平行光
class Infinite_Light
{
private:
	ColorRGB color; // 光源颜色
	ColorRGB intensity; // 光照强度
public:
	ColorRGB intensity_light;
	bool active;

	Vector4D direction; // 朝向

	Infinite_Light(const Vector4D &_direction, const ColorRGB &_color,
		const ColorRGB &_intensity = ColorRGB(1.0f, 1.0f, 1.0f),
		bool _active = true) :color(_color), intensity(_intensity), direction(_direction)
	{
		direction.normalize();
		intensity_light = color * intensity;
		active = _active;
	}
};

//点光源
class Point_Light
{
private:
	ColorRGB color; // 光源颜色
	ColorRGB intensity; // 光照强度
public:
	ColorRGB intensity_light;
	bool active;

	Point4D position; // 位置
	float kc, kl, kq; // 距离衰减因子

	Point_Light(const Vector4D & _position,
		const ColorRGB &_color, const ColorRGB &_intensity = ColorRGB(1.0f, 1.0f, 1.0f),
		float _kc = 0, float _kl = 1, float _kq = 0,
		bool _active = true) :color(_color), position(_position), intensity(_intensity)
	{
		intensity_light = color * intensity;
		kc = _kc; kl = _kl; kq = _kq;
		active = _active;
	}
};

//聚光灯
class Spotlight
{
private:
	ColorRGB color; // 光源颜色
	ColorRGB intensity; // 光照强度
public:
	ColorRGB intensity_light;
	bool active;

	Point4D position; // 位置
	Vector4D direction; // 朝向
	float kc, kl, kq; // 距离衰减因子
	float umbra, // 本影角度
		penumbra; // 半影角度
	float pf; // 减弱因子

	Spotlight(const Point4D &_position, const Vector4D &_direction, 
		float _umbra, float _penumbra,
		const ColorRGB &_color, const ColorRGB &_intensity = ColorRGB(1.0f, 1.0f, 1.0f),
		float _kc = 0, float _kl = 1, float _kq = 0,
		float _falloff = 1,
		bool _active = true) :color(_color), intensity(_intensity), position(_position), direction(_direction)
	{
		direction.normalize();
		intensity_light = color * intensity;
		kc = _kc; kl = _kl; kq = _kq;
		umbra = deg_to_rad(_umbra); penumbra = deg_to_rad(_penumbra);
		pf = _falloff;
		active = _active;
	}
};
//光源列表
class Light_List
{
public:
	std::vector<Ambient_Light> ambient_light_list;
	std::vector<Infinite_Light> infinite_light_list;
	std::vector<Point_Light> point_light_list;
	std::vector<Spotlight> spotlight_list;

	//添加环境光
	inline void add_ambient_light(const Ambient_Light & _ambient_light)
	{
		ambient_light_list.push_back(_ambient_light);
	}
	//添加平行光
	inline void add_infinite_light(const Infinite_Light & _infinitet_light)
	{
		infinite_light_list.push_back(_infinitet_light);
	}
	//添加点光源
	inline void add_point_light(const Point_Light & _point_light)
	{
		point_light_list.push_back(_point_light);
	}
	//添加聚光灯
	inline void add_spotlight(const Spotlight &spotlight)
	{
		spotlight_list.push_back(spotlight);
	}
};
