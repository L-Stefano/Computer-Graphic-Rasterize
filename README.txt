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
 │    ├Vector2D：Vector2D类的实现文件。
 ╰    └Vector3D：Vector3D类的实现文件。
 
 ╭ALPHA：实现了一个用阿尔法通道的融合方程暴力计算颜色值的效果。（待加入graphic.h）
 │ ├ALPHA.cpp
 │ ├front.png：前景图片
 │ ├back.png：背景图片
 ╰ └mixed.png：50%α混合

 ─generalLine.cpp：包含了svpng.h，用直线的一般式绘制。（待加入graphic.h）
 ─setPixel.cpp：设置单点像素。（待加入graphic.h）
