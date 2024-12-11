#include "Colision.h"
#include"GameObject.h"
#include <algorithm>
Colision* Colision::__instance = NULL; //pre def
int CollisionEvent::Collided()
{
	return t >= 0.0f && t <= 1.0f && objd->IsDirectionColliable(nx, ny) == 1;
}
	Colision* Colision::GetInstance()
	{
		if (__instance == NULL) __instance = new Colision();
		return __instance;
	}
void Colision::SweptAABB(
	float ml, float mt, float mr, float mb,
	float dx, float dy,
	float sl, float st, float sr, float sb,
	float& t, float& nx, float& ny
)
{
	float dx_entry,  dx_exit,  dy_entry,  dy_exit;//distance
	float tx_entry,  tx_exit,  ty_entry,  ty_exit;//time
	float t_entry, t_exit;//time in total
	t = -1.0f;//no col
	nx = ny = 0;
	//Broadphase(mo rong collision box theo phuong di chuyen)
	float bl = dx > 0 ? ml : ml + dx;  // Adjust left bound based on movement
	float br = dx > 0 ? mr + dx : mr;  // Adjust right bound based on movement
	float bt = dy > 0 ? mt + dy : mt;  // Fix: Use dy instead of dx
	float bb = dy > 0 ? mb : mb + dy;  // Adjust bottom bound based on movement

	if (dx == 0 && dy == 0) return;//relative speed =0-> can not col
	if (br < sl || bl > sr || bb > st|| bt < sb)
	{
		return;
	}
	
	//exit la 2 mat xa nhat theo phuong di chuyen
	//entry la 2 mat gan nhat neu di chuyen dung phuong co the va cham
	if (dx > 0)
	{
		dx_entry = sl - mr;
		dx_exit = sr - ml;
	}
	else
	{
		dx_entry = sr - ml;
		dx_exit = sl - mr;
	}
	if (dy > 0)
	{
		dy_entry = sb - mt;
		dy_exit = st - mb;
	}
	else
	{
		dy_entry = st - mb;
		dy_exit = sb - mt;
	}
	//calculate time
	if (dx == 0)
	{
		tx_entry = -9999999.0f;
		tx_exit = 99999999.0f;
	}
	else
	{
		tx_entry = dx_entry / dx;
		tx_exit = dx_exit / dx;
	}

	if (dy == 0)
	{
		ty_entry = -99999999999.0f;
		ty_exit = 99999999999.0f;
	}
	else
	{
		ty_entry = dy_entry / dy;
		ty_exit = dy_exit / dy;
	}
	//calculate final time
	if ((tx_entry < 0.0f && ty_entry < 0.0f) || tx_entry > 1.0f || ty_entry > 1.0f) return;

	t_entry = max(tx_entry, ty_entry);//all x and y enter col phase ->col
	t_exit = min(tx_exit, ty_exit);//x or y exit -> no more collision
	if (t_entry > t_exit)
	{
		return;
	}
	t = t_entry;
	if (tx_entry > ty_entry)//direction x or y first
	{
		ny = 0.0f;
		dx > 0 ? nx = -1.0f : nx = 1.0f;//col left or right
	}
	else
	{
		nx = 0.0f;
		dy > 0 ? ny = -1.0f : ny = 1.0f;//col top or bot
	}

}
/*
	Extension of original SweptAABB to deal with two moving objects
*/
LPCOLLISIONEVENT Colision::SweptAABB(LPGAMEOBJECT objSrc, DWORD dt, LPGAMEOBJECT objDest)
{
	float sl, st, sr, sb;		// static object bbox consider one of two object is static static ob is speed =0
	float ml, mt, mr, mb;		// moving object bbox
	float t, nx, ny;

	float mvx, mvy;
	objSrc->GetSpeed(mvx, mvy);
	float mdx = mvx; //distance in one frame(speed calculate depend on frame
	float mdy = mvy;
	float svx, svy;
	objDest->GetSpeed(svx, svy);
	float sdx = svx ;//distance in one frame(speed calculate depend on frame
	float sdy = svy ;
	//
	// NOTE: new m speed = original m speed - collide object speed
	// 
	float dx = mdx - sdx;//speed
	
	float dy = mdy - sdy;//speed

	objSrc->GetBoundingBox(ml, mt, mr, mb);//getboundbox of src
	objDest->GetBoundingBox(sl, st, sr, sb);//getboundbox of dest

	SweptAABB(
		ml, mt, mr, mb,
		dx, dy,
		sl, st, sr, sb,
		t, nx, ny
	);
	CollisionEvent* e = new CollisionEvent(t, nx, ny, dx, dy, objSrc,objDest );
	return e;
}
//scan all possible col event for src and dest
void Colision::scan(LPGAMEOBJECT objSrc, DWORD dt, vector<LPGAMEOBJECT>* objDests, vector<LPCOLLISIONEVENT>& coEvents)
{
	for (UINT i = 0; i < objDests->size(); i++)
	{
		if (objSrc->objecttag != objDests->at(i)->objecttag) {
			LPCOLLISIONEVENT e = SweptAABB(objSrc, dt, objDests->at(i));

			if (e->Collided() == 1)
			{
				coEvents.push_back(e);
			}
			else
				delete e;
		}

	}
	//DebugOut(L"event size right after scan: %d\n", coEvents.size());
}
//filter the condition of col
void Colision::filter(LPGAMEOBJECT objSrc,
	vector<LPCOLLISIONEVENT>& coEvents,
	LPCOLLISIONEVENT& colX,
	LPCOLLISIONEVENT& colY,
	int filterBlock = 1,		// 1 = only filter block collisions, 0 = filter all collisions 
	int filterX = 1,			// 1 = process events on X-axis, 0 = skip events on X 
	int filterY = 1)			// 1 = process events on Y-axis, 0 = skip events on Y
{
	
	float min_tx, min_ty;

	min_tx = 1.0f;
	min_ty = 1.0f;
	int min_ix = -1;
	int min_iy = -1;

	for (UINT i = 0; i < coEvents.size(); i++)
	{
		LPCOLLISIONEVENT c = coEvents[i];//collison event with all member colliable in playscene
		if (c->isdelete) continue;//skip if delete
		if (c->objd->IsDeleted()) continue; //if the object deleted
		// ignore collision event with object having IsBlocking = 0 (like coin, mushroom, etc)
		if (filterBlock == 1 && !c->objd->IsBlocking())
		{
			continue;
		}
		//if x only event happen first return pos in co event and dest blocking
		if (c->t < min_tx && c->nx != 0 && filterX == 1) {
			min_tx = c->t; min_ix = i;
		}
		//if y only event happen first return pos in co event and dest blocking
		if (c->t < min_ty && c->ny != 0 && filterY == 1) {
			min_ty = c->t; min_iy = i;
		}
	}
	//checking if there is any one axis col
	if (min_ix >= 0) colX = coEvents[min_ix];
	if (min_iy >= 0) colY = coEvents[min_iy];
}
//void Colision::process(LPGAMEOBJECT objSrc, DWORD dt, vector<LPGAMEOBJECT>* coObjects)
//{
//	vector<LPCOLLISIONEVENT> coEvents;
//	LPCOLLISIONEVENT colX = NULL;
//	LPCOLLISIONEVENT colY = NULL;
//
//	coEvents.clear();
//
//	if (objSrc->IsCollidable())//check for any co available for src and coobj
//	{
//		scan(objSrc, dt, coObjects, coEvents);
//	}
//	// No collision detected
//	if (coEvents.size() == 0)
//	{
//		objSrc->OnNoCollision(dt);
//	}
//	else
//	{
//		filter(objSrc, coEvents, colX, colY);
//
//		float x, y, vx, vy, dx, dy;
//		objSrc->GetPosition(x, y);
//		objSrc->GetSpeed(vx, vy);
//		dx = vx ;
//		dy = vy ;
//		if (colX != NULL && colY != NULL) //check and modified
//		{
//			
//			if (colY->t < colX->t)	// was collision on Y first ?(y block first)
//			{
//				//if blocking
//				y += colY->t * dy + colY->ny * BLOCK_PUSH_FACTOR;
//				objSrc->SetPosition(x, y);
//
//				objSrc->OnCollisionWith(colY);
//
//				//
//				// see if after correction on Y, is there still a collision on X ? 
//				//
//				LPCOLLISIONEVENT colX_other = NULL;
//
//				//
//				// check again if there is true collision on X 
//				//
//				colX->isdelete = true;		// remove current collision event on X
//
//				// replace with a new collision event using corrected location 
//				coEvents.push_back(SweptAABB(objSrc, dt, colX->objd));
//
//				// re-filter on X only
//				filter(objSrc, coEvents, colX_other, colY, /*filterBlock = */ 1, 1, /*filterY=*/0);//skip Y event for this filter because Y already done giai quyet tiep qua de quy
//				//still has event on x
//				if (colX_other != NULL)
//				{
//					x += colX_other->t * dx + colX_other->nx * BLOCK_PUSH_FACTOR;
//					objSrc->OnCollisionWith(colX_other);
//				}
//				else
//				{
//					x += dx;
//				}
//			}
//			else // collision on X first
//			{
//				//if blocking
//				x += colX->t * dx + colX->nx * BLOCK_PUSH_FACTOR;
//				objSrc->SetPosition(x, y);
//
//				objSrc->OnCollisionWith(colX);
//
//				//
//				// see if after correction on X, is there still a collision on Y ? 
//				//
//				LPCOLLISIONEVENT colY_other = NULL;
//
//				//
//				// check again if there is true collision on Y
//				//
//				colY->isdelete = true;		// remove current collision event on Y
//
//				// replace with a new collision event using corrected location 
//				coEvents.push_back(SweptAABB(objSrc, dt, colY->objd));
//
//				// re-filter on Y only
//				filter(objSrc, coEvents, colX, colY_other, /*filterBlock = */ 1, /*filterX=*/0, /*filterY=*/1);
//				//still has event on Y
//				if (colY_other != NULL)
//				{
//					y += colY_other->t * dy + colY_other->ny * BLOCK_PUSH_FACTOR;
//					objSrc->OnCollisionWith(colY_other);
//				}
//				else
//				{
//					y += dy;
//				}
//			}
//		}
//		else
//			if (colX != NULL)//hoac colx hoac coly null
//			{
//				x += colX->t * dx + colX->nx * BLOCK_PUSH_FACTOR;
//				y += dy;
//				objSrc->OnCollisionWith(colX);
//			}
//			else {//x null
//				if (colY != NULL)
//				{
//					
//					x += dx;
//					y += colY->t * dy + colY->ny * BLOCK_PUSH_FACTOR;
//					objSrc->OnCollisionWith(colY);
//				}
//				else // both colX & colY are NULL 
//				{
//					x += dx;
//					y += dy;
//				}
//			}
//
//		objSrc->SetPosition(x, y);
//	}
//
//	//
//	// Scan all non-blocking collisions for further collision logic
//	//
//	for (UINT i = 0; i < coEvents.size(); i++)//check col with all collsion that from non blocking object
//	{
//		LPCOLLISIONEVENT e = coEvents[i];
//		if (e->isdelete) continue;
//		if (e->objd->IsBlocking()) continue;  // blocking collisions were handled already, skip them
//
//		objSrc->OnCollisionWith(e);
//	}
//
//
//	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];//xoa toan bo nhung event 
//}