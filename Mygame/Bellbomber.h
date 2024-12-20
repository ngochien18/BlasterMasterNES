#pragma once
#include "Enermy.h"
#include "Playerlevel.h"
#include "PlayerBullet.h"
#include "Bomb.h"

#define BELLBOMBER_STATE_DIE 5500
#define BELLBOMBER_DIE_TIMEOUT 5500
#define BELLBOMBER_BBOX_WIDTH 16
#define BELLBOMBER_BBOX_HEIGHT 16
#define BELLBOMBER_BBOX_HEIGHT_DIE 7
#define BELLBOMBER_STATE_FLYING 5000
#define BELLBOMBER_STATE_IDLE 5010
#define BELLBOMBER_STATE_DROPPING_BOMB 5020
#define BELLBOMBER_STATE_FLYING_AWAY 5030
#define	ID_ANI_BELLBOMBER_FLYING_LEFT 5100
#define ID_ANI_BELLBOMBER_FLYING_RIGHT 5200
#define ID_ANI_BELLBOMBER_DROPPING_BOMB_LEFT 5300
#define ID_ANI_BELLBOMBER_DROPPING_BOMB_RIGHT 5400
#define ID_ANI_BELLBOMBER_DIE 5500
#define	ID_ANI_BELLBOMBER_IDLE 5600
#define ID_ANI_BELLBOMBER_FLYING_AWAY 5700
#define BELLBOMBER_FLYING_SPEED 0.1f

class Bellbomber : public Enermy
{
protected:
	float ax;
	float ay;
	float maxVx, maxVy;
	ULONGLONG die_start;

	float distance;
	int GunDirectionX;
	int delaytimetoshoot;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	Bellbomber(float x, float y) : Enermy(x, y)
	{
		state = BELLBOMBER_STATE_IDLE;
		maxVx = 0.3f;
		maxVy = 0.0f;
		objecttag = "Enermy";
		ax = 0.01f;
		ay = 0.0f;
		maxVx = 0.2f;
		maxVy = 0.5f;
		GunDirectionX = -1;
		health = 50;
		delaytimetoshoot = 100;
	}
	virtual void SetState(int state);
	virtual void CollisionProcess(DWORD dt, vector<LPGAMEOBJECT>* coObject);
	void DropBomb();
};





