#include "Sunami.h"
#include"Playablechracter.h"
#include "PlayScene.h"
#include "Game.h"
void Sunami::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	SetState(this->state);
	vy += ay * dt;
	vx += ax * dt;

	if (abs(vx) > abs(maxVx)) vx = maxVx * nx;
	if (abs(vy) > abs(maxVy))	vy = maxVy * ny;
	x += vx;
	y += vy;
	if ((state == SUNAMI_STATE_DIE) && (GetTickCount64() - die_start > SUNAMI_DIE_TIMEOUT))
	{
		isdeleted = true;
		return;
	}

	Gameobject::Update(dt, coObjects);
}
void Sunami::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == SUNAMI_STATE_DIE)
	{
		left = x - SUNAMI_BBOX_WIDTH / 2;
		top = y - SUNAMI_BBOX_HEIGHT_DIE / 2;
		right = left + SUNAMI_BBOX_WIDTH;
		bottom = top + SUNAMI_BBOX_HEIGHT_DIE;
	}
	else
	{
		left = x - SUNAMI_BBOX_WIDTH / 2;
		top = y - SUNAMI_BBOX_HEIGHT / 2;
		right = left + SUNAMI_BBOX_WIDTH;
		bottom = top + SUNAMI_BBOX_HEIGHT;
	}
}
void Sunami::render()
{
	int aniID = 0;
	if (state == SUNAMI_STATE_DIE)
	{
		aniID = ID_ANI_SUNAMI_DIE;
	}
	else if (ax >= 0)
	{
		aniID = ID_ANI_SUNAMI_WALKING_RIGHT;
	}
	else if (ax < 0)
	{
		aniID = ID_ANI_SUNAMI_WALKING_LEFT;
	}
	if (ay >= 0)
	{
		aniID = ID_ANI_SUNAMI_WALKING_DOWN;
	}
	else if (ay < 0)
	{
		aniID = ID_ANI_SUNAMI_WALKING_UP;
	}


	Animations::GetInstance()->Get(aniID)->Render(x, y);
	RenderBoundingBox();
}
void Sunami::SetState(int state)
{
	float cx = 0;
	float cy = 0;
	Game::GetInstance()->GetCamPos(cx, cy);
	Gameobject::SetState(state);
	switch (state)
	{
	case SUNAMI_STATE_DIE:
		die_start = GetTickCount64();
		y += (SUNAMI_BBOX_HEIGHT - SUNAMI_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case SUNAMI_STATE_WALKING_X:

		if (ax > 0 && x - cx > Game::GetInstance()->GetBackBufferWidth() - 10) { ax = -ax; nx = -1; }
		if (ax < 0 && x - cx < 10) { ax = -ax; nx = 1; }
		break;
	case SUNAMI_STATE_WALKING_Y:

		if (ay > 0 && y > 180) { ay = -ay; ny = -1; }
		if (ay < 0 && y < 10) { ay = -ay; ny = 1; }
		break;

	}
}