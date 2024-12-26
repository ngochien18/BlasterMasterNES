#pragma once
#include "GameObject.h"
#include "Playerlevel.h"
#include "PlayScene.h"
#include "PlayerBullet.h"
#include "HealUp.h"
struct box
{
	float t, l, r, b;
};
class Enermy :
    public Gameobject
{
protected:
	float ax;
	float ay;
	float maxVx, maxVy;
	ULONGLONG die_start;
	float range;
	int health;
	DWORD lastShoot;

public:
	Enermy(float x, float y) : Gameobject(x, y)
	{
	}
	virtual void SetState(int state)=0;
	virtual box GetTrackingBox()
	{
		box trackingbox;
		this->GetBoundingBox(trackingbox.l, trackingbox.t, trackingbox.r, trackingbox.b);
		trackingbox.r += range;
		trackingbox.b -= range;
		return trackingbox;
	}
	float distancewithplayer();
	float distancewithplayerx();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) = 0;
	virtual void render() = 0;

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt) = 0;
	virtual void OnCollisionWith(LPCOLLISIONEVENT e) = 0;
	DWORD GetLastShoot() { return this->lastShoot; }
	void SetLastShoot() { this->lastShoot = GetTickCount64(); }
	void TakeDamage(int dame);
	//virtual void DropItem();
};

