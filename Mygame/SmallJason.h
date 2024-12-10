#pragma once

#include "Animations.h"
#include "Debug.h"
#include "Game.h"
#include "PlayScene.h"
#include"Playerlevel.h"
#define SMALLJASON_ACCEL_WALK	0.0005f
#define SMALLJASON_WALKING_SPEED		0.1f
//aniid small jason id 9xx
#pragma region ANIMATION_ID 

#define ID_ANI_SMALLJASON_IDLE_LEFT 900
#define ID_ANI_SMALLJASON_IDLE_RIGHT 901
#define ID_ANI_SMALLJASON_IDLE_UP 902
#define ID_ANI_SMALLJASON_IDLE_DOWN 903
#define ID_ANI_SMALLJASON_IDLE_CRAWLING_LEFT 904
#define ID_ANI_SMALLJASON_IDLE_CRAWLING_RIGHT 905
#define ID_ANI_SMALLJASON_IDLE_SWIMMING_LEFT 906
#define ID_ANI_SMALLJASON_IDLE_SWIMMING_RIGHT 907


#define ID_ANI_SMALLJASON_WALKING_LEFT 910
#define ID_ANI_SMALLJASON_WALKING_RIGHT 911

#define ID_ANI_SMALLJASON_WALKING_DOWN 912
#define ID_ANI_SMALLJASON_CRAWLING_LEFT 913
#define ID_ANI_SMALLJASON_CRAWLING_RIGHT 914
#define ID_ANI_SMALLJASON_SWIMMING_RIGHT 915
#define ID_ANI_SMALLJASON_SWIMMING_RIGHT 916


#define SMALLJASON_BIG_BBOX_WIDTH  7
#define SMALLJASON_BIG_BBOX_HEIGHT 12
#define ID_ANI_SMALLJASON_DIE 990
#define SMALLJASON_STATE_DIE -900
#define SMALLJASON_STATE_IDLE			0
#define SMALLJASON_STATE_WALK_LEFT	910
#define SMALLJASON_STATE_WALK_RIGHT	911
#define SMALLJASON_STATE_WALK_DOWN	912
#define SMALLJASON_STATE_CRAWL_LEFT	913
#define SMALLJASON_STATE_CRAWL_RIGHT 914
#define SMALLJASON_STATE_SWIM_LEFT	915
#define SMALLJASON_STATE_SWIM_RIGHT 916



class SmallJason : public Playerlevel
{
private:
	int GetAniIdSmall();
public:
	SmallJason(float x, float y) :Playerlevel(x, y)
	{
		maxVx = 0.0f;
		maxVy = 0.0f;
		ax = 0.0f;
		ay = 0.0f;
		state = SMALLJASON_STATE_IDLE;
		untouchable = 0;
		untouchable_start = -1;
	}
	void render()
	{
		Animations* animations = Animations::GetInstance();
		int aniId = -1;

		if (state == SMALLJASON_STATE_DIE)
			aniId = ID_ANI_SMALLJASON_DIE;
		else
			aniId = GetAniIdSmall();
		animations->Get(aniId)->Render(x, y);

		RenderBoundingBox();
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void SetState(int state);
	int GetState() { return this->state; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }
	void SetLevel(int l);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void OnkeyUP(int keycode);
	void OnkeyDown(int keycode);
	void Keystate(BYTE* key);
	void CollisionProcess(DWORD dt, vector<LPGAMEOBJECT>* coObject)
	{

	}
};


