#pragma once
#include "queue"
#include "Quadtreenode.h"
#include "Camera.h"
#include"Game.h"
class Quadtree
{
	Quadtreenode* root;
public:
	Quadtree()
	{
		vector<int>list;
		root = new Quadtreenode(0, 0, 0, 320, 240, list, -1);
	}
	void ADD(Quadtreenode* nodeneedtoadd);
	vector<int> traversal();
};

