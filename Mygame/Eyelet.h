#pragma once
#include "GameObject.h"
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
class Eyelet : public Gameobject
{
protected:
	float ax;
	float ay;
	float maxVx, maxVy;
	float upperbar, lowerbar;
	ULONGLONG die_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void render();


public:
	Eyelet(float x, float y) : Gameobject(x, y)
	{
		state = EYELET_STATE_FLYING;
		maxVx = 0.9f;
		maxVy = 0.9f;
		ax = 0.1f;
		ay = 0.1f;
		objecttag = "Enermy";
		//upperbar = 140;
		//lowerbar = 120;
	}
	virtual void SetState(int state);
};


