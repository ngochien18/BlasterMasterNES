#pragma once
#include "GameObject.h"
#define BELLBOMBER_STATE_DIE 300
#define BELLBOMBER_DIE_TIMEOUT 500
#define BELLBOMBER_BBOX_WIDTH 16
#define BELLBOMBER_BBOX_HEIGHT 14
#define BELLBOMBER_BBOX_HEIGHT_DIE 7
#define BELLBOMBER_STATE_WALKING 100
#define	ID_ANI_BELLBOMBER_WALKING_LEFT 1100
#define ID_ANI_BELLBOMBER_WALKING_RIGHT 1200
#define ID_ANI_BELLBOMBER_DIE 1300
#define BELLBOMBER_WALKING_SPEED 0.1f
class Bellbomber : public Gameobject
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
	Bellbomber(float x, float y) : Gameobject(x, y)
	{
		state = BELLBOMBER_STATE_WALKING;
		maxVx = 0.9f;
		maxVy = 0.0f;
		ax = 0.01f;
		ay = 0.0f;
	}
	virtual void SetState(int state);
};


