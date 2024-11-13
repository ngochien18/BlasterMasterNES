#pragma once
#include "Game.h"
class Game;
class Camera
{
	float cam_x = 0.0f;
	float cam_y = 0.0f;
	int BackBufferWidth = 0;
	int BackBufferHeight = 0;
public:
	Camera(int x, int y)
	{
		x = BackBufferHeight;
		y = BackBufferWidth;
	}
	void SetCamPos(float x, float y) { cam_x = x; cam_y = y; }
	void Trans(float& x, float& y)
	{
		y = y-BackBufferWidth;
	}
	void GetCamPos(float& x, float& y)
	{
		x = cam_x;
		y = cam_y;
	}
};
