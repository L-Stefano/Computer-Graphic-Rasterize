#include "Geometry.h"
Geom_Vertex::Geom_Vertex(float _x, float _y, float _z, ColorRGB _c)
{
	local_pos.x = _x;
	local_pos.y = _y;
	local_pos.z = _z;
	local_pos.w = 1;
	color = _c;
}
