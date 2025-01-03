#pragma once

#include "EffectItem.h"
#define HEALUP_BBOX_WIDTH 16
#define HEALUP_BBOX_HEIGHT 16

#define HEALUP_STATE_ACTIVE 100
#define ID_ANI_HEALUP_ACTIVE 21000

class HealUp : public EffectItem
{
protected:
	int amount;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	HealUp(float x, float y) : EffectItem(x, y)
	{
		state = HEALUP_STATE_ACTIVE;
		objecttag = "HealUp";
		amount = 50;
		vx = 0;
		vy = 0;
		ay = -0.01f;
		maxVy = 0.1f;
		nx = 0;
		ny = -1;
	}
	virtual void SetState(int state);
	virtual void CollisionProcess(DWORD dt, vector<LPGAMEOBJECT>* coObject);
	int GetAmount() { return amount; };
};
