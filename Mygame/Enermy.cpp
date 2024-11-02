#include "Enermy.h"
#include"Playablechracter.h"
#include "PlayScene.h"
#include "Game.h"
void Enermy::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	SetState(this->state);
	vy += ay * dt;
	vx += ax * dt;

	if (abs(vx) > abs(maxVx)) vx = maxVx*nx;
	if (abs(vy) > abs(maxVy))	vy = maxVy*ny;
	x += vx;
	y += vy;
	if ((state == ENERMY_STATE_DIE) && (GetTickCount64() - die_start > ENERMY_DIE_TIMEOUT))
	{
		isdeleted = true;
		return;
	}

	Gameobject::Update(dt, coObjects);
}
void Enermy::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == ENERMY_STATE_DIE)
	{
		left = x - ENERMY_BBOX_WIDTH / 2;
		top = y - ENERMY_BBOX_HEIGHT_DIE / 2;
		right = left + ENERMY_BBOX_WIDTH;
		bottom = top + ENERMY_BBOX_HEIGHT_DIE;
	}
	else
	{
		left = x - ENERMY_BBOX_WIDTH / 2;
		top = y - ENERMY_BBOX_HEIGHT / 2;
		right = left + ENERMY_BBOX_WIDTH;
		bottom = top + ENERMY_BBOX_HEIGHT;
	}
}
void Enermy::render()
{
	int aniID = 0;
	if (state == ENERMY_STATE_DIE)
	{
		aniID = ID_ANI_ENERMY_DIE;
	}
	else if (ax >= 0)
	{
		aniID = ID_ANI_ENERMY_WALKING_RIGHT;
	}
	else
	{
		aniID = ID_ANI_ENERMY_WALKING_LEFT;
	}
	

	Animations::GetInstance()->Get(aniID)->Render(x, y);
	RenderBoundingBox();
}
void Enermy::SetState(int state)
{
	Gameobject::SetState(state);
	switch (state)
	{
	case ENERMY_STATE_DIE:
		die_start = GetTickCount64();
		y += (ENERMY_BBOX_HEIGHT - ENERMY_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case ENERMY_STATE_WALKING:
		//vy = 0;
		//ax = 0.001f;
		if (((LPPLAYSCENE)Game::GetInstance()->GetCurrentScene())->GetPlayer()->Getx() - this->x > 0)
		{
			ax = 0.001f; nx = 1;
		}
		else if (((LPPLAYSCENE)Game::GetInstance()->GetCurrentScene())->GetPlayer()->Getx()-this->x < 0)
		{
			ax = -0.001f;
			nx = -1;
		}
		else
		{
			vx = 0;
			ax = 0;
		}
		DebugOut(L"POS %f,%f,%f,%f\n", this->x, this->y,
			((LPPLAYSCENE)Game::GetInstance()->GetCurrentScene())->GetPlayer()->Getx(),
			((LPPLAYSCENE)Game::GetInstance()->GetCurrentScene())->GetPlayer()->Gety());
		if (this->y - ((LPPLAYSCENE)Game::GetInstance()->GetCurrentScene())->GetPlayer()->Gety() > 0)
		{
			ay = -0.001f; ny = -1;
		}
		else if (this->y - ((LPPLAYSCENE)Game::GetInstance()->GetCurrentScene())->GetPlayer()->Gety()< 0)
		{
			ay = 0.001f;
			ny = 1;
		}
		else
		{
			vy = 0;
			ay = 0;
		}
		DebugOut(L"state %f,%f,%f,%f\n", ax, ay,vx,vy);
		maxVx = ENERMY_WALKING_SPEED;
		maxVy = ENERMY_WALKING_SPEED;
		break;
	}
}