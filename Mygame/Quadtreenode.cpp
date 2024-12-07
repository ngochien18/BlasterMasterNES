#include "Quadtreenode.h"
bool Quadtreenode::AABB(float c_x, float c_y, float c_w, float c_h)
{
	float node_l = this->x;
	float node_b = this->y;
	float node_r = this->width+this->x;
	float node_t = this->height+this->y;
	float c_b = c_y-c_h;
	float c_l = c_x;
	float c_r = c_x + c_w;
	float c_t = c_y;
	bool AABBonX = false;
	bool AABBonY = false;
	if ((node_l > c_r || node_r < c_l)==false)
	{
		AABBonX = true;
	}
	if ((node_b >= c_t || node_t <= c_b)==false)
	{
		AABBonY = true;
	}
	if (AABBonX==true && AABBonY==true)
	{
		return true;
	}
	return false;
}