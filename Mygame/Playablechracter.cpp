#include "Playablechracter.h"
#include "Debug.h"
void Playablechracter::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;
	
	
	if (abs(vx) > abs(maxVx)) vx = maxVx;
	if(abs(vy)>abs(maxVy))	vy=maxVy;
	x += vx;
	y += vy;
	// reset untouchable timer if untouchable time has passed
	if (GetTickCount64() - untouchable_start > JASON_DASH_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}
}
int Playablechracter::GetAniIdBig()
{
	int aniId = -1;

	if (vx == 0&&vy==0)
	{
		if (nx > 0) aniId = ID_ANI_JASON_IDLE_RIGHT;
		else if (ny < 0) aniId = ID_ANI_JASON_IDLE_UP;
		else if (ny>0)		aniId= ID_ANI_JASON_IDLE_DOWN;
		else aniId = ID_ANI_JASON_IDLE_LEFT;
	}
	else if (vx > 0)
	{
			aniId = ID_ANI_JASON_WALKING_RIGHT;
	}
	else if(vx<0)// vx < 0
	{
			aniId = ID_ANI_JASON_WALKING_LEFT;
	}
	else if (vy > 0)
	{
		aniId = ID_ANI_JASON_WALKING_UP;
	}
	else if (vy < 0)
	{
		aniId = ID_ANI_JASON_WALKING_DOWN;
	}
	if (aniId == -1) aniId = ID_ANI_JASON_IDLE_RIGHT;

	return aniId;
}
void Playablechracter::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (this->state == JASON_STATE_DIE) return;

	switch (state)
	{
	case JASON_STATE_WALK_DOWN:
		maxVy = JASON_WALKING_SPEED;
		ay = JASON_ACCEL_WALK;
		ax = 0;
		vx = 0;
		ny = 1;
		nx = 0;
		break;
	case JASON_STATE_WALK_UP:
		maxVy = -JASON_WALKING_SPEED;
		ay = -JASON_ACCEL_WALK;
		ax = 0;
		vx = 0;
		ny = -1;
		nx = 0;
		break;
	case JASON_STATE_WALK_RIGHT:
		maxVx = JASON_WALKING_SPEED;
		ax = JASON_ACCEL_WALK;
		ay = 0;
		vy =0 ;
		nx = 1;
		ny = 0;
		break;
	case JASON_STATE_WALK_LEFT:
		maxVx = -JASON_WALKING_SPEED;
		ax = -JASON_ACCEL_WALK;
		ay = 0;
		vy = 0;
		nx = -1;
		ny = 0;
		break;
	case JASON_STATE_IDLE:
		ax = 0.0f;
		ay = 0.0f;
		vx = 0;
		vy = 0;
		break;
	case JASON_STATE_DIE:
		vy = 0.0f;
		vx = 0.0f;
		ax = 0.0f;
		ay = 0.0f;
		break;
	}

	
	Gameobject::setstate(state);
	
	DebugOut(L"Set stated %d\n", this->state);
}
void Playablechracter::SetLevel(int l)
{
	//// Adjust position to avoid falling off platform
	////if (this->level == MARIO_LEVEL_SMALL)
	////{
	//	y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
	//}
	level = l;
}
void Playablechracter::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - JASON_BIG_BBOX_WIDTH / 2;
	top = y - JASON_BIG_BBOX_HEIGHT / 2;
	right = left + JASON_BIG_BBOX_WIDTH;
	bottom = top + JASON_BIG_BBOX_HEIGHT;
}
void Playablechracter::OnkeyUP(int keycode)
{
	switch (keycode)
	{
	case DIK_W:
		SetState(JASON_STATE_WALK_UP);
		break;
	case DIK_S:
		SetState(JASON_STATE_WALK_DOWN);
		break;
	case DIK_D:
		SetState(JASON_STATE_WALK_RIGHT);
		break;
	case DIK_A:
		SetState(JASON_STATE_WALK_LEFT);
		break;
	default:
		DebugOut(L"No key called\n");
	}
}
void Playablechracter::Keystate(BYTE* key)
{
	LPGAME game = game->GetInstance();
	if (game->IsKeyDown(DIK_S))
	{
		if (game->IsKeyDown(DIK_LSHIFT))
		{
			DebugOut(L"DASHING");
			SetState(JASON_STATE_DASHING);
			DebugOut(L"DASHING");
		}
	}
	else if (game->IsKeyDown(DIK_A))
	{

	}
	else if (game->IsKeyDown(DIK_D))
	{

	}
	else if (game->IsKeyDown(DIK_W))
	{

	}
	else
	{
		SetState(JASON_STATE_IDLE);
	}
}