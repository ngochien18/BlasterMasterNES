#pragma once
#include "GameObject.h"
#define ENERMY_STATE_DIE 300
#define ENERMY_DIE_TIMEOUT 500
#define ENERMY_BBOX_WIDTH 16
#define ENERMY_BBOX_HEIGHT 14
#define ENERMY_BBOX_HEIGHT_DIE 7
#define ENERMY_STATE_WALKING 100
#define	ID_ANI_ENERMY_WALKING_LEFT 1100
#define ID_ANI_ENERMY_WALKING_RIGHT 1200
#define ID_ANI_ENERMY_DIE 1300
#define ENERMY_WALKING_SPEED 0.1f
class Enermy: public Gameobject
{
protected:
	float ax;
	float ay;
	float maxVx, maxVy;
	ULONGLONG die_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void render();

	//virtual int IsCollidable() { return 1; };
	//virtual int IsBlocking() { return 0; }
	//virtual void OnNoCollision(DWORD dt);

	//virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	Enermy(float x, float y) : Gameobject(x, y)
	{
		state = ENERMY_STATE_WALKING;
		maxVx = 0.0f;
		maxVy = 0.0f;
		ax = 0.0f;
		ay = 0.0f;
	}
	virtual void SetState(int state);
};

