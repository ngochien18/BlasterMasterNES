#pragma once
#include "Enermy.h"
#define EYELET_STATE_DIE 300
#define EYELET_DIE_TIMEOUT 500
#define EYELET_BBOX_WIDTH 16
#define EYELET_BBOX_HEIGHT 14
#define EYELET_BBOX_HEIGHT_DIE 7
#define EYELET_STATE_FLYING 4000
#define ID_ANI_EYELET_FLYING_RIGHT 4100
#define	ID_ANI_EYELET_FLYING_LEFT 4200
#define ID_ANI_EYELET_DIE 4300
#define EYELET_WALKING_SPEED 0.1f
class Eyelet : public Enermy
{
protected:

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	


public:
	Eyelet(float x, float y) : Enermy(x, y)
	{
		state = EYELET_STATE_FLYING;
		maxVx = 0.2f;
		maxVy = 0.2f;
		ax = 0.02f;
		ay = 0.02f;
		objecttag = "Enermy";
		health = 50;
		
	}
	virtual void SetState(int state);
	virtual void CollisionProcess(DWORD dt, vector<LPGAMEOBJECT>* coObject);
};


