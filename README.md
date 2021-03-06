# Computer-Graphic-Rasterize
基于SDL的软件光栅化渲染器
会逐步完善

## 外部库有：
1. libpng
2. SDL

## 目前已实现：
1. 线框渲染
2. 固体色着色
3. 背面消隐/物体剔除
4. z-buffer
5. 重心插值
6. 透视校正插值
7. 纹理映射：支持双线性过滤，仅png
8. 双线程并行光栅化三角形片元（效果不好）
9. Gouraud着色
10. Phong着色

mipmap：

![Image text](https://github.com/L-Stefano/Computer-Graphic-Rasterize/blob/master/img/mipmap.png)

z-buffer：

![Image text](https://github.com/L-Stefano/Computer-Graphic-Rasterize/blob/master/img/z-buffer.png)

Phong着色：

![Image text](https://github.com/L-Stefano/Computer-Graphic-Rasterize/blob/master/img/pic_shading.png)

Phong光照模型：

![Image text](https://github.com/L-Stefano/Computer-Graphic-Rasterize/blob/master/img/pic_phong_specular.png)

最近点采样：

![Image text](https://github.com/L-Stefano/Computer-Graphic-Rasterize/blob/master/img/pic_point_sampling.png)

双线性过滤：

![Image text](https://github.com/L-Stefano/Computer-Graphic-Rasterize/blob/master/img/pic_bilinear.png)

![Image text](https://github.com/L-Stefano/Computer-Graphic-Rasterize/blob/master/img/pic_1.png)

