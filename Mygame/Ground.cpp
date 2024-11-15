#include "Ground.h"
#include"Playablechracter.h"
#include "PlayScene.h"
#include "Game.h"

void Ground::Render()
{
	Animations::GetInstance()->Get(ID_ANI_GROUND)->Render(x, y);
	/*Animations* animations = Animations::GetInstance();
	animations->Get(ID_ANI_GROUND)->Render(x, y);*/
	RenderBoundingBox();
}


void Ground::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x -GROUND_BBOX_WIDTH / 2;
	t = y - GROUND_BBOX_HEIGHT / 2;
	r = l + GROUND_BBOX_WIDTH;
	b = t + GROUND_BBOX_HEIGHT;
}
