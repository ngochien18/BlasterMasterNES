#pragma once
#include "Enermy.h"
#define BLACKFOOT_STATE_DIE 300
#define BLACKFOOT_DIE_TIMEOUT 500
#define BLACKFOOT_BBOX_WIDTH 12
#define BLACKFOOT_BBOX_HEIGHT 24
#define BLACKFOOT_BBOX_HEIGHT_DIE 7
#define BLACKFOOT_STATE_WALKING_RL 100
#define BLACKFOOT_WALKING_DU 200
#define	ID_ANI_BLACKFOOT_WALKING_LEFT 1100
#define ID_ANI_BLACKFOOT_WALKING_RIGHT 1200
#define ID_ANI_BLACKFOOT_DIE 1300
#define BLACKFOOT_WALKING_SPEED 0.2f

class Blackfoot : public Enermy
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
	Blackfoot(float x, float y) : Enermy(x, y)
	{
		state = BLACKFOOT_STATE_WALKING_RL;
		maxVx = 0.5f;
		maxVy = 0.5f;
		objecttag = "Enermy";
		ax = 0.01f;
		ay = 0.0f;
		range = 100;
	}
	virtual void SetState(int state);
	virtual void CollisionProcess(DWORD dt, vector<LPGAMEOBJECT>* coObject);
};

