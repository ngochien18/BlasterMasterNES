#pragma once
#include "GameObject.h"
class Playerlevel :
	public Gameobject
{
protected:
	float maxVx;
	float maxVy;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 
	int untouchable;
	ULONGLONG untouchable_start;
	static int health;
public:
	Playerlevel(float x, float y) :Gameobject(x, y)
	{
		objecttag = "Player";
	}
	static void changehealth(int value)
	{
		health += value;
	}
	virtual void OnkeyUP(int keycode)=0;
	virtual void OnkeyDown(int keycode)=0;
	virtual void Keystate(BYTE* key)=0;
	virtual void render() = 0;
	virtual void Delete() { isdeleted = true; }
	virtual void SetState(int state) { this->state = state; }
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;
	virtual void Update(DWORD dt, vector<Gameobject*>* coObjects = NULL) {};
	virtual int IsBlocking() { return 0; }
	virtual void CollisionProcess(DWORD dt, vector<LPGAMEOBJECT>* coObject)=0;
};
