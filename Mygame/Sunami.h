#pragma once
#include "Enermy.h"
#define SUNAMI_STATE_DIE 300
#define SUNAMI_DIE_TIMEOUT 500
#define SUNAMI_BBOX_WIDTH 16
#define SUNAMI_BBOX_HEIGHT 14
#define SUNAMI_BBOX_HEIGHT_DIE 7
#define SUNAMI_STATE_WALKING_X 100
#define SUNAMI_STATE_WALKING_Y 200
#define	ID_ANI_SUNAMI_WALKING_LEFT 2100
#define ID_ANI_SUNAMI_WALKING_RIGHT 2200
#define	ID_ANI_SUNAMI_WALKING_UP 2300
#define	ID_ANI_SUNAMI_WALKING_DOWN 2400
#define ID_ANI_SUNAMI_DIE 2500
#define SUNAMI_WALKING_SPEED 0.1f
class Sunami : public Enermy
{
protected:
	float ax;
	float ay;
	float maxVx, maxVy;
	ULONGLONG die_start;
	float lastcolX;
	float lastcolY;
	float lastXcol;
	float lastYcol;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnNoCollision(DWORD dt);
	virtual void render();
	int IsBlocking() { return 0; }
public:
	Sunami(float x, float y) : Enermy(x, y)
	{
		state = SUNAMI_STATE_WALKING_X;
		maxVx = 0.9f;
		maxVy = 0.9f;
		objecttag = "Enermy";
		nx = 1;
		ny = -1;
	}
	virtual void SetState(int state);
};

