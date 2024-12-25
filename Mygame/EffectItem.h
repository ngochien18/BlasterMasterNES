#include "GameObject.h"
#include "Timer.h"
#include "Game.h"

#define ITEM_ACTIVE_UNACTIVE 0
#define ITEM_STATE_ACTIVE 100

#define ITEM_BBOX_WIDTH		16
#define ITEM_BBOX_HEIGHT	16
#define ITEM_LIFETIME	3600
#define ITEM_ANI_POWER_UP		0

class EffectItem;
typedef EffectItem* LPGAMEEFFECTITEM;

class EffectItem : public Gameobject
{
protected:
	float ax;
	float ay;
	float maxVx, maxVy;

	bool isFlashy;
	bool isAutoDisappear;

public:
	EffectItem(float x, float y) : Gameobject(x, y)
	{
		vx = 0;
		vy = 0;
		ax = 0;
		ay = 0;
		maxVx = 0;
		maxVy = 0;
	}

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) = 0;
	virtual void render() = 0;
	virtual void SetState(int state) = 0;

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt) = 0;

	virtual void OnCollisionWith(LPCOLLISIONEVENT e) = 0;

};
