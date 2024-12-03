#pragma once
#include "Enermy.h"
#define BELLBOMBER_STATE_DIE 300
#define BELLBOMBER_DIE_TIMEOUT 500
#define BELLBOMBER_BBOX_WIDTH 16
#define BELLBOMBER_BBOX_HEIGHT 14
#define BELLBOMBER_BBOX_HEIGHT_DIE 7
#define BELLBOMBER_STATE_FLYING 5000
#define	ID_ANI_BELLBOMBER_FLYING_LEFT 5100
#define ID_ANI_BELLBOMBER_FLYING_RIGHT 5200
#define ID_ANI_BELLBOMBER_DROPPING_BOMB_LEFT 5300
#define ID_ANI_BELLBOMBER_DROPPING_BOMB_RIGHT 5400
#define ID_ANI_BELLBOMBER_DIE 5500
#define BELLBOMBER_FLYING_SPEED 0.1f
class Bellbomber : public Enermy
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
	Bellbomber(float x, float y) : Enermy(x, y)
	{
		state = BELLBOMBER_STATE_FLYING;
		maxVx = 0.9f;
		maxVy = 0.0f;
		objecttag = "Enermy";
		ax = 0.01f;
		ay = 0.0f;
	}
	virtual void SetState(int state);
};


