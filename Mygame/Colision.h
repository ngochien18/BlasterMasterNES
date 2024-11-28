#pragma once
#include "Windows.h"
#include <vector>
using namespace std;

class Gameobject;
typedef Gameobject* LPGAMEOBJECT;
struct CollisionEvent;
typedef CollisionEvent* LPCOLLISIONEVENT;
struct CollisionEvent
{
	LPGAMEOBJECT objs;//source object:calculate from this
	LPGAMEOBJECT objd;//targetobject
	float t, nx, ny;//time and direction of collison
	float dx, dy;//speed of collison(relative speed of two object)=0 is they are not collison is x or y axis
	bool isdelete;// this collision mentioned before
	CollisionEvent(float t, float nx, float ny, float dx = 0, float dy = 0, LPGAMEOBJECT src = NULL, LPGAMEOBJECT dest = NULL)
	{
		this->t = t;
		this->nx = nx;
		this->ny = ny;
		this->dx = dx;
		this->dy = dy;
		objs = src;
		objd = dest;
		isdelete = 0;
	}
	int Collided();
	static bool compare(const LPCOLLISIONEVENT& a,const LPCOLLISIONEVENT& b)
	{
		return a->t < b->t;
	}
};
class Colision
{
	static Colision* __instance;
public:
	static void SweptAABB(
		float ml,//moving object bounding box
		float mt,
		float mr,
		float mb,
		float dx,//relative speed
		float dy,
		float sl,//static bounding box
		float st,
		float sr,
		float sb,
		float & t,
		float & nx,//direction
		float & ny
		);
	LPCOLLISIONEVENT SweptAABB(
		LPGAMEOBJECT objsrc, DWORD dt,
		LPGAMEOBJECT objdest);
	void scan(LPGAMEOBJECT objsrc, DWORD dt,
		vector<LPGAMEOBJECT>* objdest, vector<LPCOLLISIONEVENT>& coEvents);//scan all possible collision
	void filter(LPGAMEOBJECT objsrc,
		 vector<LPCOLLISIONEVENT>&coEvents,
		LPCOLLISIONEVENT &COLX, LPCOLLISIONEVENT& COLY,
		int filterblock,int filterX,int filterY);//check collision condition
	void process(LPGAMEOBJECT objsrc, DWORD dt, vector<LPGAMEOBJECT>*coobj);
	static Colision* GetInstance();
};

