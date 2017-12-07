# Computer-Graphic-Rasterize

记录了学习图形学的光栅化部分
会逐步实现各项功能，最后目标是做出一个较为完整的软渲。

暂时直接通过编码保存到了PNG里（此处使用了https://github.com/miloyip/svpng 中的svpng()函数），日后会实现一个渲染器的。

周期或许会很长，权当自己的学习笔记。

文件概览：

 ╭header：内涵所有所需的头文件以及实现文件，目前正在完善graphic。
 │ ├svpng.h：感谢MiloYip提供的png编码函数：https://github.com/miloyip/svpng
 │ └graphic：
 │    ├graphic.h：步步完善，最终会成为一个较为完整的图形学综合库。
 │    ├Vector2D：向量Vector2D类。
 │    ├Vector3D：向量Vector3D类。
 │    ├Image：Image类，内涵一个exprortPNG函数用于输出图片。
 │    ├Triangle：Triangle类，包含了基本的三角形操作，如法向量，面积，重心坐标获取函数等。
 │    ├Rasterize：Rasterize类，主要包含各种光栅化算法，如单像素绘制、中点直线绘制、参数直线绘制等。
 │    ├RGB：RGB类，以RGB模型存储颜色值，可以通过整数(0-255)或浮点数(0.0f-1.0f)进行存储。
 ╰    └graphic.lib：编译好的静态库，需配合graphic.h食用（#include "graphic.h" #pragma comment(lib,"graphic.lib")）。(暂时已删除)
 
 ╭ALPHA：实现了一个用阿尔法通道的融合方程暴力计算颜色值的效果。（已加入graphic.h:RGB）
 │ ├ALPHA.cpp
 │ ├front.png：前景图片
 │ ├back.png：背景图片
 ╰ └mixed.png：50%α混合

 ─generalLine.cpp：包含了svpng.h，用直线的一般式绘制。（已加入graphic.h:Rasterize）
 ─setPixel.cpp：设置单点像素。（已加入graphic.h:Rasterize）

更新：2017/12/01
更新：2017/12/02
更新：2017/12/07 12:12

个人主页：http://stefano.com.cn
