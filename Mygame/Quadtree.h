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
		root = NULL;
	}
	Quadtree(Quadtreenode* root)
	{
		this->root=root;
		if (root == NULL)
		{
			DebugOut(L"something go wrong\n");
		}
		split(root);
	}
	/*void CreatQuadTree(Quadtreenode* nodetoadd)
	{
			if(nodetoadd)
	}*/
	/*void ADD(Quadtreenode* nodeneedtoadd)
	{
		if (root != NULL)
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
		else
		{
			root = nodeneedtoadd;

		}
	}*/
	
	vector<LPGAMEOBJECT> traversal()
	{
		vector<LPGAMEOBJECT>list;
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
			if (currentnode->AABB(cx, cy, w, h) == TRUE)
			{
				for (int i = 0; i < currentnode->object_list.size(); i++)
				{
					LPGAMEOBJECT currentid = currentnode->object_list[i];
					int canadd = true;
					for (int j = 0; j < list.size(); j++)
					{
						if (currentid == list[j])
						{
							canadd = false;
						}
					}
					if (canadd == true)
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
	void deletequadtree()
	{
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
			for (int i = 0; i < 4; i++)
			{
					if (currentnode->ChildNodeList[i] != NULL)
					{
						node.push(currentnode->ChildNodeList[i]);
					}
			}
			delete currentnode;
		}
	}
	void split(Quadtreenode* node)//chia 1 node thanh 4 node
	{
		float x, y, width, height;
		node->GetStat(x, y, width, height);
		if (node->object_list.size() <= 1 || node->checkcondition((float)Game::GetInstance()->GetBackBufferWidth() / 4))
		{
			return;
		}
		Quadtreenode* node1 = new Quadtreenode(node->id + 1, x, y, width / 2, height / 2);
		Quadtreenode* node2 = new Quadtreenode(node->id + 2, x+ width / 2, y - height / 2, width / 2, height / 2);
		Quadtreenode* node3 = new Quadtreenode(node->id + 3, x, y - height / 2, width / 2, height / 2);
		Quadtreenode* node4 = new Quadtreenode(node->id + 4, x + width / 2, y, width / 2, height / 2);
		node->ChildNodeList[0] = node1;
		node->ChildNodeList[1] = node2;
		node->ChildNodeList[2] = node3;
		node->ChildNodeList[3] = node4;
		for (int i = 0; i < node->object_list.size();i++)
		{
			for (int j = 0; j < 4; j++)
			{
				node->ChildNodeList[j];
				float t, l, r, b;
				node->object_list[i]->GetBoundingBox(l, t, r, b);
				if (node->ChildNodeList[j] != NULL) {
					
					if (node->ChildNodeList[j]->AABB(l, t, (r - l), (t - b))==true)
					{
						
						node->ChildNodeList[j]->object_list.push_back(node->object_list[i]);
					}
				}
				else
				{
					DebugOut(L"child node null\n");
				}
			}
		}
		node->object_list.clear();
		for (int i = 0; i < 4; i++)
		{
			
			if (node->ChildNodeList[i] != NULL)
			split(node->ChildNodeList[i]);
		}
	}
};

