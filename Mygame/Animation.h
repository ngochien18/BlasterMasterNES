#pragma once
#include "Animationframe.h"
#include <vector>
#include "Sprites.h"
#include "AnimationFrame.h"
using namespace std;
class Animation
{
	ULONGLONG lastFrameTime;
	int defaultTime;
	int currentFrame;
	vector<LPANIMATION_FRAME> frames;
public:
	Animation(int defaultTime = 100) { this->defaultTime = defaultTime; lastFrameTime = -1; currentFrame = -1; }
	void Add(int spriteId, DWORD time = 0);
	void Render(float x, float y);
};
typedef Animation* LPANIMATION;

