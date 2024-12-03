#include "Gameobject.h"
#include <d3dx9.h>
#include <algorithm>


#include "debug.h"
#include "Textures.h"
#include "Game.h"
#include "GameObject.h"
#include "Sprites.h"

Gameobject::Gameobject()
{
	x = y = 0;
	vx = vy = 0;
	nx = 1;
	ny = 0;
	state = -1;
	isdeleted = false;
}

void Gameobject::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPTEXTURE bbox = Textures::GetInstance()->Get(ID_TEX_BBOX);

	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)t - (int)b;

	float cx, cy;
	Game::GetInstance()->GetCamera()->GetCamPos(cx, cy);
	Game::GetInstance()->Draw(x-cx, cy-y, bbox, &rect, BBOX_ALPHA);
}

Gameobject::~Gameobject()
{

}