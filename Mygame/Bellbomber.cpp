#include "Bellbomber.h"
#include"Playablechracter.h"
#include "PlayScene.h"
#include "Game.h"
void Bellbomber::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	SetState(this->state);
	vy += ay * dt;
	vx += ax * dt;

	if (abs(vx) > abs(maxVx)) vx = maxVx * nx;
	if (abs(vy) > abs(maxVy))	vy = maxVy * ny;
	x += vx;
	y += vy;
	if ((state == BELLBOMBER_STATE_DIE) && (GetTickCount64() - die_start > BELLBOMBER_DIE_TIMEOUT))
	{
		isdeleted = true;
		return;
	}

	Gameobject::Update(dt, coObjects);
}
void Bellbomber::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == BELLBOMBER_STATE_DIE)
	{
		left = x - BELLBOMBER_BBOX_WIDTH / 2;
		top = y - BELLBOMBER_BBOX_HEIGHT_DIE / 2;
		right = left + BELLBOMBER_BBOX_WIDTH;
		bottom = top + BELLBOMBER_BBOX_HEIGHT_DIE;
	}
	else
	{
		left = x - BELLBOMBER_BBOX_WIDTH / 2;
		top = y - BELLBOMBER_BBOX_HEIGHT / 2;
		right = left + BELLBOMBER_BBOX_WIDTH;
		bottom = top + BELLBOMBER_BBOX_HEIGHT;
	}
}
void Bellbomber::render()
{
	int aniID = 0;
	if (state == BELLBOMBER_STATE_DIE)
	{
		aniID = ID_ANI_BELLBOMBER_DIE;
	}
	else if (vx >= 0)
	{
		aniID = ID_ANI_BELLBOMBER_WALKING_RIGHT;
	}
	else
	{
		aniID = ID_ANI_BELLBOMBER_WALKING_LEFT;
	}


	Animations::GetInstance()->Get(aniID)->Render(x, y);
	RenderBoundingBox();
}
void Bellbomber::SetState(int state)
{
	Gameobject::SetState(state);
	switch (state)
	{
	case BELLBOMBER_STATE_DIE:
		die_start = GetTickCount64();
		y += (BELLBOMBER_BBOX_HEIGHT - BELLBOMBER_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case BELLBOMBER_STATE_WALKING:

		if (ax > 0 && x > 250) { ax = -ax; nx = -1; }
		if (ax < 0 && x < 50) { ax = -ax; nx = 1; }
		
	}
}