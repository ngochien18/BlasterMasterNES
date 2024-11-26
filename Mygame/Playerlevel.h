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
public:
	Playerlevel(float x, float y) :Gameobject(x, y)
	{

	}
	virtual void render() = 0;
	virtual void Delete() { isdeleted = true; }
	virtual void SetState(int state) { this->state = state; }
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;
	virtual void Update(DWORD dt, vector<Gameobject*>* coObjects = NULL) {};
};
