#include "vector"
#include "math.h"
#pragma once
#include"GameObject.h"
using namespace std;
class Quadtreenode
{
	float x, y, width, height;
	
public:
	int id;

	vector<LPGAMEOBJECT> object_list;
	vector<Quadtreenode*> ChildNodeList;
	Quadtreenode()
	{
		for (int i = 0; i < 4; i++)
		{
			Quadtreenode* node = NULL;
			ChildNodeList.push_back(node);
		}
	}
	Quadtreenode(int id,float x, float y,float w, float h,vector<LPGAMEOBJECT>list)
	{
		this->id = id;
		this->x = x;
		this->y = y;
		width = w;
		height = h;
		object_list = list;
		for (int i = 0; i < 4; i++)
		{
			Quadtreenode* node = NULL;
			ChildNodeList.push_back(node);
		}
	}
	Quadtreenode(int id, float x, float y, float w, float h)
	{
		this->id = id;
		this->x = x;
		this->y = y;
		width = w;
		height = h;
		for (int i = 0; i < 4; i++)
		{
			Quadtreenode* node = NULL;
			ChildNodeList.push_back(node);
		}
	}
	void GetNodeSize(float& w, float& height);
	bool AABB(float c_x, float c_y, float c_w, float c_h);
	bool checkcondition(float width)
	{
		if (this->width < width)
		{
			return true;
		}
		return false;
	}
	void GetStat(float& x, float& y, float& width, float& height)
	{
		x = this->x;
		y = this->y;
		width = this->width;
		height = this->height;
	}
};


