#include "Playablechracter.h"
#include "Debug.h"
void Playablechracter::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;
	
	if (abs(vx) > abs(maxVx)) vx = maxVx;
	if(abs(vy)>abs(maxVy))	vy=maxVy;
	/*x += vx;
	y += vy;*/
	// reset untouchable timer if untouchable time has passed
	if (GetTickCount64() - untouchable_start > JASON_DASH_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}
	if (health <= 0) {
		this->SetState(JASON_STATE_DIE);
	}
	if (state == JASON_STATE_DIE) {
		isdeleted = true;
		return;
	}
	Gameobject::Update(dt, coObjects);
	CollisionProcess(dt, coObjects);
	
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
	case BIG_JASON_STATE_WALK_DOWN:
		maxVy = -JASON_WALKING_SPEED;
		ay = -JASON_ACCEL_WALK;
		ax = 0;
		vx = 0;
		ny = -1;
		nx = 0;
		GunDirectionX = 0;
		GunDirectionY = -1;
		break;
	case BIG_JASON_STATE_WALK_UP:
		maxVy = JASON_WALKING_SPEED;
		ay = JASON_ACCEL_WALK;
		ax = 0;
		vx = 0;
		ny = 1;
		nx = 0;
		GunDirectionX = 0;
		GunDirectionY = 1;
		break;
	case BIG_JASON_STATE_WALK_RIGHT:
		maxVx = JASON_WALKING_SPEED;
		ax = JASON_ACCEL_WALK;
		ay = 0;
		vy =0 ;
		nx = 1;
		ny = 0;
		GunDirectionX = 1;
		GunDirectionY = 0;
		break;
	case BIG_JASON_STATE_WALK_LEFT:
		maxVx = -JASON_WALKING_SPEED;
		ax = -JASON_ACCEL_WALK;
		ay = 0;
		vy = 0;
		nx = -1;
		ny = 0;
		GunDirectionX = -1;
		GunDirectionY = 0;
		break;
	case BIG_JASON_STATE_IDLE:
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
}
void Playablechracter::SetLevel(int l)
{
}

void Playablechracter::Shoot() {
	PlayerBullet* pBullet = new PlayerBullet(x, y);
	pBullet->ShootService(GunDirectionX, GunDirectionY);
}
void Playablechracter::TakeDamage(int dame) {
	if (dame == 0)
		return;


	if (dame < health)
	{
		health -= dame;
	}
	else
	{
		health = 0;
	}
}
void Playablechracter::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - JASON_BIG_BBOX_WIDTH / 2;
	top = y +JASON_BIG_BBOX_HEIGHT / 2;
	right = left + JASON_BIG_BBOX_WIDTH;
	bottom = top - JASON_BIG_BBOX_HEIGHT;
}

void Playablechracter::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}
void Playablechracter::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->objd->objecttag == "Ground")
	{
		Colision::GetInstance()->PushingX(e->t, e->dx, e->nx, x, e);
		Colision::GetInstance()->PushingY(e->t, e->dy, e->ny, y, e);
	}
	if (e->objd->objecttag == "HealUp")
	{
		HealUp* healup = new HealUp(0,0);
		resHealth(healup->GetAmount());
		e->objd->Delete();

	}
	if (e->objd->objecttag == "Enermy")
	{
		TakeDamage(10);
	}
	if (e->objd->objecttag == "Bomb")
	{
		Bomb* bomb = new Bomb(0, 0);
		TakeDamage(bomb->dame);
		e->objd->Delete();
	}
	if (e->objd->objecttag == "OffBullet")
	{
		OffBullet* oBullet = new OffBullet(0, 0);
		TakeDamage(oBullet->dame);
		e->objd->Delete();
	}
}
void Playablechracter::OnkeyUP(int keycode)
{

}
void Playablechracter::OnkeyDown(int keycode)
{
}
void Playablechracter::Keystate(BYTE* key)
{
	LPGAME game = game->GetInstance();
	if (state == JASON_STATE_DIE)
	{
		return;
	}
	else if (state == BIG_JASON_STATE_IDLE)
	{
		if (game->IsKeyDown(DIK_S))
		{
			SetState(BIG_JASON_STATE_WALK_DOWN);
		}
		else if (game->IsKeyDown(DIK_A))
		{
			SetState(BIG_JASON_STATE_WALK_LEFT);
		}
		else if (game->IsKeyDown(DIK_D))
		{
			SetState(BIG_JASON_STATE_WALK_RIGHT);
		}
		else if (game->IsKeyDown(DIK_W))
		{
			SetState(BIG_JASON_STATE_WALK_UP);
		}
		else if (game->IsKeyDown(DIK_C))
		{
			if (GetTickCount64() - this->GetLastShoot() >= 500) {

				Shoot();
				this->SetLastShoot();
			}
		}
		else
		{
			SetState(BIG_JASON_STATE_IDLE);
		}
	}
	else if (state == BIG_JASON_STATE_WALK_UP || state == BIG_JASON_STATE_WALK_LEFT
		|| state == BIG_JASON_STATE_WALK_DOWN || state == BIG_JASON_STATE_WALK_RIGHT)
	{
		if (game->IsKeyDown(DIK_S))
		{
			SetState(BIG_JASON_STATE_WALK_DOWN);
		}
		else if (game->IsKeyDown(DIK_A))
		{
			SetState(BIG_JASON_STATE_WALK_LEFT);
		}
		else if (game->IsKeyDown(DIK_D))
		{
			SetState(BIG_JASON_STATE_WALK_RIGHT);
		}
		else if (game->IsKeyDown(DIK_W))
		{
			SetState(BIG_JASON_STATE_WALK_UP);
		}
		else
		{
			SetState(BIG_JASON_STATE_IDLE);
		}
	}
}
void Playablechracter::CollisionProcess(DWORD dt, vector<LPGAMEOBJECT>* coObject)
{
	vector<LPCOLLISIONEVENT>event;
	LPCOLLISIONEVENT colX=NULL;
	LPCOLLISIONEVENT colY=NULL;
	event.clear();
	if (IsCollidable())
	{
		Colision::GetInstance()->scan(this, dt, coObject, event);
	}
	if (event.size() == 0)
	{
		OnNoCollision(dt);
	}
	else
	{
		Colision::GetInstance()->filter(this, event, colX, colY, 1, 1, 1);
		if (colX != NULL && colY != NULL)
		{
			if (colX < colY)
			{
				this->OnCollisionWith(colX);
				LPCOLLISIONEVENT colY_other = NULL;
				colX->isdelete = true;
				event.push_back(Colision::GetInstance()->SweptAABB(this, dt, colX->objd));
				Colision::GetInstance()->filter(this, event, colX, colY_other,1,0,1);
				if (colY_other != NULL)
				{
					OnCollisionWith(colY_other);
				}
				else
				{
					y += vy*dt;
				}
			}
			else
			{
				this->OnCollisionWith(colY);
				LPCOLLISIONEVENT colX_other = NULL;
				colY->isdelete = true;
				event.push_back(Colision::GetInstance()->SweptAABB(this, dt, colY->objd));
				Colision::GetInstance()->filter(this, event, colX_other, colY, 1, 1, 0);
				if (colX_other != NULL)
				{
					OnCollisionWith(colX_other);
				}
				else
				{
					x +=vx*dt;
				}
			}
		}
		else
		{
			if (colX != NULL)//hoac colx hoac coly null
				{
							y += vy*dt;
							this->OnCollisionWith(colX);
				}
			else {//x null
				if (colY != NULL)
				{
					x += vx*dt;
					this->OnCollisionWith(colY);
				}
				else // both colX & colY are NULL 
				{
					x += vx*dt;
					y += vy*dt;
				}
			}
		}
	// Scan all non-blocking collisions for further collision logic
	//
	for (UINT i = 0; i < event.size(); i++)//check col with all collsion that from non blocking object
	{
		LPCOLLISIONEVENT e = event[i];
		if (e->isdelete) continue;
		if (e->objd->IsBlocking()) continue;  // blocking collisions were handled already, skip them

		OnCollisionWith(e);
	}


	for (UINT i = 0; i <event.size(); i++) delete event[i];//xoa toan bo nhung event 
	}
}
