#pragma once
#include "Sophia.h"

#define SOPHIA_ANI_GUN_0_LEFT			4
#define SOPHIA_ANI_GUN_45_LEFT			5
#define SOPHIA_ANI_GUN_90_LEFT			6

#define SOPHIA_ANI_GUN_0_RIGHT			9
#define SOPHIA_ANI_GUN_45_RIGHT			10

#define SOPHIA_PART_ANI_SETS_ID		1

class SophiaGun : public Playerlevel {
protected:

	Sophia* parent;

public:
	SophiaGun(Sophia* sophia);
	~SophiaGun();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) {};
	void OnkeyUP(int keycode) {};
	void OnkeyDown(int keycode) {};
	void Keystate(BYTE* key) {};
	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; };
	void OnNoCollision(DWORD dt) {};
	virtual void CollisionProcess(DWORD dt, vector<LPGAMEOBJECT>* coObject) {};

};

