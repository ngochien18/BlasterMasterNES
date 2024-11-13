#pragma once
#include "Game.h"
class Playerdata;
class PlayerState;
#define JASON_ACCEL_WALK	0.0005f
#define JASON_WALKING_SPEED		0.1f
enum ControlKey
{
	LEFT = DIK_A,
	RIGHT = DIK_D,
	UP=DIK_W,
	DOWN=DIK_S
};
class Player
{
public:
	Player()
	{
		
	}
	~Player();
	Playerdata* mPlayerdata;
	PlayerState* mPlayerstate;
protected:
};

