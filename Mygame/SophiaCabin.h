#pragma once
#include "Sophia.h"

#define SOPHIA_ANI_CABIN_STANDING_LEFT			7
#define SOPHIA_ANI_CABIN_WALKING_LEFT			8
#define SOPHIA_ANI_CABIN_STANDING_RIGHT			11
#define SOPHIA_ANI_CABIN_WALKING_RIGHT			12

#define SOPHIA_PART_ANI_SETS_ID		1

class SophiaCabin : public Playerlevel {
protected:

	Sophia* parent;

public:
	SophiaCabin(Sophia* sophia);
	~SophiaCabin();

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

