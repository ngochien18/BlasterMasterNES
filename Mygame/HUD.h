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


#define HUD_WIDTH 55
#define HUD_BBOX_WIDTH 55
#define HUD_BBOX_HEIGHT 180

class HUD : public Gameobject
{
private:

	DWORD dt;
	Camera* camera;
	Playerlevel* player;
	float width, height;
public:
	HUD(float x, float y) : Gameobject(x, y) {
		alwaysrender = false;
		width = 10;
		height = 55;
	};

	virtual void Update(DWORD dt, vector<Gameobject*>* coObjects);

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }

	virtual void render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) {//muon su dung quadtree phai co bounding box
		left = x - width / 2;
		top = y + height / 2;
		right = left + width;
		bottom = top - height;
	};
	virtual void CollisionProcess(DWORD dt, vector<LPGAMEOBJECT>* coObject) {};

};


