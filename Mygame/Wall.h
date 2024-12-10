#pragma once

#include "GameObject.h"
#include "Game.h"

#define ID_ANI_WALL 100000
#define WALL_WIDTH 16
#define WALL_BBOX_WIDTH 16
#define WALL_BBOX_HEIGHT 16

class Wall : public Gameobject {
private:
	int width;
	int height;
public:
	Wall();
	Wall(float x, float y, int width, int height);
	virtual int IsBlocking() { return 1; }
	~Wall();
	int GetWidth() { return width; }
	int GetHeight() { return height; }
	virtual void render();
	void Update(DWORD dt) {}
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void CollisionProcess(DWORD dt, vector<LPGAMEOBJECT>* coObject)
	{
	}
};
