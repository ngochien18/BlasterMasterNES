#pragma once
#include "GameObject.h"

#define BLACKFOOT_GRAVITY 0.002f
#define BLACKFOOT_WALKING_SPEED 0.05f


#define BLACKFOOT_BBOX_WIDTH 16
#define BLACKFOOT_BBOX_HEIGHT 14
#define BLACKFOOT_BBOX_HEIGHT_DIE 7

#define BLACKFOOT_DIE_TIMEOUT 500

#define BLACKFOOT_STATE_WALKING_LEFT 100
#define BLACKFOOT_STATE_DIE 200
#define BLACKFOOT_STATE_WALKING_RIGHT 300

#define ID_ANI_BLACKFOOT_WALKING_LEFT 5000
#define ID_ANI_BLACKFOOT_DIE 5001
#define ID_ANI_BLACKFOOT_WALKING_RIGHT 5002

class CBlackfoot : public CGameObject
{
protected:
	float ax;
	float ay;

	ULONGLONG die_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CBlackfoot(float x, float y);
	virtual void SetState(int state);
};