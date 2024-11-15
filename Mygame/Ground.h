#pragma once

#include "GameObject.h"

#define ID_ANI_GROUND 100000
#define GROUND_WIDTH 16
#define GROUND_BBOX_WIDTH 16
#define GROUND_BBOX_HEIGHT 16

class Ground : public Gameobject {
public:
	Ground(float x, float y) : Gameobject(x, y) {}
	void render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};
