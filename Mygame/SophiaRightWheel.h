#pragma once
#include "Sophia.h"

#define SOPHIA_ANI_STANDING			24000
#define SOPHIA_ANI_LEFT_WALK		24001
#define SOPHIA_ANI_RIGHT_WALK		24002

#define SOPHIA_PART_ANI_SETS_ID		1

class SophiaRightWheel : public Playerlevel {
protected:

	Sophia* base;

public:
	SophiaRightWheel(Sophia* sophia);
	~SophiaRightWheel();

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

