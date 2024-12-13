#pragma once
#include "Utils.h"
#include "GameObject.h"
#include "Camera.h"
#include "Playablechracter.h"
#include "Playerlevel.h"


#define BOUNDRRY_X_MAX 1792.0f

#define HUD_ANI_100	    		50001
#define HUD_ANI_90				50002
#define HUD_ANI_80				50003
#define HUD_ANI_70				50004
#define HUD_ANI_60				50005
#define HUD_ANI_50				50006
#define HUD_ANI_40				50007
#define HUD_ANI_30				50008
#define HUD_ANI_20				50009
#define HUD_ANI_10				50010


#define HUD_ANI_SETS_ID					40

class HUD : public Gameobject
{
private:

	DWORD dt;
	Camera* camera;
	Playerlevel* player;
public:
	HUD(float x, float y) : Gameobject(x, y) {

	};

	virtual void Update(DWORD dt, vector<Gameobject*>* coObjects);

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }

	virtual void render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) {};
	virtual void CollisionProcess(DWORD dt, vector<LPGAMEOBJECT>* coObject) {};

};


