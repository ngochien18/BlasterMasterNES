#pragma once
#include "Enermy.h"
#include "OffBullet.h"
#define OFFSIDE_DIE_TIMEOUT 500
#define OFFSIDE_BBOX_WIDTH 18
#define OFFSIDE_BBOX_HEIGHT 20
#define OFFSIDE_BBOX_HEIGHT_DIE 7
#define OFFSIDE_STATE_IDLE 100
#define OFFSIDE_STATE_SHOOT_LEFT 200
#define OFFSIDE_STATE_SHOOT_RIGHT 300
#define OFFSIDE_STATE_DIE 400
#define	ID_ANI_OFFSIDE_SHOOT_LEFT 6100
#define ID_ANI_OFFSIDE_SHOOT_RIGHT 6200
#define ID_ANI_OFFSIDE_DIE 6300
#define ID_ANI_OFFSIDE_IDLE 6400
#define OFFSIDE_SHOOT_RANGE 100

class Offside : public Enermy
{
protected:
	int GunDirectionX;
	float distance;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	Offside(float x, float y) : Enermy(x, y)
	{
		state = OFFSIDE_STATE_IDLE;
		objecttag = "Enermy";
		ax = 0;
		ay = 0;
		nx = 0;
		ny = 0;
		maxVx = 0;
		maxVy = 0;
		health = 200;
		GunDirectionX = 1;
	}
	virtual void SetState(int state);
	virtual void CollisionProcess(DWORD dt, vector<LPGAMEOBJECT>* coObject);
	void Shoot();
};


