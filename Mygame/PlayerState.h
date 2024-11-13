#pragma once
#include "Game.h"
#include "PlayerState.h"
#include "Playerdata.h"
#include "Windows.h"
enum class StateName
{
//Small
	SmallIdle=10,
//Big
	BigIdle = 0,
	BigWalking=1,
//Sophia
	SophiaRunning=20
};
class PlayerState
{
protected:	
	Player* data;
public:
	PlayerState()
	{

	}
	PlayerState(Player* data)
	{
		this->data = data;
	}
	~PlayerState() = default;
	virtual StateName GetState() = 0;
	virtual void HandleKeyBoard(int keycode)=0;
};
