#include"Image.h"


Texture::Texture(const char * filename)
{
	if (rgba != nullptr)
		return;
	//用于存放png开头8字节
	char checkheader[8];

	fopen_s(&fp, filename, "rb");
	if (fp == nullptr)
	{
		throw std::exception("Failed to open file.");
		return;
	}
	//将png开头8字节存入checkheader
	//并检查是否不满8字节或读取失败
	if (fread_s(checkheader, 8, 1, 8, fp) != 8)
		return;
	if (png_sig_cmp((png_bytep)checkheader, 0, 8) != 0)
		throw std::exception("Not a PNG file.");

	// 1. 初始化png的结构体
	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	info_ptr = png_create_info_struct(png_ptr);

	// 2. 设置错误返回点
	setjmp(png_jmpbuf(png_ptr));
	rewind(fp); //等价fseek(fp, 0, SEEK_SET);

	// 3. 将文件流fp与png的结构体绑定
	png_init_io(png_ptr, fp);

	// 4. 读取png文件信息以及强转转换成RGBA:8888数据格式
	png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_EXPAND, 0); //读取文件信息
	int channels, color_type;
	channels = png_get_channels(png_ptr, info_ptr); //通道数量
	color_type = png_get_color_type(png_ptr, info_ptr);//颜色类型
	bit_depth = png_get_bit_depth(png_ptr, info_ptr);//位深度	
	width = png_get_image_width(png_ptr, info_ptr);//宽
	height = png_get_image_height(png_ptr, info_ptr);//高

	int i, j, k;
	int size, pos = 0;
	int temp;

	//5: 读取实际的rgb数据
	png_bytepp row_pointers; //实际存储rgb数据的buf
	row_pointers = png_get_rows(png_ptr, info_ptr); //也可以分别每一行获取png_get_rowbytes();
	size = width * height; //申请内存先计算空间
	if (channels == 4 || color_type == PNG_COLOR_TYPE_RGB_ALPHA)  //判断是24位还是32位
	{
		have_alpha = true; //记录是否有透明通道
		size *= (sizeof(unsigned char) * 4); //size = out->width * out->height * channel
		rgba = (png_bytep)malloc(size);
		if (NULL == rgba)
		{
			throw std::exception("Failed to alloc.");
			png_destroy_read_struct(&png_ptr, &info_ptr, 0);
			fclose(fp);
			return;
		}
		//从row_pointers里读出实际的rgb数据出来
		temp = channels - 1;
		for (i = 0; i < height; i++)
			for (j = 0; j < width * 4; j += 4)
				for (k = 0; k <= temp; k++)
					rgba[pos++] = row_pointers[i][j + k];
	}
	else if (channels == 3 || color_type == PNG_COLOR_TYPE_RGB)//判断颜色深度是24位还是32位
	{
		have_alpha = false;
		size *= (sizeof(unsigned char) * 3);
		rgba = (png_bytep)malloc(size);
		if (NULL == rgba) {
			printf("malloc rgba faile ...\n");
			png_destroy_read_struct(&png_ptr, &info_ptr, 0);
			fclose(fp);
			return;
		}
		//从row_pointers里读出实际的rgb数据
		temp = (3 * width);
		for (i = 0; i < height; i++) {
			for (j = 0; j < temp; j += 3) {
				rgba[pos++] = row_pointers[i][j + 2];
				rgba[pos++] = row_pointers[i][j + 1];
				rgba[pos++] = row_pointers[i][j + 0];
			}
		}
	}
	else return;
	//6:销毁内存
	png_destroy_read_struct(&png_ptr, &info_ptr, 0);
	fclose(fp);
	return;

}

void Texture::load_png(const char * filename)
{

	//用于存放png开头8字节
	char checkheader[8];

	fopen_s(&fp, filename, "rb");
	if (fp == nullptr)
	{
		throw std::exception("Failed to open file.");
		return;
	}
	//将png开头8字节存入checkheader
	//并检查是否不满8字节或读取失败
	if (fread_s(checkheader, 8, 1, 8, fp) != 8)
		return;
	if (png_sig_cmp((png_bytep)checkheader, 0, 8) != 0)
		throw std::exception("Not a PNG file.");

	// 1. 初始化png的结构体
	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	info_ptr = png_create_info_struct(png_ptr);

	// 2. 设置错误返回点
	setjmp(png_jmpbuf(png_ptr));
	rewind(fp); //等价fseek(fp, 0, SEEK_SET);

	// 3. 将文件流fp与png的结构体绑定
	png_init_io(png_ptr, fp);

	// 4. 读取png文件信息以及强转转换成RGBA:8888数据格式
	png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_EXPAND, 0); //读取文件信息
	int channels, color_type;
	channels = png_get_channels(png_ptr, info_ptr); //通道数量
	color_type = png_get_color_type(png_ptr, info_ptr);//颜色类型
	bit_depth = png_get_bit_depth(png_ptr, info_ptr);//位深度	
	width = png_get_image_width(png_ptr, info_ptr);//宽
	height = png_get_image_height(png_ptr, info_ptr);//高

	int i, j, k;
	int size, pos = 0;
	int temp;

	//5: 读取实际的rgb数据
	png_bytepp row_pointers; //实际存储rgb数据的buf
	row_pointers = png_get_rows(png_ptr, info_ptr); //也可以分别每一行获取png_get_rowbytes();
	size = width * height; //申请内存先计算空间
	if (channels == 4 || color_type == PNG_COLOR_TYPE_RGB_ALPHA)  //判断是24位还是32位
	{
		this->color_type = color_type;
		have_alpha = true; //记录是否有透明通道
		size *= (sizeof(unsigned char) * 4); //size = out->width * out->height * channel
		rgba = (png_bytep)malloc(size);
		if (NULL == rgba)
		{
			throw std::exception("Failed to alloc.");
			png_destroy_read_struct(&png_ptr, &info_ptr, 0);
			fclose(fp);
			return;
		}
		//从row_pointers里读出实际的rgb数据出来
		temp = channels - 1;
		for (i = 0; i < height; i++)
			for (j = 0; j < width * 4; j += 4)
				for (k = 0; k <= temp; k++)
					rgba[pos++] = row_pointers[i][j + k];
	}
	else if (channels == 3 || color_type == PNG_COLOR_TYPE_RGB)//判断颜色深度是24位还是32位
	{
		this->color_type = color_type;
		have_alpha = false;
		size *= (sizeof(unsigned char) * 3);
		rgba = (png_bytep)malloc(size);
		if (NULL == rgba) {
			printf("malloc rgba faile ...\n");
			png_destroy_read_struct(&png_ptr, &info_ptr, 0);
			fclose(fp);
			return;
		}
		//从row_pointers里读出实际的rgb数据
		temp = (3 * width);
		for (i = 0; i < height; i++) {
			for (j = 0; j < temp; j += 3) {
				rgba[pos++] = row_pointers[i][j + 0];
				rgba[pos++] = row_pointers[i][j + 1];
				rgba[pos++] = row_pointers[i][j + 2];
			}
		}
	}
	else return;
	//6:销毁内存
	png_destroy_read_struct(&png_ptr, &info_ptr, 0);
	fclose(fp);
	return;
}

