#include "Geometry.h"
Geom_Vertex::Geom_Vertex(float _x, float _y, float _z, ColorRGB _c)
{
	world_pos.x = _x;
	world_pos.y = _y;
	world_pos.z = _z;
	world_pos.w = 1;
	color = _c;
}
