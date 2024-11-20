#include "vector"
#include "math.h"
#pragma once
using namespace std;
class Quadtreenode
{
	float x, y, width, height;
	
public:
	int parentID; int id;

	vector<int> objectID_list;
	vector<Quadtreenode*> ChildNodeList;
	Quadtreenode()
	{
		for (int i = 0; i < 4; i++)
		{
			Quadtreenode* node = NULL;
			ChildNodeList.push_back(node);
		}
	}
	Quadtreenode(int id,float x, float y,float w, float h,vector<int>list,int ParentID)
	{
		this->id = id;
		this->x = x;
		this->y = y;
		width = w;
		height = h;
		objectID_list = list;
		this->parentID = ParentID;
		for (int i = 0; i < 4; i++)
		{
			Quadtreenode* node = NULL;
			ChildNodeList.push_back(node);
		}
	}
	bool camerainnode(float x, float y, float c_x, float c_y);
	bool nodeincamera(float x, float y, float c_x, float c_y);
};


