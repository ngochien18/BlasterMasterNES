#pragma once
#include "Sophia.h"

#define SOPHIA_ANI_CABIN_STANDING_LEFT			24007
#define SOPHIA_ANI_CABIN_WALKING_LEFT			24008
#define SOPHIA_ANI_CABIN_STANDING_RIGHT			24011
#define SOPHIA_ANI_CABIN_WALKING_RIGHT			24012

class SophiaCabin : public Playerlevel {
protected:

	Sophia* base;

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

