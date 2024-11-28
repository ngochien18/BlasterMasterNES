#pragma once
#include "GameObject.h"
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
class Sunami : public Gameobject
{
protected:
	float ax;
	float ay;
	float maxVx, maxVy;
	ULONGLONG die_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void render();


public:
	Sunami(float x, float y) : Gameobject(x, y)
	{
		state = SUNAMI_STATE_WALKING_X;
		maxVx = 0.9f;
		maxVy = 0.9f;
		objecttag = "Enermy";
		ax = 0.01f;
		ay = 0.0f;
	}
	virtual void SetState(int state);
};

