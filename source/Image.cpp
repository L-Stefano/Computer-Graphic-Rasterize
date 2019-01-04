#include"Image.h"


Texture::Texture(const char * filename)
{
	if (rgba != nullptr)
		return;
	//���ڴ��png��ͷ8�ֽ�
	char checkheader[8];

	fopen_s(&fp, filename, "rb");
	if (fp == nullptr)
	{
		throw std::exception("Failed to open file.");
		return;
	}
	//��png��ͷ8�ֽڴ���checkheader
	//������Ƿ���8�ֽڻ��ȡʧ��
	if (fread_s(checkheader, 8, 1, 8, fp) != 8)
		return;
	if (png_sig_cmp((png_bytep)checkheader, 0, 8) != 0)
		throw std::exception("Not a PNG file.");

	// 1. ��ʼ��png�Ľṹ��
	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	info_ptr = png_create_info_struct(png_ptr);

	// 2. ���ô��󷵻ص�
	setjmp(png_jmpbuf(png_ptr));
	rewind(fp); //�ȼ�fseek(fp, 0, SEEK_SET);

	// 3. ���ļ���fp��png�Ľṹ���
	png_init_io(png_ptr, fp);

	// 4. ��ȡpng�ļ���Ϣ�Լ�ǿתת����RGBA:8888���ݸ�ʽ
	png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_EXPAND, 0); //��ȡ�ļ���Ϣ
	int channels, color_type;
	channels = png_get_channels(png_ptr, info_ptr); //ͨ������
	color_type = png_get_color_type(png_ptr, info_ptr);//��ɫ����
	bit_depth = png_get_bit_depth(png_ptr, info_ptr);//λ���	
	width = png_get_image_width(png_ptr, info_ptr);//��
	height = png_get_image_height(png_ptr, info_ptr);//��

	int i, j, k;
	int size, pos = 0;
	int temp;

	//5: ��ȡʵ�ʵ�rgb����
	png_bytepp row_pointers; //ʵ�ʴ洢rgb���ݵ�buf
	row_pointers = png_get_rows(png_ptr, info_ptr); //Ҳ���Էֱ�ÿһ�л�ȡpng_get_rowbytes();
	size = width * height; //�����ڴ��ȼ���ռ�
	if (channels == 4 || color_type == PNG_COLOR_TYPE_RGB_ALPHA)  //�ж���24λ����32λ
	{
		have_alpha = true; //��¼�Ƿ���͸��ͨ��
		size *= (sizeof(unsigned char) * 4); //size = out->width * out->height * channel
		rgba = (png_bytep)malloc(size);
		if (NULL == rgba)
		{
			throw std::exception("Failed to alloc.");
			png_destroy_read_struct(&png_ptr, &info_ptr, 0);
			fclose(fp);
			return;
		}
		//��row_pointers�����ʵ�ʵ�rgb���ݳ���
		temp = channels - 1;
		for (i = 0; i < height; i++)
			for (j = 0; j < width * 4; j += 4)
				for (k = 0; k <= temp; k++)
					rgba[pos++] = row_pointers[i][j + k];
	}
	else if (channels == 3 || color_type == PNG_COLOR_TYPE_RGB)//�ж���ɫ�����24λ����32λ
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
		//��row_pointers�����ʵ�ʵ�rgb����
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
	//6:�����ڴ�
	png_destroy_read_struct(&png_ptr, &info_ptr, 0);
	fclose(fp);
	return;

}

void Texture::load_png(const char * filename)
{

	//���ڴ��png��ͷ8�ֽ�
	char checkheader[8];

	fopen_s(&fp, filename, "rb");
	if (fp == nullptr)
	{
		throw std::exception("Failed to open file.");
		return;
	}
	//��png��ͷ8�ֽڴ���checkheader
	//������Ƿ���8�ֽڻ��ȡʧ��
	if (fread_s(checkheader, 8, 1, 8, fp) != 8)
		return;
	if (png_sig_cmp((png_bytep)checkheader, 0, 8) != 0)
		throw std::exception("Not a PNG file.");

	// 1. ��ʼ��png�Ľṹ��
	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	info_ptr = png_create_info_struct(png_ptr);

	// 2. ���ô��󷵻ص�
	setjmp(png_jmpbuf(png_ptr));
	rewind(fp); //�ȼ�fseek(fp, 0, SEEK_SET);

	// 3. ���ļ���fp��png�Ľṹ���
	png_init_io(png_ptr, fp);

	// 4. ��ȡpng�ļ���Ϣ�Լ�ǿתת����RGBA:8888���ݸ�ʽ
	png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_EXPAND, 0); //��ȡ�ļ���Ϣ
	int channels, color_type;
	channels = png_get_channels(png_ptr, info_ptr); //ͨ������
	color_type = png_get_color_type(png_ptr, info_ptr);//��ɫ����
	bit_depth = png_get_bit_depth(png_ptr, info_ptr);//λ���	
	width = png_get_image_width(png_ptr, info_ptr);//��
	height = png_get_image_height(png_ptr, info_ptr);//��

	int i, j, k;
	int size, pos = 0;
	int temp;

	//5: ��ȡʵ�ʵ�rgb����
	png_bytepp row_pointers; //ʵ�ʴ洢rgb���ݵ�buf
	row_pointers = png_get_rows(png_ptr, info_ptr); //Ҳ���Էֱ�ÿһ�л�ȡpng_get_rowbytes();
	size = width * height; //�����ڴ��ȼ���ռ�
	if (channels == 4 || color_type == PNG_COLOR_TYPE_RGB_ALPHA)  //�ж���24λ����32λ
	{
		this->color_type = color_type;
		have_alpha = true; //��¼�Ƿ���͸��ͨ��
		size *= (sizeof(unsigned char) * 4); //size = out->width * out->height * channel
		rgba = (png_bytep)malloc(size);
		if (NULL == rgba)
		{
			throw std::exception("Failed to alloc.");
			png_destroy_read_struct(&png_ptr, &info_ptr, 0);
			fclose(fp);
			return;
		}
		//��row_pointers�����ʵ�ʵ�rgb���ݳ���
		temp = channels - 1;
		for (i = 0; i < height; i++)
			for (j = 0; j < width * 4; j += 4)
				for (k = 0; k <= temp; k++)
					rgba[pos++] = row_pointers[i][j + k];
	}
	else if (channels == 3 || color_type == PNG_COLOR_TYPE_RGB)//�ж���ɫ�����24λ����32λ
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
		//��row_pointers�����ʵ�ʵ�rgb����
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
	//6:�����ڴ�
	png_destroy_read_struct(&png_ptr, &info_ptr, 0);
	fclose(fp);
	return;
}

