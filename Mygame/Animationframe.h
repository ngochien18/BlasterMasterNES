#pragma once
#include "Sprite.h"
class Animationframe
{
	LPSPRITE sprite;
	DWORD time;

public:
	Animationframe(LPSPRITE sprite, int time) { this->sprite = sprite; this->time = time; }
	DWORD GetTime() { return time; }
	LPSPRITE GetSprite() { return sprite; }
};
typedef Animationframe* LPANIMATION_FRAME;
