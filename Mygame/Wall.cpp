#include "Wall.h"
#include"Playablechracter.h"
#include "PlayScene.h"
#include "Game.h"
#include "Animation.h"
#include "Animations.h"
#include "sprites.h"
#include "sprite.h"
#include "AnimationFrame.h"

Wall::Wall()
{
	width = 0;
	height = 0;
}
Wall::Wall(float x, float y, int width, int height)
{
	objecttag = "Wall";
	this->x = x;
	vx = 0;
	vy = 0;
	this->y = y;
	this->width = width;
	this->height = height;
}
void Wall::render()
{
	RenderBoundingBox();
}

void Wall::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - width / 2;
	t = y + height / 2;
	r = l + width;
	b = t - height;
}
Wall::~Wall()
{

}