#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "Debug.h"
#include "Game.h"
#include "PlayScene.h"
#include "Playerlevel.h"
#include"Colision.h"
#include"HealUp.h"
#include"SmallJason.h"
#define JASON_DASH_TIME 200
#define JASON_LEVEL_SMALL 1
#define JASON_LEVEL_BIG 2

#define JASON_ACCEL_WALK	0.005f
#define JASON_WALKING_SPEED		3.5
//aniid
#pragma region ANIMATION_ID

#define ID_ANI_JASON_IDLE_RIGHT 400
#define ID_ANI_JASON_IDLE_LEFT 401
#define ID_ANI_JASON_IDLE_UP 402
#define ID_ANI_JASON_IDLE_DOWN 403


#define ID_ANI_JASON_WALKING_RIGHT 500
#define ID_ANI_JASON_WALKING_LEFT 501

#define ID_ANI_JASON_WALKING_UP 600
#define ID_ANI_JASON_WALKING_DOWN 601

#define JASON_BIG_BBOX_WIDTH  14
#define JASON_BIG_BBOX_HEIGHT 24
#define ID_ANI_JASON_DIE 999
#define JASON_STATE_DIE -100
#define BIG_JASON_STATE_IDLE			0
#define BIG_JASON_STATE_WALK_RIGHT	100
#define BIG_JASON_STATE_WALK_LEFT	200
#define BIG_JASON_STATE_WALK_UP			300
#define BIG_JASON_STATE_WALK_DOWN		400
class Playablechracter : public Playerlevel
{	
private:
	int GetAniIdBig();
public:
	Playablechracter (float x,float y) :Playerlevel(x, y)
	{
		maxVx = 0.0f;
		maxVy = 0.0f;
		ax = 0.0f;
		ay = 0.0f;
		objecttag = "Player";
		state = BIG_JASON_STATE_IDLE;
		untouchable = 0;
		untouchable_start = -1;
	}
	void render()
	{
		Animations* animations = Animations::GetInstance();
		int aniId = -1;

		if (state == JASON_STATE_DIE)
			aniId = ID_ANI_JASON_DIE;
		else {
			aniId = GetAniIdBig();
		}
		animations->Get(aniId)->Render(x, y);

		RenderBoundingBox();
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void SetState(int state);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }
	void SetLevel(int l);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void OnkeyUP(int keycode);
	void OnkeyDown(int keycode);
	void Keystate(BYTE* key);
	virtual int IsCollidable() { return 1; };
	void OnNoCollision(DWORD dt)
	{
		x += vx ;
		y += vy ;
	}
	void OnCollisionWith(LPCOLLISIONEVENT e)
	{
		if (e->objd->objecttag=="Ground")
		{
			Colision::GetInstance()->PushingX(e->t, vx, e->nx, x, e);
			Colision::GetInstance()->PushingY(e->t, vy, e->ny, y, e);
		}
		/*if (dynamic_cast<HealUp*>(e->obj))
		{
			HealUp* healup = dynamic_cast<HealUp*>(e->obj);
			healup->SetState(HEALUP_STATE_DIE);
			this->ResetHeal();
		}*/
		if (e->objd->objecttag == "Item")
		{			
			//this->SetState(JASON_LEVEL_SMALL);
			((LPPLAYSCENE)Game::GetInstance()->GetCurrentScene())->Setplayerstate(new SmallJason(x, y));
			e->objd->Delete();
		}
	}
	virtual void CollisionProcess(DWORD dt, vector<LPGAMEOBJECT>* coObject);
};

