#pragma once
#include "GameObject.h"
#include "Utils.h"
#include "Playerlevel.h"

#define SOPHIA_WALKING_SPEED					0.15f 
//0.1f
#define SOPHIA_JUMP_SPEED_Y						0.5f
#define SOPHIA_JUMP_DEFLECT_SPEED				0.2f
#define SOPHIA_GRAVITY							0.002f
#define SOPHIA_DIE_DEFLECT_SPEED				0.5f

#define SOPHIA_STATE_IDLE						0
#define SOPHIA_STATE_WALKING_RIGHT				100
#define SOPHIA_STATE_WALKING_LEFT				200					
#define SOPHIA_STATE_JUMP						300
#define SOPHIA_STATE_DIE						400
#define SOPHIA_STATE_HEAD_UP					500
#define SOPHIA_STATE_FIRE						600
#define SOPHIA_STATE_FIRE_UP					700

#define SOPHIA_ANI_BIG_IDLE_RIGHT				0
#define SOPHIA_ANI_BIG_IDLE_LEFT				1

#define SOPHIA_ANI_WHEEL_STANDING				0
#define SOPHIA_ANI_WHEEL_LEFT					1
#define SOPHIA_ANI_WHEEL_RIGHT					2
#define SOPHIA_ANI_MIDDLE						3
#define SOPHIA_ANI_GUN_0						4
#define SOPHIA_ANI_GUN_45						5
#define SOPHIA_ANI_GUN_90						6
#define SOPHIA_ANI_CABIN_STANDING				7
#define SOPHIA_ANI_CABIN_WALKING				8
#define SOPHIA_ANI_CABIN_HEAD_LEFT				13
#define SOPHIA_ANI_CABIN_HEAD_RIGHT				14

#define SOPHIA_ANI_DIE							69

#define	SOPHIA_LEVEL_JASON					1
#define	SOPHIA_LEVEL_SOPHIA				2

#define SOPHIA_BIG_BBOX_WIDTH				28
#define SOPHIA_BIG_BBOX_HEIGHT				14

#define SOPHIA_SMALL_BBOX_WIDTH				13
#define SOPHIA_SMALL_BBOX_HEIGHT			15

#define SOPHIA_UNTOUCHABLE_TIME				1000

#define FALLING_VELOCITY_UPPER_LIMITATION	0.02f


class SophiaMiddle;
class SophiaRightWheel;
class SophiaLeftWheel;
class SophiaCabin;
class SophiaGun;


class Sophia : public Playerlevel
{

	SophiaMiddle* middle;
	SophiaRightWheel* rightWheel;
	SophiaLeftWheel* leftWheel;
	SophiaCabin* cabin;
	SophiaGun* gun;

public:
	Sophia(float x, float y) : Playerlevel(x, y)
	{
		maxVx = 0.0f;
		maxVy = 0.0f;
		ax = 0.0f;
		ay = 0.0f;
		state = SOPHIA_STATE_IDLE;
		untouchable = 0;
		untouchable_start = -1;

		this->x = x;
		this->y = y;

		/*middle = new SophiaMiddle(this);
		rightWheel = new SophiaRightWheel(this);
		leftWheel = new SophiaLeftWheel(this);
		cabin = new SophiaCabin(this);
		gun = new SophiaGun(this);*/
	}

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void render();
	void SetState(int state);

};
