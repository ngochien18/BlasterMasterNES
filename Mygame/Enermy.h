#pragma once
#include "GameObject.h"
class Enermy :
    public Gameobject
{
protected:
protected:
	float ax;
	float ay;
	float maxVx, maxVy;
	ULONGLONG die_start;
	float range;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom)=0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)=0;
	virtual void render()=0;

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt)=0;

	virtual void OnCollisionWith(LPCOLLISIONEVENT e)=0;

public:
	Enermy(float x, float y) : Gameobject(x, y)
	{
	}
	virtual void SetState(int state)=0;
};

