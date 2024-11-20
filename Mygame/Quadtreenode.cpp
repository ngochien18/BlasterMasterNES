#include "Quadtreenode.h"
bool Quadtreenode::camerainnode(float c_x, float c_y, float c_w, float c_h)
{
	if (c_x >= x && c_x <= x + width)// xay dung zone toa do cua cac zone la khac biet khong co 1 diem cung ton tai trong gioi han 2 zone
	{
		if ((c_y >= y && c_y <= y + height) || (c_y + c_h >= y && c_y + c_h <= y + height))
		{
			return true;
		}
	}
	if (c_x+c_w >= x && c_x+c_w <= x + width)// xay dung zone toa do cua cac zone la khac biet khong co 1 diem cung ton tai trong gioi han 2 zone
	{
		if ((c_y >= y && c_y <= y + height) || (c_y + c_h >= y && c_y + c_h <= y + height))
		{
			return true;
		}
	}
	return false;
}
bool Quadtreenode::nodeincamera(float c_x, float c_y, float c_w, float c_h)
{
	if (x >= c_x && x <= c_x + c_w)// xay dung zone toa do cua cac zone la khac biet khong co 1 diem cung ton tai trong gioi han 2 zone
	{
		if ((y >= c_y && y <= c_y + c_h) || (y + height >= y && y+height<= c_y + c_h))
		{
			return true;
		}
	}
	if (x+width >= c_x && x+width <= c_x + c_w)// xay dung zone toa do cua cac zone la khac biet khong co 1 diem cung ton tai trong gioi han 2 zone
	{
		if ((y >= c_y && y <= c_y + c_h) || (y + height >= y && y + height <= c_y + c_h))
		{
			return true;
		}
	}
	return false;
}