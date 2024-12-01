#pragma once

#include "GameObject.h"
#include "Game.h"

#define ID_ANI_GROUND 100000
#define GROUND_WIDTH 16
#define GROUND_BBOX_WIDTH 16
#define GROUND_BBOX_HEIGHT 16

class Ground : public Gameobject {
private:
	int width;
	int height;
public:
	Ground();
	Ground(float x, float y, int width, int height);
	virtual int IsBlocking() { return 1; }
	~Ground();
	int GetWidth() { return width; }
	int GetHeight() { return height; }
	virtual void render();
	void Update(DWORD dt) {}
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

};
