#include <algorithm>
#include "debug.h"

#include "Jason.h"
#include "Game.h"

#include "Goomba.h"
#include "Coin.h"
#include "Portal.h"

#include "Collision.h"

void CJason::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if (abs(vx) > abs(maxVx)) vx = maxVx;

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount64() - untouchable_start > JASON_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CJason::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
	isOnPlatform = false;
}

void CJason::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
		if (e->ny < 0) isOnPlatform = true;
	}
	else
		if (e->nx != 0 && e->obj->IsBlocking())
		{
			vx = 0;
		}

	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CCoin*>(e->obj))
		OnCollisionWithCoin(e);
	else if (dynamic_cast<CPortal*>(e->obj))
		OnCollisionWithPortal(e);
}

void CJason::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0)
	{
		if (goomba->GetState() != GOOMBA_STATE_DIE)
		{
			goomba->SetState(GOOMBA_STATE_DIE);
			vy = -JASON_JUMP_DEFLECT_SPEED;
		}
	}
	else // hit by Goomba
	{
		if (untouchable == 0)
		{
			if (goomba->GetState() != GOOMBA_STATE_DIE)
			{
				if (level > JASON_LEVEL_SMALL)
				{
					level = JASON_LEVEL_SMALL;
					StartUntouchable();
				}
				else
				{
					DebugOut(L">>> Jason DIE >>> \n");
					SetState(JASON_STATE_DIE);
				}
			}
		}
	}
}

void CJason::OnCollisionWithCoin(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	coin++;
}

void CJason::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	CPortal* p = (CPortal*)e->obj;
	CGame::GetInstance()->InitiateSwitchScene(p->GetSceneId());
}

//
// Get animation ID for small Jason
//
int CJason::GetAniIdSmall()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == JASON_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_JASON_SMALL_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_JASON_SMALL_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_JASON_SMALL_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_JASON_SMALL_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_JASON_SIT_RIGHT;
			else
				aniId = ID_ANI_JASON_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_JASON_SMALL_IDLE_RIGHT;
				else aniId = ID_ANI_JASON_SMALL_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_JASON_SMALL_BRACE_RIGHT;
				else if (ax == JASON_ACCEL_RUN_X)
					aniId = ID_ANI_JASON_SMALL_RUNNING_RIGHT;
				else if (ax == JASON_ACCEL_WALK_X)
					aniId = ID_ANI_JASON_SMALL_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_JASON_SMALL_BRACE_LEFT;
				else if (ax == -JASON_ACCEL_RUN_X)
					aniId = ID_ANI_JASON_SMALL_RUNNING_LEFT;
				else if (ax == -JASON_ACCEL_WALK_X)
					aniId = ID_ANI_JASON_SMALL_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_JASON_SMALL_IDLE_RIGHT;

	return aniId;
}


//
// Get animdation ID for big Jason
//
int CJason::GetAniIdBig()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == JASON_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_JASON_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_JASON_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_JASON_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_JASON_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_JASON_SIT_RIGHT;
			else
				aniId = ID_ANI_JASON_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_JASON_IDLE_RIGHT;
				else aniId = ID_ANI_JASON_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_JASON_BRACE_RIGHT;
				else if (ax == JASON_ACCEL_RUN_X)
					aniId = ID_ANI_JASON_RUNNING_RIGHT;
				else if (ax == JASON_ACCEL_WALK_X)
					aniId = ID_ANI_JASON_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_JASON_BRACE_LEFT;
				else if (ax == -JASON_ACCEL_RUN_X)
					aniId = ID_ANI_JASON_RUNNING_LEFT;
				else if (ax == -JASON_ACCEL_WALK_X)
					aniId = ID_ANI_JASON_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_JASON_IDLE_RIGHT;

	return aniId;
}

void CJason::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;

	if (state == JASON_STATE_DIE)
		aniId = ID_ANI_JASON_DIE;
	else if (level == JASON_LEVEL_BIG)
		aniId = GetAniIdBig();
	else if (level == JASON_LEVEL_SMALL)
		aniId = GetAniIdSmall();

	animations->Get(aniId)->Render(x, y);

	//RenderBoundingBox();

	DebugOutTitle(L"Coins: %d", coin);
}

void CJason::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (this->state == JASON_STATE_DIE) return;

	switch (state)
	{
	case JASON_STATE_RUNNING_RIGHT:
		if (isSitting) break;
		maxVx = JASON_RUNNING_SPEED;
		ax = JASON_ACCEL_RUN_X;
		nx = 1;
		break;
	case JASON_STATE_RUNNING_LEFT:
		if (isSitting) break;
		maxVx = -JASON_RUNNING_SPEED;
		ax = -JASON_ACCEL_RUN_X;
		nx = -1;
		break;
	case JASON_STATE_WALKING_RIGHT:
		if (isSitting) break;
		maxVx = JASON_WALKING_SPEED;
		ax = JASON_ACCEL_WALK_X;
		nx = 1;
		break;
	case JASON_STATE_WALKING_LEFT:
		if (isSitting) break;
		maxVx = -JASON_WALKING_SPEED;
		ax = -JASON_ACCEL_WALK_X;
		nx = -1;
		break;
	case JASON_STATE_JUMP:
		if (isSitting) break;
		if (isOnPlatform)
		{
			if (abs(this->vx) == JASON_RUNNING_SPEED)
				vy = -JASON_JUMP_RUN_SPEED_Y;
			else
				vy = -JASON_JUMP_SPEED_Y;
		}
		break;

	case JASON_STATE_RELEASE_JUMP:
		if (vy < 0) vy += JASON_JUMP_SPEED_Y / 2;
		break;

	case JASON_STATE_SIT:
		if (isOnPlatform && level != JASON_LEVEL_SMALL)
		{
			state = JASON_STATE_IDLE;
			isSitting = true;
			vx = 0; vy = 0.0f;
			y += JASON_SIT_HEIGHT_ADJUST;
		}
		break;

	case JASON_STATE_SIT_RELEASE:
		if (isSitting)
		{
			isSitting = false;
			state = JASON_STATE_IDLE;
			y -= JASON_SIT_HEIGHT_ADJUST;
		}
		break;

	case JASON_STATE_IDLE:
		ax = 0.0f;
		vx = 0.0f;
		break;

	case JASON_STATE_DIE:
		vy = -JASON_JUMP_DEFLECT_SPEED;
		vx = 0;
		ax = 0;
		break;
	}

	CGameObject::SetState(state);
}

void CJason::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (level == JASON_LEVEL_BIG)
	{
		if (isSitting)
		{
			left = x - JASON_BIG_SITTING_BBOX_WIDTH / 2;
			top = y - JASON_BIG_SITTING_BBOX_HEIGHT / 2;
			right = left + JASON_BIG_SITTING_BBOX_WIDTH;
			bottom = top + JASON_BIG_SITTING_BBOX_HEIGHT;
		}
		else
		{
			left = x - JASON_BIG_BBOX_WIDTH / 2;
			top = y - JASON_BIG_BBOX_HEIGHT / 2;
			right = left + JASON_BIG_BBOX_WIDTH;
			bottom = top + JASON_BIG_BBOX_HEIGHT;
		}
	}
	else
	{
		left = x - JASON_SMALL_BBOX_WIDTH / 2;
		top = y - JASON_SMALL_BBOX_HEIGHT / 2;
		right = left + JASON_SMALL_BBOX_WIDTH;
		bottom = top + JASON_SMALL_BBOX_HEIGHT;
	}
}

void CJason::SetLevel(int l)
{
	// Adjust position to avoid falling off platform
	if (this->level == JASON_LEVEL_SMALL)
	{
		y -= (JASON_BIG_BBOX_HEIGHT - JASON_SMALL_BBOX_HEIGHT) / 2;
	}
	level = l;
}

