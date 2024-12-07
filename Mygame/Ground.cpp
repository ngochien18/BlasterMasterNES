#include "Ground.h"
#include"Playablechracter.h"
#include "PlayScene.h"
#include "Game.h"
#include "Animation.h"
#include "Animations.h"
#include "sprites.h"
#include "sprite.h"
#include "AnimationFrame.h"

Ground::Ground()
{
	width = 0;
	height = 0;
}
Ground::Ground(float x, float y, int width, int height)
{
	objecttag = "Ground";
	this->x = x;
	vx = 0;
	vy = 0;
	this->y = y;
	this->width = width;
	this->height = height;
}
void Ground::render()
{
	//Animations::GetInstance()->Get(ID_ANI_GROUND)->Render(x, y);
//	//Animations* animations = Animations::GetInstance();
//	//animations->Get(ID_ANI_GROUND)->render(x, y);
	RenderBoundingBox();

}

void Ground::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - width / 2;
	t = y - height / 2;
	r = l + width;
	b = t -height;
}
Ground::~Ground()
{

}