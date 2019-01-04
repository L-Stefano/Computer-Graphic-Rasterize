#pragma once
#include"Math3D.h"
#include"Math3D.h"
#include<zlib.h>
#include<png.h>

class Texture
{
private:
	png_structp png_ptr;
	png_infop	info_ptr;
	FILE *fp;
	int color_type;//RGB/RGBA
public:
	int width, height;
	int bit_depth;
	bool have_alpha;
	//´æ·ÅrgbaÊý¾Ý
	png_bytep rgba;

	Texture() = default;
	Texture(const char* filename);

	void load_png(const char* filename);

	inline ColorRGB get_color_point_sampling(int x, int y)
	{
		if (color_type == PNG_COLOR_TYPE_RGB_ALPHA)
			return ColorRGB(rgba[(y * width + x) * 4], rgba[(y * width + x) * 4 + 1], rgba[(y * width + x) * 4 + 2]);
		else if (color_type == PNG_COLOR_TYPE_RGB)
			return ColorRGB(rgba[(y * width + x) * 3], rgba[(y * width + x) * 3 + 1], rgba[(y * width + x) * 3 + 2]);
	}
	inline ColorRGB get_color_bilinear(float x, float y)
	{
		ColorRGB result;
		int x_integer = floorf(x), y_integer = floorf(y);
		float x_decimal = x - x_integer, y_decimal = y - y_integer;



		if (color_type == PNG_COLOR_TYPE_RGB_ALPHA)
		{
			if (x_integer == width - 1)
			{
				x_decimal = 0;
				result.R = rgba[(y_integer * width + x_integer) * 4] * (1.0f - x_decimal)*(1.0f - y_decimal) +
					rgba[((y_integer + 1) * width + x_integer) * 4] * (1.0f - x_decimal)*y_decimal;
				result.G = rgba[(y_integer * width + x_integer) * 4 + 1] * (1.0f - x_decimal)*(1.0f - y_decimal) +
					rgba[((y_integer + 1) * width + x_integer) * 4 + 1] * (1.0f - x_decimal)*y_decimal;
				result.B = rgba[(y_integer * width + x_integer) * 4 + 2] * (1.0f - x_decimal)*(1.0f - y_decimal) +
					rgba[((y_integer + 1) * width + x_integer) * 4 + 2] * (1.0f - x_decimal)*y_decimal;
			}
			if (y_integer == height - 1)
			{
				y_decimal = 0;
				result.R = rgba[(y_integer * width + x_integer) * 4] * (1.0f - x_decimal)*(1.0f - y_decimal) +
					rgba[(y_integer * width + (x_integer + 1)) * 4] * x_decimal*(1.0f - y_decimal);
				result.G = rgba[(y_integer * width + x_integer) * 4 + 1] * (1.0f - x_decimal)*(1.0f - y_decimal) +
					rgba[(y_integer * width + (x_integer + 1)) * 4+ 1] * x_decimal*(1.0f - y_decimal);
				result.B = rgba[(y_integer * width + x_integer) * 4 + 2] * (1.0f - x_decimal)*(1.0f - y_decimal) +
					rgba[(y_integer * width + (x_integer + 1)) * 4 + 2] * x_decimal*(1.0f - y_decimal);
			}
			else
			{
				result.R = rgba[(y_integer * width + x_integer) * 4] * (1.0f - x_decimal)*(1.0f - y_decimal) +
					rgba[(y_integer * width + (x_integer + 1)) * 4] * x_decimal*(1.0f - y_decimal) +
					rgba[((y_integer + 1) * width + x_integer) * 4] * (1.0f - x_decimal)*y_decimal +
					rgba[((y_integer + 1) * width + (x_integer + 1)) * 4] * x_decimal*y_decimal;
				result.G = rgba[(y_integer * width + x_integer) * 4 + 1] * (1.0f - x_decimal)*(1.0f - y_decimal) +
					rgba[(y_integer * width + (x_integer + 1)) * 4 + 1] * x_decimal*(1.0f - y_decimal) +
					rgba[((y_integer + 1) * width + x_integer) * 4 + 1] * (1.0f - x_decimal)*y_decimal +
					rgba[((y_integer + 1) * width + (x_integer + 1)) * 4 + 1] * x_decimal*y_decimal;
				result.B = rgba[(y_integer * width + x_integer) * 4 + 2] * (1.0f - x_decimal)*(1.0f - y_decimal) +
					rgba[(y_integer * width + (x_integer + 1)) * 4 + 2] * x_decimal*(1.0f - y_decimal) +
					rgba[((y_integer + 1) * width + x_integer) * 4 + 2] * (1.0f - x_decimal)*y_decimal +
					rgba[((y_integer + 1) * width + (x_integer + 1)) * 4 + 2] * x_decimal*y_decimal;
			}
			return result;
		}
		else if (color_type == PNG_COLOR_TYPE_RGB)
		{
			if (x_integer == width - 1)
			{
				x_decimal = 0;
				result.R = rgba[(y_integer * width + x_integer) * 3] * (1.0f - x_decimal)*(1.0f - y_decimal) +
					rgba[((y_integer + 1) * width + x_integer) * 3] * (1.0f - x_decimal)*y_decimal;
				result.G = rgba[(y_integer * width + x_integer) * 3 + 1] * (1.0f - x_decimal)*(1.0f - y_decimal) +
					rgba[((y_integer + 1) * width + x_integer) * 3 + 1] * (1.0f - x_decimal)*y_decimal;
				result.B = rgba[(y_integer * width + x_integer) * 3 + 2] * (1.0f - x_decimal)*(1.0f - y_decimal) +
					rgba[((y_integer + 1) * width + x_integer) * 3 + 2] * (1.0f - x_decimal)*y_decimal;
			}
			if (y_integer == height - 1)
			{
				y_decimal = 0;
				result.R = rgba[(y_integer * width + x_integer) * 3] * (1.0f - x_decimal)*(1.0f - y_decimal) +
					rgba[(y_integer * width + (x_integer + 1)) * 3] * x_decimal*(1.0f - y_decimal);
				result.G = rgba[(y_integer * width + x_integer) * 3 + 1] * (1.0f - x_decimal)*(1.0f - y_decimal) +
					rgba[(y_integer * width + (x_integer + 1)) * 3 + 1] * x_decimal*(1.0f - y_decimal);
				result.B = rgba[(y_integer * width + x_integer) * 3 + 2] * (1.0f - x_decimal)*(1.0f - y_decimal) +
					rgba[(y_integer * width + (x_integer + 1)) * 3 + 2] * x_decimal*(1.0f - y_decimal);
			}
			else
			{
				result.R = rgba[(y_integer * width + x_integer) * 3] * (1.0f - x_decimal)*(1.0f - y_decimal) +
					rgba[(y_integer * width + (x_integer + 1)) * 3] * x_decimal*(1.0f - y_decimal) +
					rgba[((y_integer + 1) * width + x_integer) * 3] * (1.0f - x_decimal)*y_decimal +
					rgba[((y_integer + 1) * width + (x_integer + 1)) * 3] * x_decimal*y_decimal;
				result.G = rgba[(y_integer * width + x_integer) * 3 + 1] * (1.0f - x_decimal)*(1.0f - y_decimal) +
					rgba[(y_integer * width + (x_integer + 1)) * 3 + 1] * x_decimal*(1.0f - y_decimal) +
					rgba[((y_integer + 1) * width + x_integer) * 3 + 1] * (1.0f - x_decimal)*y_decimal +
					rgba[((y_integer + 1) * width + (x_integer + 1)) * 3 + 1] * x_decimal*y_decimal;
				result.B = rgba[(y_integer * width + x_integer) * 3 + 2] * (1.0f - x_decimal)*(1.0f - y_decimal) +
					rgba[(y_integer * width + (x_integer + 1)) * 3 + 2] * x_decimal*(1.0f - y_decimal) +
					rgba[((y_integer + 1) * width + x_integer) * 3 + 2] * (1.0f - x_decimal)*y_decimal +
					rgba[((y_integer + 1) * width + (x_integer + 1)) * 3 + 2] * x_decimal*y_decimal;
			}
			return result;
		}
	}
};