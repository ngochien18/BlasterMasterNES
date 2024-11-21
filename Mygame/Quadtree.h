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
	void ADD(Quadtreenode* nodeneedtoadd)
	{
		if (root != nullptr)
		{
			queue<Quadtreenode*> node;
			node.push(this->root);
			Quadtreenode* currentnode;
			while (node.empty() == false)
			{
				currentnode = node.front();
				node.pop();
				if (nodeneedtoadd->parentID == currentnode->id)
				{
					for (int i = 0; i < 4; i++)
					{
						if (currentnode->ChildNodeList[i] == NULL)
						{
							currentnode->ChildNodeList[i] = nodeneedtoadd;
							return;
						}
					}
				}
				for (int i = 0; i < 4; i++)
				{
					if (currentnode->ChildNodeList[i] != NULL)
					{
						node.push(currentnode->ChildNodeList[i]);
					}
				}
			}
		}
	}
	
	vector<int> traversal()
	{
		vector<int>list;
		float cx, cy;
		Game::GetInstance()->GetCamera()->GetCamPos(cx, cy);
		int w = Game::GetInstance()->GetBackBufferWidth();
		int h = Game::GetInstance()->GetBackBufferHeight();
		queue<Quadtreenode*> node;
		node.push(this->root);
		Quadtreenode* currentnode;
		while (node.empty() == false)
		{
			currentnode = node.front();
			node.pop();
			if (currentnode->camerainnode(cx, cy, w, h) == true || currentnode->nodeincamera(cx, cy, w, h) == true)
			{
				for (int i = 0; i < currentnode->objectID_list.size(); i++)
				{
					int currentid = currentnode->objectID_list[i];
					int canadd = true;
					for (int j = 0; j < list.size(); j++)
					{
						if (currentid == list[j])
						{
							canadd = false;
						}
					}
					if (canadd = true)
					{
						list.push_back(currentid);
					}

				}
				for (int i = 0; i < 4; i++)
				{

					if (currentnode->ChildNodeList[i] != NULL)
					{
						node.push(currentnode->ChildNodeList[i]);
					}
				}
			}
			
		}
		return list;
	}
};

