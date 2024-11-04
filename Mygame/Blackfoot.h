#pragma once
#include "GameObject.h"
#define BLACKFOOT_STATE_DIE 300
#define BLACKFOOT_DIE_TIMEOUT 500
#define BLACKFOOT_BBOX_WIDTH 16
#define BLACKFOOT_BBOX_HEIGHT 14
#define BLACKFOOT_BBOX_HEIGHT_DIE 7
#define BLACKFOOT_STATE_WALKING 100
#define	ID_ANI_BLACKFOOT_WALKING_LEFT 1100
#define ID_ANI_BLACKFOOT_WALKING_RIGHT 1200
#define ID_ANI_BLACKFOOT_DIE 1300
#define BLACKFOOT_WALKING_SPEED 0.1f
class Blackfoot: public Gameobject
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
	Blackfoot(float x, float y) : Gameobject(x, y)
	{
		state = BLACKFOOT_STATE_WALKING;
		maxVx = 0.0f;
		maxVy = 0.0f;
		ax = 0.0f;
		ay = 0.0f;
	}
	virtual void SetState(int state);
};

