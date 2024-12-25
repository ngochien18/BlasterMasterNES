#include "HealUp.h"
#include"Playablechracter.h"
#include "PlayScene.h"
#include "Game.h"
#include "Colision.h"
#include "string"
void HealUp::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	SetState(this->state);
	vy = ay * dt;
	vx = ax * dt;

	if (abs(vx) > abs(maxVx)) vx = maxVx * nx;
	if (abs(vy) > abs(maxVy))	vy = maxVy * ny;
	Gameobject::Update(dt, coObjects);
	//Colision::GetInstance()->process(this, dt, coObjects);

}
void HealUp::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->objd->objecttag == "Player"|| e->objs->objecttag == "Player")
	{
		isdeleted = true;
	}
}
void HealUp::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void HealUp::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - HEALUP_BBOX_WIDTH / 2;
	top = y + HEALUP_BBOX_HEIGHT / 2;
	right = left + HEALUP_BBOX_WIDTH;
	bottom = top - HEALUP_BBOX_HEIGHT;
}
void HealUp::render()
{
	int aniID = 0;
	if (state == HEALUP_STATE_ACTIVE)
	{
		aniID = ID_ANI_HEALUP_ACTIVE;
	}
	Animations::GetInstance()->Get(aniID)->Render(x, y);
	RenderBoundingBox();
}
void HealUp::SetState(int state)
{
	Gameobject::SetState(state);
	switch (state)
	{
	case HEALUP_STATE_ACTIVE:
		break;

	}
}