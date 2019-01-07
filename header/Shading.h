#pragma once
#include"Math3D.h"
#include<vector>
//=====================================================================
// ����
//=====================================================================
//��ɫģʽ;
constexpr int SHADE_MODE_GOURAUD = 0x0001;
constexpr int SHADE_MODE_PHONG = 0x0002;
constexpr int SHADE_MODE_BLINN_PHONG = 0x0003;
class Material
{
public:
	const char* name; // ��������
	int shading_mode; // ��ɫģʽ

	ColorRGB ka, // �����ⷴ��ϵ��
		kd, // ������ϵ��
		ks; // ���淴��ϵ��
	float power; // ���淴��ָ��

	Material() = default;
	//��ʼ������
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
// ��Դ
//=====================================================================
//������
class Ambient_Light
{
private:
	ColorRGB color; // ��Դ��ɫ
	ColorRGB intensity; // ����ǿ��
public:
	ColorRGB intensity_light;
	bool active;

	Ambient_Light(const ColorRGB &_color, const ColorRGB &_intensity = ColorRGB(1.0f, 1.0f, 1.0f), bool _active = true) :color(_color), intensity(_intensity)
	{
		intensity_light = color * intensity;
		active = _active;
	}
};

//ƽ�й�
class Infinite_Light
{
private:
	ColorRGB color; // ��Դ��ɫ
	ColorRGB intensity; // ����ǿ��
public:
	ColorRGB intensity_light;
	bool active;

	Vector4D direction; // ����

	Infinite_Light(const Vector4D &_direction, const ColorRGB &_color,
		const ColorRGB &_intensity = ColorRGB(1.0f, 1.0f, 1.0f),
		bool _active = true) :color(_color), intensity(_intensity), direction(_direction)
	{
		direction.normalize();
		intensity_light = color * intensity;
		active = _active;
	}
};

//���Դ
class Point_Light
{
private:
	ColorRGB color; // ��Դ��ɫ
	ColorRGB intensity; // ����ǿ��
public:
	ColorRGB intensity_light;
	bool active;

	Point4D position; // λ��
	float kc, kl, kq; // ����˥������

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

//�۹��
class Spotlight
{
private:
	ColorRGB color; // ��Դ��ɫ
	ColorRGB intensity; // ����ǿ��
public:
	ColorRGB intensity_light;
	bool active;

	Point4D position; // λ��
	Vector4D direction; // ����
	float kc, kl, kq; // ����˥������
	float umbra, // ��Ӱ�Ƕ�
		penumbra; // ��Ӱ�Ƕ�
	float pf; // ��������

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
//��Դ�б�
class Light_List
{
public:
	std::vector<Ambient_Light> ambient_light_list;
	std::vector<Infinite_Light> infinite_light_list;
	std::vector<Point_Light> point_light_list;
	std::vector<Spotlight> spotlight_list;

	//��ӻ�����
	inline void add_ambient_light(const Ambient_Light & _ambient_light)
	{
		ambient_light_list.push_back(_ambient_light);
	}
	//���ƽ�й�
	inline void add_infinite_light(const Infinite_Light & _infinitet_light)
	{
		infinite_light_list.push_back(_infinitet_light);
	}
	//��ӵ��Դ
	inline void add_point_light(const Point_Light & _point_light)
	{
		point_light_list.push_back(_point_light);
	}
	//��Ӿ۹��
	inline void add_spotlight(const Spotlight &spotlight)
	{
		spotlight_list.push_back(spotlight);
	}
};
