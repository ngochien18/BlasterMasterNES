#pragma once
#include "GameObject.h"
#include "Utils.h"
#include "Playerlevel.h"

#define SOPHIA_WALKING_SPEED					0.15f 

#define SOPHIA_STATE_IDLE						0
#define SOPHIA_STATE_WALKING_RIGHT				100
#define SOPHIA_STATE_WALKING_LEFT				200					
#define SOPHIA_STATE_DIE						400

#define SOPHIA_ANI_BIG_IDLE_RIGHT				24000
#define SOPHIA_ANI_BIG_IDLE_LEFT				24001

#define SOPHIA_ANI_WHEEL_STANDING				24000
#define SOPHIA_ANI_WHEEL_LEFT					24001
#define SOPHIA_ANI_WHEEL_RIGHT					24002
#define SOPHIA_ANI_MIDDLE						24003
#define SOPHIA_ANI_GUN_0						24004
#define SOPHIA_ANI_GUN_45						24005
#define SOPHIA_ANI_GUN_90						24006
#define SOPHIA_ANI_CABIN_STANDING				24007
#define SOPHIA_ANI_CABIN_WALKING				24008
#define SOPHIA_ANI_CABIN_HEAD_LEFT				24013
#define SOPHIA_ANI_CABIN_HEAD_RIGHT				24014

#define SOPHIA_ANI_DIE							69

#define	SOPHIA_LEVEL_JASON					1
#define	SOPHIA_LEVEL_SOPHIA					2

#define SOPHIA_BIG_BBOX_WIDTH				28
#define SOPHIA_BIG_BBOX_HEIGHT				14

#define SOPHIA_UNTOUCHABLE_TIME				1000

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
	Sophia(float x, float y);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void render();
	void SetState(int state);
	void OnkeyUP(int keycode) {};
	void OnkeyDown(int keycode) {};
	void Keystate(BYTE* key);
	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; };
	void OnNoCollision(DWORD dt) {};
	virtual void CollisionProcess(DWORD dt, vector<LPGAMEOBJECT>* coObject) {};

};
